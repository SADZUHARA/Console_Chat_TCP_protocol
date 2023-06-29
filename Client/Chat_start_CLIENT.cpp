#include "Chat.h"
#include "Message.h"
#include "User.h"
#include "BadLogin.h"
#include "BadPassword.h"
#include <iostream>
#include <ctime>


Chat* Chat::ChatStart() {
	int socket_file_descriptor, connection;
    struct sockaddr_in serveraddress, client;
	char i_message[MESSAGE_LENGTH];
	bzero(i_message, MESSAGE_LENGTH);
	std::string string_imess;
	
	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        std::cout << "Creation of Socket failed!" << std::endl;
        exit(1);
    }
    
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    serveraddress.sin_port = htons(PORT);
    
    serveraddress.sin_family = AF_INET;
    
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        std::cout << "Connection with the server failed.!" << std::endl;
        exit(1);                                                                          
	}                                                                                     

	std::cout << "Hello! Let's start!" << std::endl;
	
	while (1) {
			bzero(i_message, MESSAGE_LENGTH);
			read(socket_file_descriptor, i_message, sizeof(i_message));
			if (strncmp("Good luck, bye", i_message, 14) == 0) {
				std::cout << "Client Exited." << std::endl;
				std::cout << "Server is Exiting..!" << std::endl;
				break;
			}			
			//std::cout << "Data received from the SERVER: " << i_message << std::endl;
			std::cout << i_message << std::endl;
			string_imess = i_message;
			if (std::string::npos == string_imess.find("*")) 			                                      
					continue;                                                                   
				 
			else                 
			   {  bzero(i_message, MESSAGE_LENGTH);		
			
			//std::cout << "Enter the message you want to send to the SERVER: " << std::endl;
			//std::cout << std::endl;
			std::getline (std::cin,string_imess);
			strcpy(i_message,string_imess.c_str());
			ssize_t bytes = write(socket_file_descriptor, i_message, sizeof(i_message));
			
			    if (bytes >= 0) {
				//std::cout << "Data successfully sent to the SERVER.!" << std::endl;}
			    }
	        }
	    }
	
	close(socket_file_descriptor);


	std::cout << std::endl;
	std::cout << "Done Chat_start_CLIENT!";

	return nullptr;
}