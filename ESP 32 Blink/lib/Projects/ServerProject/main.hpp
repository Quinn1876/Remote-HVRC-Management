#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "WifiDriver.hpp"
#include "SerialDriver.hpp"
#include "pages.hpp"
#include "WebServer.h"

WebServer server(80);
int minutes = 0;
hw_timer_t *Timer0_Cfg = NULL;

void handle_index() {
    server.send(200, "text/html", Pages::index_html);
}

#define RELAY_IO GPIO_NUM_4

void handle_addTime() {
    if (minutes < 60) {
        auto add_time_value = server.arg("value").toInt();
        if (add_time_value > 60 - minutes) {
            Serial.println("Caping time at 60");
            minutes = 60;
        } else if (add_time_value > 0) {
            Serial.println("Adding Time");
            minutes += add_time_value;
        }
        if (minutes > 0) {
            // add_time_value can be zero
            digitalWrite(RELAY_IO, HIGH);
            digitalWrite(LED_BUILTIN, HIGH);
        }
    }

    JsonDocument document;
    document["minutes"] = minutes;
    char content[20];
    serializeJson(document, content);
    server.send(200, "application/json", content);
}

void handle_clearTime() {
    Serial.println("Clearing Time");
    minutes = 0;
    digitalWrite(RELAY_IO, LOW);
    digitalWrite(LED_BUILTIN, LOW);

    JsonDocument document;
    document["minutes"] = minutes;
    char content[20];
    serializeJson(document, content);
    server.send(200, "application/json", content);
}

void handle_favicon() {
    server.send(404, "text/text", "No Icon available");
}

void IRAM_ATTR Timer0_ISR()
{
    if (minutes > 0) {
        minutes -= 1;
        if (minutes == 0) {
            digitalWrite(RELAY_IO, LOW);
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}

WifiDriver::Driver wifi_driver;
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(RELAY_IO, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.begin(SerialDriver::Constants::BAUD_RATE);

    wifi_driver.setup();
    while (!wifi_driver.is_connected()) {
        Serial.println("Waiting to connect...");
        delay(500);
    }
    Serial.println("Connected");
    wifi_driver.print_connection_info();
    server.on("/", HTTP_GET, handle_index);
    /** TODO: GET requests here are temp. Update to proper protocol later */
    server.on("/addTime", handle_addTime);
    server.on("/clearTime", handle_clearTime);
    server.on("/favicon.ico", handle_favicon);
    server.begin();
    digitalWrite(LED_BUILTIN, LOW);

    delay(500);

    Timer0_Cfg = timerBegin(1'000'000);
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR);
    timerAlarm(Timer0_Cfg, 60 * 1'000'000, true, 0);
}

void loop() {
    server.handleClient();
}
