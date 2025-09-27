#pragma once
#include "secrets.h"
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

struct TelegramMessage
{
	String chat_id;
	String text;
	String from;
};

String sanitize(const String &input, size_t maxLen = 64);

class TelegramService
{
public:
	TelegramService() = default;
	void init(const char *token);
	TelegramMessage getNextMessage();
	bool sendMessage(String chat_id, String message);
	bool resolveCommand(String chat_id, String msg, String user_name);

private:
	WiFiClientSecure client;
	UniversalTelegramBot bot{"", client};
};
