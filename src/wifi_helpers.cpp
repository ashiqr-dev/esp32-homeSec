#include "wifi_helpers.h"

int8_t WiFiService::connect(const char *ssid, const char *pass)
{
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, pass);

	for (int8_t i = 0; i < 20; i++)
	{
		if (WiFi.status() == WL_CONNECTED)
		{
			return 0;
		}
		Serial.write(".");
		delay(500);
	}

	return -1;
}

int8_t mDNSService::init(const char *hostname)
{
	if (!MDNS.begin(hostname))
		return -1;
	else
		return 0;
}

void OTAService::init(const char *hostname, const char *pass)
{
	if (hostname != nullptr)
	{
		ArduinoOTA.setHostname(hostname);
	}

	if (pass != nullptr)
	{
		ArduinoOTA.setPassword(pass);
	}

	ArduinoOTA.onStart([]()
					   { Serial.println("OTA Start"); });

	ArduinoOTA.onEnd([]()
					 { Serial.println("\nOTA End"); });

	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
						  { Serial.printf("OTA Progress: %u%%\r", (progress * 100) / total); });

	ArduinoOTA.onError([](ota_error_t error)
					   {
		Serial.printf("OTA Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR)
			Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR)
			Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR)
			Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR)
			Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR)
			Serial.println("End Failed"); });

	ArduinoOTA.begin();
}

void OTAService::handle()
{
	ArduinoOTA.handle();
}