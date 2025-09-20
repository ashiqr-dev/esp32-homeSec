#include "config.h"
#include "secrets.h"
#include "telegram_helpers.h"
#include "wifi_helpers.h"

WiFiService wifi;
mDNSService mdns;
OTAService ota;
TelegramService telegram;

void setup()
{
	Serial.begin(115200);
	Serial.write("\n");

	Serial.print("[WIFI] Connecting to WiFi");
	if (wifi.connect(WIFI_SSID, WIFI_PASS) == 0)
	{
		Serial.println("\n[WIFI] WiFi Connected!");
		Serial.print("[WIFI] IP Address: ");
		Serial.println(WiFi.localIP());
	}
	else
	{
		Serial.println("\n[WIFI] WiFi Failed to Connect. Rebooting...");
		ESP.restart();
	}

	ota.init(OTA_HOSTNAME, OTA_PASS);
	Serial.println("[OTA ] OTA Ready");

	if (mdns.init(MDNS_HOSTNAME) == 0)
	{
		Serial.print("[MDNS] mDNS Ready: ");
		Serial.print(MDNS_HOSTNAME);
		Serial.println(".local");
	}
	else
	{
		Serial.println("[MDNS] Initialization failed!");
	}

	telegram.init(BOT_TOKEN);
	Serial.println("[BOT ] Telegram bot initalized!");
}

void loop()
{
	ota.handle();

	TelegramMessage msg = telegram.getNextMessage();
	if (msg.chat_id != "" && msg.text != "")
	{
		if(!telegram.resolveCommand(msg.chat_id, msg.text, msg.from))
		{
			Serial.print("[BOT ] Message failed to send!");
		}
	}
}