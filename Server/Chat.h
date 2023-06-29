#pragma once

#include <string>
#include <memory>
#include <iostream>
#include "User.h"
#include "Message.h"
#include <iomanip>
#include <typeinfo>
#include <map>
#include <set>
#include <fstream>
//#include <iomanip>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>


#define MESSAGE_LENGTH 1024 
#define PORT 7777

typedef std::map<std::string, std::shared_ptr <User>>::iterator map_us_iter;
typedef std::map<int, std::shared_ptr <Message>>::iterator map_mass_iter;

class Chat
{
private:
	
	std::shared_ptr <User> _activeUser;
	std::map<std::string, std::shared_ptr <User>> _map_us;            
	std::map<int, std::shared_ptr<Message>> _map_mess;                
	size_t _mess_count;


public:

	Chat();
	~Chat();
	std::size_t getMessCount() { return _mess_count; }
	bool createNewUser(const std::string& name, const std::string& login, const std::string& password);
	void setActiveUser(const std::shared_ptr<User>& user);
	void login(const std::string& login, const std::string& password);
	void Write(const std::string& text, std::shared_ptr<User>);
	void writeToAll(const std::string& text);
	bool isLoginExist(const std::string& login);
	std::shared_ptr <User> getActiveUser();
	std::shared_ptr <User> getUser(const std::string& login);
	void showMenuAddMessege();
	void showAllUserMesseges(std::shared_ptr <User>);
	friend std::ostream& operator<< (std::ostream& os, Chat&);
	void showAllLogin();
	bool isUnicName(const std::string& name);
	const std::string getNameByLogin(const std::string& login);
	const std::string getLoginByName(const std::string& name);
	bool isontheList(const std::string& name);		
	void showAllUsers() const;
	void showAllMessages() const;
	Chat* ChatStart();
	void read_map_us(const char*);
	void write_map_us(const char*);
	void read_map_mess(const char*);
	void write_map_mess(const char*);
	void s_send(int, char[]);	
	void s_get(int, char[]);	
	void sendAllUserMesseges(int, char[],std::shared_ptr<User> shpu);	
	void sendAll_names(int, char[]);
	void sendAll_login(int, char[]);
	
	
	// test function and template (there are the notes in main()---------------------------------------------------		
	
	const std::map<std::string, std::shared_ptr <User>> getVusers() const { return _map_us; }
	const std::map<int, std::shared_ptr<Message>> getVmessages() const  { return _map_mess; }	
	
	template <typename Key, typename T>
	bool isontheList(const std::map<Key, T>&, const std::string& Element, const std::string& fromElement);
};


template <typename Key, typename T>
bool Chat::isontheList(const std::map<Key,T>& vecshptr, const std::string& Element, const std::string& fromElement)
{

	if (typeid(T).name() == typeid(std::shared_ptr<User>).name())
	{
		if (Element == "name")
		{
			for (auto& tempname : getVusers())
			{
				if (tempname.second->getName() == fromElement)
					return true;
			}
			std::cout << "not : \"" << fromElement << "\" in the list \n";
			return false;

		}
		else
		{
			std::cout << "bad element, try again!\n";
			
		}

		if (Element == "login")
		{
			for (auto& tempname : getVusers())
			{
				if (tempname.second->getLogin() == fromElement)
					return true;
			}
			std::cout << "not : \"" << fromElement << "\" in the list \n";
			return false;

		}
		else
		{
			std::cout << "bad element, try again!\n";
			
		}
	}

	
	if (typeid(T).name() == typeid(std::shared_ptr<Message>).name())
	{
		if (Element == "text")
		{
			for (auto& tempelem : getVmessages())
			{
				if (tempelem.second->getText() == fromElement)
					return true;
			}
			std::cout << "not : \" " << fromElement << "\" in the list \n";
				return false;

		}
		else
		{
			std::cout << "bad element, try again!\n";
			return false;
		}	

	}
	
	std::cout << "Nothing foud at all\n";

	return false;
}
 
 
