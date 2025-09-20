#include "wifi_helpers.h"
#include "secrets.h"
#include "config.h"

WiFiService wifi;
mDNSService mdns;
OTAService ota;

void setup()
{
	Serial.begin(115200);
	Serial.write("\n");

	Serial.print("[WIFI] Connecting to WiFi");
	if (wifi.connect(WIFI_SSID, WIFI_PASS) == 0) {
		Serial.println("\n[WIFI] WiFi Connected!");
		Serial.print("[WIFI] IP Address: ");
		Serial.println(WiFi.localIP());
	} else {
		Serial.println("\n[WIFI] WiFi Failed to Connect. Rebooting...");
		ESP.restart();
	}

	ota.init(OTA_HOSTNAME, OTA_PASS);
	Serial.println("[OTA ] OTA Ready");

	if (mdns.init(MDNS_HOSTNAME) == 0) {
		Serial.print("[MDNS] mDNS Ready: ");
		Serial.print(MDNS_HOSTNAME);
		Serial.println(".local");
	} else {
		Serial.println("[MDNS] Initialization failed!");
	}
}

void loop()
{
	ota.handle();
}