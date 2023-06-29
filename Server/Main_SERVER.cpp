#include "Chat.h"
#include "Message.h"
#include "User.h"
#include "BadLogin.h"
#include "BadPassword.h"
#include <iostream>
#include <ctime>


int main() {
	
	Chat ch;
	
	const char* file_u = "Users.txt";
	const char* file_m = "Messeges.txt";
	

	ch.read_map_us(file_u);
	ch.read_map_mess(file_m);
	
	Chat* contain = ch.ChatStart();
		
	std::cout << "check contain some element\n";
	
	if (contain->isontheList(contain->getVusers(), "name", "Roman"))		
		
		std::cout << "Ura! isontheList found Roman! \n";
	else std::cout << "In _users Nothing not found! \n";
	
	if (contain->isontheList(contain->getVmessages(), "text", "Roman to Roman"))
		
		std::cout << "Ura! isontheList found \"Roman to Roman\"! \n";
	else std::cout << "In messages Nothing not found! \n";
	
	std::cout << std::endl;
	
	ch.write_map_us(file_u);
	ch.write_map_mess(file_m);
	
	ch.showAllMessages();
	
	std::cout << std::endl;
	
	std::cout << "Done!!!";

	return 0;

}