#pragma once
#include <WiFi.h>
#include <stdint.h>
#include <ESPmDNS.h>
#include <Arduino.h>
#include <ArduinoOTA.h>

class WiFiService
{
    public:
	int8_t connect(const char *ssid, const char *pass);
};

class mDNSService
{
    public:
	int8_t init(const char *hostname);
};

class OTAService
{
    public:
	void init(const char *hostname, const char *pass);
	void handle();
};