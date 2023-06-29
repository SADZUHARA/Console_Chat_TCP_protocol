// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Message.h"
#include <iostream>
#include <ctime>
#include <locale>
#include <fstream>

Message::Message() = default;

Message::Message(const std::string& text, const std::string& sender, const std::string& recipient) :
	_text(text),
	_sender(sender),
	_recipient(recipient)
{
	
	std::time_t t = std::time(nullptr);
	char str[100];
	
	if (std::strftime(str, sizeof(str), "%A %c", std::localtime(&t))) {
		_time = str;
	}
	
}

const std::string Message::getText()const
{
	return _text;
}

const std::string& Message::getSender()const
{
	return _sender;
}

const std::string& Message::getRecipient()const 
{	
	return _recipient;
}

std::string Message::getTime()const
{	
	return _time;
}


std::fstream& operator>>(std::fstream& is, Message& mess){

	
	std::getline(is, mess._text);
	std::cout << mess._text << std::endl;
	
	std::getline(is, mess._sender);
	std::cout << mess._sender << std::endl;
	
	std::getline(is, mess._recipient);
	std::cout << mess._recipient << std::endl;
	
	std::getline(is, mess._time);
	std::cout << mess._time << std::endl;
	
	return is;

}

std::fstream& operator<<(std::fstream& os, const Message& mess) {

	os << mess._text;
	os << '\n';
	os << mess._sender;
	os << '\n';
	os << mess._recipient;
	os << '\n';
	os << mess._time;
	os << '\n';
	return os;

}