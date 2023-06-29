#include "Chat.h"
#include "BadLogin.h"
#include "BadPassword.h"
//#include <iostream>
//#include <set>
//#include <iomanip>
//#include <unistd.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <string.h>





Chat::Chat(){

	_activeUser = nullptr;
	_mess_count = 0;
	std::shared_ptr <User> newUser = std::make_shared <User>("to All", "to All", "0");
	_map_us.emplace(make_pair("to All", newUser));
}

Chat::~Chat() = default;


bool Chat::createNewUser(const std::string& name, const std::string& login, const std::string& password){

	if (isLoginExist(login)) {
		std::cout << "User with login " << login << " is already exists." << std::endl;
		return false;
	}
	std::shared_ptr <User> newUser = std::make_shared <User>(name, login, password);
	_map_us.emplace(make_pair (login, newUser));
	setActiveUser(newUser);

	return true;
}


void Chat::setActiveUser(const std::shared_ptr<User>& user){

	if (user != nullptr)
		std::cout << "Hello, " << user->getName() << "! Nice to see you!" << std::endl;
	_activeUser = user;
}


void Chat::login(const std::string& login, const std::string& password){

	bool found = isLoginExist(login);
	if (!found)
		throw BadLogin();

	map_us_iter it = _map_us.find(login);	
	if (it == _map_us.end())                         // скорректировано под анализатор
		return;
		
	if (it->second->getPassword() == password) {
		setActiveUser(it->second);            
	}
	else
		throw BadPassword();
	
	
}


void Chat::Write(const std::string& text, std::shared_ptr<User> recipient){

	std::shared_ptr <Message> shp_mess = std::make_shared<Message>(text, getActiveUser()->getLogin(),
		recipient->getLogin());
	
	_map_mess.emplace(make_pair(_mess_count,shp_mess));
	getActiveUser()->get_num_mess().insert(_mess_count);
	recipient->get_num_mess().insert(_mess_count);

	_mess_count++;
}


void Chat::writeToAll(const std::string& text){

	std::shared_ptr <Message> shp_mess = std::make_shared<Message>(text, getActiveUser()->getLogin(),
		"to All");	
	_map_mess.emplace(make_pair(_mess_count, shp_mess));
	getActiveUser()->get_num_mess().insert(_mess_count);
	_mess_count++;
	
	for (auto& recipient : _map_us)
	{
		if (recipient.second->getLogin() != getActiveUser()->getLogin())
		{
			std::shared_ptr <Message> shp_mess = std::make_shared<Message>(text, getActiveUser()->getLogin(),
				recipient.second->getLogin());
			_map_mess.emplace(make_pair(_mess_count, shp_mess));			
			recipient.second->get_num_mess().insert(_mess_count);
		    _mess_count++;
		}
	}
}


bool Chat::isLoginExist(const std::string& login){

	map_us_iter it = _map_us.find(login);
	{
		if (it != _map_us.end())
			return true;
	}
	return false;
}


std::shared_ptr<User> Chat::getActiveUser(){

	return _activeUser;
}

void Chat::showMenuAddMessege()
{
	std::cout << "Choose recipient mode : 1 - to One , 2 - to All, 3 - Exit \n";
}

std::shared_ptr<User> Chat::getUser(const std::string& login)
{
	for (auto& user : _map_us)
		if (user.second->getLogin() == login)				
			return user.second;    
		
		return std::make_shared <User>();
}


void Chat::showAllUserMesseges(std::shared_ptr<User> shpu){

	if (shpu->getLogin() == "\0")
	{
		std::cout << "Bad recipient, choose right recipient!\n";
		return;
	}
	
	std::cout << shpu->getName() << ", your all messages are : " << std::endl << std::endl;

	for (const auto& i : shpu->get_num_mess()){  
		
		map_mass_iter it = _map_mess.find(i);
		if (it == _map_mess.end())
			continue;
		std::shared_ptr <Message> message = it->second;

			std::cout << getNameByLogin(message->getSender()) << std::setw(35) << message->getTime() << std::setw(30)
				<< "--->" << std::setw(30)
				<< getNameByLogin(message->getRecipient()) << std::endl << std::endl << std::setw(20) << "\" "
				<< message->getText() << " \""
				<< std::endl << std::endl;
	}

}

std::ostream& operator<< (std::ostream& os, Chat& ch){

	int count(0);
	for (auto& user : ch._map_us)
	{
		os << std::setw(3) << " < " << user.second->getName() << " > ";
		count++;
		if (!(count % 6))
			os << std::endl;
	}
	return os;
}

void Chat::showAllLogin(){

	for (auto& user : _map_us)
	{
		int count(0);
		std::cout << std::setw(3) << " < " << user.second->getLogin() << " > ";
		count++;
		if (!(count % 6))
			std::cout << std::endl;
	}

}


bool Chat::isUnicName(const std::string& name){

	int count(0);
	
	for (auto& user : _map_us)
	{
		
		if (user.second->getName() == name)
			count++;
	}
	
	if (count == 1)
		return true;
	
	else 
		return false;

}

const std::string Chat::getNameByLogin(const std::string& login){

	for (auto& user : _map_us)
	{

		if (user.second->getLogin() == login)
			return user.second->getName();

	}
	std::cout << "Name by " << login << " is not found!\n";
	return "\0";		
	
}

const std::string Chat::getLoginByName(const std::string& name){
	
	for (auto& user : _map_us)
	{

		if (user.second->getName() == name)
			return user.second->getLogin();

	}
	std::cout << "Login by " << name << "is not found!\n";
	return "\0";
}


bool Chat::isontheList(const std::string& name){
	
	for (auto& tempname : _map_us)
	{
		if (tempname.second->getName() == name)
			return true;
	}
	std::cout << "bad recipient, try again!\n";
	return false;
}

void Chat::showAllUsers() const {
	
	std::cout << "showall" << std::endl;
	for (auto& user : _map_us)
	{
		std::cout << user.second->getName() << " " << std::endl;
	}
}

void Chat::showAllMessages()const {
	
	for (auto& pairmass : _map_mess)
	{
		std::cout << pairmass.second->getText();
		std::cout << std::setw(30);
		std::cout << pairmass.second->getSender();
		std::cout << std::setw(40);
		std::cout << pairmass.second->getRecipient();
		std::cout << std::endl;
	}
}


void Chat::write_map_us(const char* file) {

    std::fstream finout;
	finout = std::fstream(file, std::ios::in | std::ios::out);
	if (!finout) 
		
           finout = std::fstream(file, std::ios::in | std::ios::out | std::ios::trunc);
	
	if (finout) {

	int count =  _map_us.size();
	finout << count;
	finout << '\n';	
	map_us_iter it = _map_us.begin() ;
	while (it != _map_us.end())
	     {
		    finout << it->first <<'\n';
			finout << *it->second << ' ';
			it++;

		 }  		
		
	}
	else
	{
		std::cout << "Could not open file Users.txt !" << '\n';
		return;

	}


}

void Chat::read_map_us(const char* file){

    std::fstream finout;
	finout = std::fstream(file, std::ios::in | std::ios::out);
	if (!finout) 
		     std::cout << "Not finout Users!\n";           
	
	if (finout) {
     
	int count(0); 
	finout >> count;
	

	for (int i = 0; i < count; i++)
	     {
			User us ("SPACE","SPACE","0");
			std::string log;
			while (finout.peek() == '\n' || finout.peek() == ' ')
			finout.get(); 
			std::getline(finout, log);
			finout >> us;
			std::shared_ptr <User> newUser = std::make_shared <User>(us.getName(), us.getLogin(), us.getPassword());			
			
			for (auto& gnm : us.get_num_mess())			      
			      newUser->get_num_mess().emplace(gnm); 
			_map_us.emplace(make_pair (log, newUser));
			
			

		 }     
	}
	else
	{
		std::cout << "Could not open file Users.txt !" << '\n';
		return;

	}


}

void Chat::write_map_mess(const char* file) {

    std::fstream finout;
	finout = std::fstream(file, std::ios::in | std::ios::out);
	if (!finout) 
		
           finout = std::fstream(file, std::ios::in | std::ios::out | std::ios::trunc);
	
	if (finout) {

	finout << _mess_count;
	finout << '\n';
	int count =  _map_mess.size();
	finout << count;
	finout << '\n';	
	map_mass_iter it = _map_mess.begin() ;
	while (it != _map_mess.end())
	     {
		    finout << it->first << ' ';
		    finout << *it->second;         // подумать
			it++;

		 }  		
		
	}
	else
	{
		std::cout << "Could not open file Messages.txt !" << '\n';
		return;

	}


}

void Chat::read_map_mess(const char* file){

    std::fstream finout;
	finout = std::fstream(file, std::ios::in | std::ios::out);
	if (!finout) 
		  std::cout << "Not finout Messages!\n";
          
	
	if (finout) {
     
	finout >> _mess_count;
	int count(0); 
	finout >> count;	

	for (int i = 0; i < count; i++)
	     {
			Message mess;
			int mc;
			finout >> mc;
			while (finout.peek() == '\n' || finout.peek() == ' ')
			       finout.get();
			finout >> mess;
			std::shared_ptr <Message> shp_mess = std::make_shared<Message>(mess.getText(), mess.getSender(), mess.getRecipient());	
	        shp_mess->getTime() = mess.getTime();
			_map_mess.emplace(make_pair(mc, shp_mess));		

		 }     
	}
	else
	{
		std::cout << "Could not open file users.txt !" << '\n';
		return;

	}


}


void Chat::s_send(int connection, char* i_message) {                                      //SERVER

	
	//memset(message, 0, MESSAGE_LENGTH);
	//std::cout << "Enter the message you want to send to the client: " << std::endl;
	//std::cin >> message;
	ssize_t bytes = write(connection, i_message, MESSAGE_LENGTH);
	// Если передали >= 0  байт, значит пересылка прошла успешно
	if (bytes >= 0) {
		//std::cout << "Data successfully sent to the client.!" << std::endl;
	}

}

void Chat::s_get(int connection, char* i_message) {                                              //SERVER

	
	read(connection, i_message, MESSAGE_LENGTH); // MESSAGE_LENGTH вместо sizeof - это одно и тоже получается
	if (strncmp("end", i_message, 3) == 0) {
		std::cout << "Client Exited." << std::endl;
		std::cout << "Server is Exiting..!" << std:: endl;
		return;
	}
	//std::cout << "Data received from client: " << i_message << std::endl;

}

void Chat::sendAllUserMesseges(int connection, char* i_message,std::shared_ptr<User> shpu) {      // SERVER

	if (shpu->getLogin() == "\0")
	{
		std::cout << "* Bad recipient, choose right recipient!\n";
		std::string string_imess = "* Bad recipient, choose right recipient!\n";
		strcpy(i_message, string_imess.c_str());
		s_send(connection, i_message);
		//std::cout << i_message << std::endl;
		bzero(i_message, MESSAGE_LENGTH);
		return;
	}

	std::cout << shpu->getName() << ", your all messages are : " << std::endl << std::endl;
	std::string string_imess = shpu->getName() + ", your all messages are : \n\n";
	strcpy(i_message, string_imess.c_str());
	s_send(connection, i_message);
	bzero(i_message, MESSAGE_LENGTH);		
	
	for (const auto& i : shpu->get_num_mess()) {
		
		map_mass_iter it = _map_mess.find(i);
		if (it == _map_mess.end())
			continue;
		std::shared_ptr <Message> message = it->second;

		std::string string_imess = getNameByLogin(message->getSender()) + "  " +
		message->getTime() + "  --->          "
		+ message->getRecipient() + "\n" + message->getText() + "\n";
		
		strcpy(i_message, string_imess.c_str());
		s_send(connection, i_message);
		bzero(i_message, MESSAGE_LENGTH);	
			
	}	
}

void Chat::sendAll_names(int connection, char* i_message) {

	std::string string_imess = " * ";

	for (auto& user : _map_us)
	{
		int count(0);
		std::cout << std::setw(3) << " < " << user.second->getName() << " > ";
		string_imess += " < " + user.second->getName() + " > ";
		
		count++;
		if (!(count % 6)) {
			std::cout << std::endl;
			string_imess += "\n";
			
		}
	}
	
	strcpy(i_message, string_imess.c_str());
	s_send(connection, i_message);
	//std::cout << i_message << std::endl;
	bzero(i_message, MESSAGE_LENGTH);
}
void Chat::sendAll_login(int connection, char* i_message) {
	
	std::string string_imess = " * ";

	for (auto& user : _map_us)
	{
		int count(0);
		std::cout << std::setw(3) << " < " << user.second->getLogin() << " > ";
		string_imess += " < " + user.second->getLogin() + " > ";

		count++;
		if (!(count % 6)) {
			std::cout << std::endl;
			string_imess += "\n";

		}
	}

	strcpy(i_message, string_imess.c_str());
	s_send(connection, i_message);
	//std::cout << i_message << std::endl;
	bzero(i_message, MESSAGE_LENGTH);
}
