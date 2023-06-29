#include "User.h"
//#include <fstream>
#include <iostream>


User::User() = default;

User::User(const std::string& name, const std::string& login, const std::string& password): 
	        _name (name), _login(login), _password(password) {}


std::fstream& operator>>(std::fstream& is, User& us){

	int count{0};	
	is >> count;
	is.get();
	std::getline(is, us._login);	
	std::getline(is, us._name);		
	std::getline(is, us._password);
	
	int num {0};
	for (int i = 0; i < count; i++)
	     {
			is >> num;
			is.get();
			us._num_mess.emplace(num);

		 }     
	
	return is;

}
std::fstream& operator<<(std::fstream& os, User& us){
	
	int count =  us._num_mess.size();
	os << count;	
	os << '\n';
	os << us._login;
	os << '\n';
	os << us._name;
	os << '\n';
	os << us._password;
	os << '\n';
	std::set<int> ::iterator it = us._num_mess.begin() ;
	
	while (it != us._num_mess.end())
	     {
			os << *it << ' ';
			it++;

		 }   
	
	return os;

}