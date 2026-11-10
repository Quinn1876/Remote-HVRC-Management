#pragma once
#include <Arduino.h>
#include "WifiDriver.hpp"
#include "SerialDriver.hpp"

WifiDriver::Driver wifi_driver;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(SerialDriver::Constants::BAUD_RATE);
  Serial.println("Hello from the setup");
  wifi_driver.setup();
  while (!wifi_driver.is_connected()) {
    Serial.println("Waiting for Wifi Connection");
    delay(500);
  }
  Serial.println("Connected");
  wifi_driver.print_connection_info();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Hello from the loop");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}
