#include "wifi_helpers.h"
#include "secrets.h"
#include "config.h"

WiFiService wifi;
mDNSService mdns;

void setup()
{
	Serial.begin(115200);
	Serial.write("\n");

	if (wifi.connect(WIFI_SSID, WIFI_PASS) > -1) {
		Serial.println("[WIFI] WiFi Connected!");
		Serial.print("[WIFI] IP Address: ");
		Serial.println(WiFi.localIP());
	} else {
		Serial.println("[WIFI] WiFi Failed to Connect. Rebooting...");
		ESP.restart();
	}

	if (mdns.init(MDNS_HOSTNAME) > -1) {
		Serial.print("[WIFI] mDNS initialized: ");
		Serial.print(MDNS_HOSTNAME);
		Serial.println(".local");
	} else {
		Serial.println("[WIFI] mDNS Failed!");
	}
}

void loop()
{
}