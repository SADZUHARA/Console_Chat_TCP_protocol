#include "Chat.h"
#include "Message.h"
#include "User.h"
#include "BadLogin.h"
#include "BadPassword.h"
//#include <iostream>
#include <ctime>
//#include <string.h>


Chat* Chat::ChatStart() {
	struct sockaddr_in serveraddress, client;
	socklen_t length;
	int sockert_file_descriptor, connection, bind_status, connection_status;
	char i_message [MESSAGE_LENGTH];
	bzero(i_message, MESSAGE_LENGTH);
	std::string string_imess;

	
		
		sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
		if (sockert_file_descriptor == -1) {
			std::cout << "Socket creation failed.!" << std::endl;
			exit(1);
		}
		// 
		serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
		
		serveraddress.sin_port = htons(PORT);
		
		serveraddress.sin_family = AF_INET;
		
		bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
		if (bind_status == -1) {
			std::cout << "Socket binding failed.!" << std::endl;
			exit(1);
		}
		 
		connection_status = listen(sockert_file_descriptor, 5);                               
		if (connection_status == -1) {                                                        
			std::cout << "Socket is unable to listen for new connections.!" << std:: endl;    
			exit(1);                                                                          
		}                                                                                    
		else {                                                                                
			std::cout << "Server is listening for new connection: " << std:: endl;            
		}                                                                                    
		length = sizeof(client);                                                              
		connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);     
		if (connection == -1) {                                                               
			std::cout << "Server is unable to accept the data from client.!" << std:: endl;   
			exit(1);                                                                          
		}                                                                                     

	std::cout << "Hello! Let's start!" << std::endl;

	char choose;                                                                            
	while (true)																			
	{
		while (getActiveUser() == nullptr) {                                                 
			std::cout << "* Would you like login(enter 'L'), register(enter 'R') or quit(enter 'Q')?" << std::endl;
			//string_imess = "* Hello! Let's start!\n";
			string_imess = "* Would you like login(enter 'L'), register(enter 'R') or quit(enter 'Q'? \n"; 
			strcpy(i_message,string_imess.c_str());						 
			
			//std::cout << i_message << std::endl;
			s_send(connection, i_message);					//-->								
			bzero(i_message, MESSAGE_LENGTH);												
			
			std::string selection;			// <--
			s_get(connection, i_message);                                                    
			selection = i_message;                                                           
			//std::cout << i_message << std::endl;
			bzero(i_message, MESSAGE_LENGTH);                                                
			
			if (selection.size() > 1) {                                                      
				std::cout << "I think you mean '" << selection.at(0) << std::endl;           
				string_imess = "I think you mean '" + std::to_string (selection.at(0)) + "'\n"; 
				strcpy(i_message, string_imess.c_str());						 
				//memcpy (i_message, string_imess.c_str(), string_imess.size())
				//std:: cout << i_message << std::endl;
				s_send(connection, i_message);													
				bzero(i_message, MESSAGE_LENGTH);												
			}
			switch (selection.at(0))
			{
			case 'R':
			{
				std::string name, login, password;
				std::cout << "* Enter login ?" << std::endl;				                                                  
				string_imess = "* Enter login ?";
				strcpy(i_message, string_imess.c_str());                        
			    s_send(connection, i_message);                                
				//std::cout << i_message << std::endl;                                       
				bzero(i_message, MESSAGE_LENGTH);                                          
				
				s_get(connection, i_message);                                                
				login = i_message;                                                           
				std::cout << i_message << std::endl;                                         
				bzero(i_message, MESSAGE_LENGTH);                                            
				
				if (isLoginExist(login)) {                                                   
					std::cout << "User with login " << login << " is already exists." << std::endl;
					string_imess = "User with login " + login + " is already exists.\n";    
					strcpy(i_message, string_imess.c_str());               
					s_send(connection, i_message);                                            
					//std::cout << i_message << std::endl;                                     
					bzero(i_message, MESSAGE_LENGTH);                                         
					break;                                                                   
				}			
				std::cout << "* Enter password " << std::endl;                                   
				string_imess = "* Enter password ";
				strcpy(i_message, string_imess.c_str());
				s_send(connection, i_message);
				//std::cout << i_message << std::endl;
				bzero(i_message, MESSAGE_LENGTH);

				s_get(connection, i_message);                                                
				std::cout << i_message << std::endl;                                         
				password = i_message;                                                        				
				bzero(i_message, MESSAGE_LENGTH);                                            
				
				std::cout << "* Enter name " << std::endl;				
				string_imess = "* Enter name ";
				strcpy(i_message, string_imess.c_str());
				s_send(connection, i_message);
				//std::cout << i_message << std::endl;
				bzero(i_message, MESSAGE_LENGTH);
				
				s_get(connection, i_message);                                                
				std::cout << i_message << std::endl;                                         
				name = i_message;                                                            
				bzero(i_message, MESSAGE_LENGTH);                                            
				createNewUser(name, login, password);                                        
				break;
			}
			case 'L':
			{
				std::string login, password;
				std::cout << "* Enter login " << std::endl;				                                                        
				string_imess = "* Enter login ";
				strcpy(i_message, string_imess.c_str());
				s_send(connection, i_message);
				//std::cout << i_message << std::endl;
				bzero(i_message, MESSAGE_LENGTH);
				
				s_get(connection, i_message);                                                
				login = i_message;                                                           
				std::cout << i_message << std::endl;                                         
				bzero(i_message, MESSAGE_LENGTH);                                                                                 
				
				std::cout << "* Enter password " << std::endl;            
				string_imess = "* Enter password ";
				strcpy(i_message, string_imess.c_str());
				s_send(connection, i_message);
				//std::cout << i_message << std::endl;
				bzero(i_message, MESSAGE_LENGTH);

				s_get(connection, i_message);                                                
				std::cout << i_message << std::endl;                                         
				password = i_message;                                                        				
				bzero(i_message, MESSAGE_LENGTH);                                           
				
				int tries = 3;

				try {
					Chat::login(login, password);                                            
					std::cout << std::endl;                                                 
					sendAllUserMesseges(connection, i_message, getActiveUser());             
					
				}
				catch (BadLogin& e) {
					std::cout << e.what() << std::endl;                                      
					string_imess = e.what();                                                  
					strcpy(i_message, string_imess.c_str());                
					s_send(connection, i_message);                                            
					//std::cout << i_message << std::endl;                                     
					bzero(i_message, MESSAGE_LENGTH);                                        
					
					break;
				}
				catch (BadPassword& e) {
					std::cout << e.what() << std::endl;
					string_imess = e.what();                                                  
					strcpy(i_message, string_imess.c_str());                
					s_send(connection, i_message);                                           
					//std::cout << i_message << std::endl;                                     
					bzero(i_message, MESSAGE_LENGTH);                                        
					
					while (--tries > 0) {
						try {
							std::cout << "* Enter password (" << tries << " tries left) " << std::endl;
							string_imess = "* Enter password (" + std::to_string (tries) + " tries left) ";                                                 // SERVER 
							strcpy(i_message, string_imess.c_str());               
							s_send(connection, i_message);                                            
							//std::cout << i_message << std::endl;                                     
							bzero(i_message, MESSAGE_LENGTH);							
							
							s_get(connection, i_message);                                    
							std::cout << i_message << std::endl;
							password = i_message;                                            
							bzero(i_message, MESSAGE_LENGTH);                                
							
							Chat::login(login, password);                                    
							std::cout << std::endl;                                            
							sendAllUserMesseges(connection, i_message, getActiveUser());     							
							std::cout << std::endl;       
						}
						catch (BadPassword& e) {
							std::cout << e.what() << std::endl;
							string_imess = e.what();                                                  
							strcpy(i_message, string_imess.c_str());                
							s_send(connection, i_message);                                            
							//std::cout << i_message << std::endl;                                     
							bzero(i_message, MESSAGE_LENGTH);                                        
						}
					}
					break; //  switch case L catch
				}    // catch (BadPassword& e)
				break; //    switch case L   catch         
			}
			case 'Q':
				std::cout << "Good luck, bye!" << std::endl;
				string_imess = "Good luck, bye!";                                                 
				strcpy(i_message, string_imess.c_str());
				s_send(connection, i_message);
				//std::cout << i_message << std::endl;
				bzero(i_message, MESSAGE_LENGTH);
				return this;
			default:
				std::cout << "Enter L, R or Q" << std::endl;				
				string_imess = "* Enter L, R or Q";
				strcpy(i_message, string_imess.c_str());
				s_send(connection, i_message);
				//std::cout << i_message << std::endl;
				bzero(i_message, MESSAGE_LENGTH);
				break;
			}
		}

		showMenuAddMessege(); // 1 - One, 2 - All, 3 - Exit	  
		std::cout << "* Choose recipient mode : 1 - to One , 2 - to All, 3 - Exit\n";
		string_imess = "* Choose recipient mode : 1 - to One , 2 - to All, 3 - Exit\n";
		strcpy(i_message, string_imess.c_str());
		s_send(connection, i_message);
		//std::cout << i_message << std::endl;
		bzero(i_message, MESSAGE_LENGTH);
		
		s_get(connection, i_message);         
		std::cout << i_message << std::endl;
		choose = i_message[0];										           
		bzero(i_message, MESSAGE_LENGTH);										          
		
		std::string message;															
		std::string name_recipient;														 
		std::string log_recipient;	
		
		switch (choose)
		{
		case '1':		
		    {
		      std::cout << "You are : " << getActiveUser()->getName() << std::endl;			  
			  string_imess = "You are : " + getActiveUser()->getName() + "\n";
			  std::cout << "Choose the recipient: \n";
			  string_imess += "Choose the recipient: \n";
			  strcpy(i_message, string_imess.c_str());
			  s_send(connection, i_message);
			  //std::cout << i_message << std::endl;
			  bzero(i_message, MESSAGE_LENGTH);
			  
			  std::cout << *this << std::endl;
			  sendAll_names(connection, i_message);  
			  		  
			  
			  s_get(connection, i_message);
			  std::cout << i_message << std::endl;
			  name_recipient = i_message;			  
			  bzero(i_message, MESSAGE_LENGTH);
			  
			  if (!(isontheList(name_recipient)))	     	  
				    continue;			    

			  if (!isUnicName(name_recipient)) // 
			    {			    
			      std::cout << "The name is not unique, choose name by login list : \n";
				  string_imess = "The name is not unique, choose name by login list : \n";
				  strcpy(i_message, string_imess.c_str());
				  s_send(connection, i_message);
				  //std::cout << i_message << std::endl;
				  bzero(i_message, MESSAGE_LENGTH);
				  showAllLogin();
			    	std::cout << std::endl;
				  sendAll_login(connection, i_message);    
					std::string login_from_list;
	    				     			
					
					s_get(connection, i_message);
					std::cout << i_message << std::endl;
					login_from_list = i_message;
					bzero(i_message, MESSAGE_LENGTH);				
					
					if (!(isontheList(getNameByLogin(login_from_list))))
						continue;
					log_recipient = login_from_list;	
				
				
	    		} else
			      log_recipient = getLoginByName(name_recipient);
			      
				  std::cout << std::endl;
			      std::cout << "The logrecipient is :" << log_recipient << std::endl;
			      std::cout << std::endl;
			      std::cout << "write a message\n";
				  string_imess = "* The logrecipient is : " + log_recipient + "\nwrite a message\n";
				  strcpy(i_message, string_imess.c_str());
				  s_send(connection, i_message);
				  //std::cout << i_message << std::endl;
				  bzero(i_message, MESSAGE_LENGTH);				  
			      std::cout << std::endl;
				 
				  s_get(connection, i_message);
				  std::cout << i_message << std::endl;
				  message = i_message;
				  bzero(i_message, MESSAGE_LENGTH);

				  Write(message, getUser(log_recipient));
				  
				  std::time_t t = std::time(nullptr);
				  char str[100];
				  std::strftime(str, sizeof(str), "%A %c", std::localtime(&t));				  
			      std::cout << getActiveUser()->getName() << std::setw(35) << str <<std::setw(30) 
			    	<< "--->"<< std::setw(30)
			    	<< getNameByLogin(log_recipient) << std::endl << std::endl << std::setw(15) << "\" " << message << " \""
			    	<< std::endl << std::endl;
				  
				  string_imess = getActiveUser()->getName() + "        " + str + "       --->       " + getNameByLogin(log_recipient) 
					             + "\n\n\" " + message + " \"";
				  strcpy(i_message, string_imess.c_str());
				  s_send(connection, i_message);
				  //std::cout << i_message << std::endl;
				  bzero(i_message, MESSAGE_LENGTH);

		    }
			continue;

		case '2':
		    {
		     	std::cout << "* You are : " << getActiveUser()->getName() << std::endl;
		    	std::cout << "write a message : \n";
				string_imess = "* You are : " + getActiveUser()->getName() + "\nwrite a message : \n";
				strcpy(i_message, string_imess.c_str());
				s_send(connection, i_message);
				//std::cout << i_message << std::endl;
				bzero(i_message, MESSAGE_LENGTH);
				
				s_get(connection, i_message);
				std::cout << i_message << std::endl;
				message = i_message;
				bzero(i_message, MESSAGE_LENGTH);
							
	    		writeToAll(message);
	    		std::cout << std::endl;
				
				std::time_t t = std::time(nullptr);
				char str[100];
				std::strftime(str, sizeof(str), "%A %c", std::localtime(&t));
	    		std::cout << getActiveUser()->getName() << std::setw(35) << str << std::setw(30)
				<< "--->" << std::setw(30)
				<< "All" << std::endl << std::endl << std::setw(15) << "\" " << message << " \""
				<< std::endl << std::endl;
				
				string_imess = getActiveUser()->getName() + "       " + str + "       --->       All\n\n\" " + message + " \"";
				strcpy(i_message, string_imess.c_str());
				s_send(connection, i_message);
				//std::cout << i_message << std::endl;
				bzero(i_message, MESSAGE_LENGTH);

		    }
			continue;
		
		case '3':
		    {			
			std::cout << "Exit write massege... \n";
			string_imess = "Exit write massege... \n";
			strcpy(i_message, string_imess.c_str());
			s_send(connection, i_message);
			//std::cout << i_message << std::endl;
			bzero(i_message, MESSAGE_LENGTH);
			
			setActiveUser(nullptr);
			break;
		    }

		default: std::cout << "bad choose mode, try again! \n";
			string_imess = "bad choose mode, try again! \n";
			strcpy(i_message, string_imess.c_str());
			s_send(connection, i_message);
			//std::cout << i_message << std::endl;
			bzero(i_message, MESSAGE_LENGTH);
			continue;
		}

	}

	//std::shared_ptr<Chat> chat2 = std::shared_ptr<Chat>(new Chat());
	std::cout << std::endl;
	std::cout << "Done Chat_Start!";
	string_imess = "Done Chat_Start!";
	strcpy(i_message, string_imess.c_str());
	s_send(connection, i_message);
	//std::cout << i_message << std::endl;
	bzero(i_message, MESSAGE_LENGTH);
	return nullptr;
}