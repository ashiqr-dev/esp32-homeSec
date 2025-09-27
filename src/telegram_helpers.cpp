#include "telegram_helpers.h"

void TelegramService::init(const char *token)
{
	client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
	bot = UniversalTelegramBot(token, client);
}

TelegramMessage TelegramService::getNextMessage()
{
	TelegramMessage msg;

	int numNew = bot.getUpdates(bot.last_message_received + 1);
	if (numNew > 0)
	{
		msg.chat_id = bot.messages[0].chat_id;
		msg.text = bot.messages[0].text;
		msg.from = bot.messages[0].from_name;
	}

	return msg;
}

bool TelegramService::sendMessage(String chat_id, String message)
{
	Serial.print("[BOT ] Sending text \"");
	Serial.print(message);
	Serial.print("\" to chat id ");
	Serial.println(chat_id);
	return bot.sendMessage(chat_id, message, "");
}

bool TelegramService::resolveCommand(String chat_id, String msg, String sender_name)
{
	Serial.println("[BOT ] Message recieved!:");
	String tmp = "[BOT ] From ";
	tmp += sender_name;
	tmp += ": \"";
	tmp += msg;
	tmp += "\" (Chat ID: ";
	tmp += chat_id;
	tmp += ")\n";
	Serial.println(tmp);

	if (msg == "/start")
	{
		String welcome = "Welcome, " + sender_name + ".\n";
		welcome += "Use the commands listed below.\n\n";
		welcome += "/arm - ARM the security system\n";
		welcome += "/disarm - DISARM the security system\n";
		welcome += "/status - Check current system status\n";
		welcome += "/enable - Enable a sensor\n";
		welcome += "/disable - Disable a sensor\n";
		welcome += "/enableall - Enable ALL sensors\n";
		welcome += "/disableall - Disable ALL sensors\n";
		welcome += "/config - Change system configurations\n";
		welcome += "/list - List enabled sensors\n";
		welcome += "/setpin - Set new pin for factory reset.\n";
		welcome += "/start - Show this help menu\n";
		return bot.sendMessage(chat_id, welcome, "");
	}
	else if (msg == "/arm")
	{
		// Set arm true here
	}
	else if (msg == "/disarm")
	{
		// Set arm false here
	}
	else if (msg == "/status")
	{
		// Reply with status
	}
	else if (msg == "/enable")
	{
		// Enable here
	}
	// Add more here
	else if (msg.startsWith("/"))
	{
		return bot.sendMessage(chat_id, "Unknown command!", "");
	}

	return true;
}

// Returns a string containing only ASCII characters in the printable range
String sanitize(const String &input, size_t maxLen)
{
	String result;
	for (size_t i = 0; i < input.length() && result.length() < maxLen; ++i)
	{
		char c = input[i];
		if (c >= 32 && c <= 126)
		{
			result += c;
		}
	}
	return result;
}