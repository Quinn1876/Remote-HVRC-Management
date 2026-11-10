#include "WifiDriver.hpp"
#include "WiFi.h"
#include "Arduino.h"

#include "secrets.hpp"
#define DEBUG_WIFI_DRIVER 1

namespace WifiDriver::Constants {
static const char*& SSID = Secrets::WIFI_SSID;
static const char*& PASSWORD = Secrets::WIFI_PASSWORD;
}

namespace WifiDriver {

void Driver::setup(const char* host_name) {
    WiFi.setHostname(host_name);
    setup();
}

void Driver::setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(Constants::SSID, Constants::PASSWORD);
    _is_setup_complete = true;
}

bool Driver::is_setup_complete() const {
    return _is_setup_complete;
}

bool Driver::is_connected() const {
    if (!is_setup_complete()) {
        #if DEBUG_WIFI_DRIVER
            Serial.println("Driver Setup must be complete before connecting");
        #endif
        return false;
    }
    bool res = WiFi.status() == WL_CONNECTED;
    #if DEBUG_WIFI_DRIVER
    if (!res) {
        auto status = WiFi.status();
        char* status_string = nullptr;
        switch (status) {
            case WL_NO_SHIELD:
                status_string = "WL_NO_SHIELD";
                break;
            case WL_STOPPED:
                status_string = "WL_STOPPED";
                break;
            case WL_IDLE_STATUS:
                status_string = "WL_IDLE_STATUS";
                break;
            case WL_NO_SSID_AVAIL:
                status_string = "WL_NO_SSID_AVAIL";
                break;
            case WL_SCAN_COMPLETED:
                status_string = "WL_SCAN_COMPLETED";
                break;
            case WL_CONNECTED:
                status_string = "WL_CONNECTED";
                break;
            case WL_CONNECT_FAILED:
                status_string = "WL_CONNECT_FAILED";
                break;
            case WL_CONNECTION_LOST:
                status_string = "WL_CONNECTION_LOST";
                break;
            case WL_DISCONNECTED:
                status_string = "WL_DISCONNECTED";
                break;
        }
        Serial.println(status_string);
    }
    #endif
    return res;
}

void Driver::print_connection_info() const {
    Serial.println("Connected to Wi-Fi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway (Router IP): ");
    Serial.println(WiFi.gatewayIP()); // Get router's IP address
    Serial.println(WiFi.macAddress());
}
}
