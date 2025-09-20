#include "wifi_helpers.h"

int8_t WiFiService::connect(const char *ssid, const char *pass)
{
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, pass);

	for (int8_t i = 0; i < 20; i++) {
		if (WiFi.status() == WL_CONNECTED) {
			return 0;
		}
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