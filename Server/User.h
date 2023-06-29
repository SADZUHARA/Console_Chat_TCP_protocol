#pragma once
#include <ostream>
#include <string>
#include <set>
#include <fstream>
class User
{
	std::string _name;
	std::string _login;
	std::string _password;
	std::set<int> _num_mess; 
public:
	User();
	User(const std::string& name, const std::string& login, const std::string& password);		
	std::string& getName() { return _name; }
	const std::string& getLogin() { return _login; }
	std::string& getPassword() { return _password; }	
	std::set<int>& get_num_mess() { return _num_mess; }
	friend std::fstream& operator>>(std::fstream&, User&);
	friend std::fstream& operator<<(std::fstream&, User&);
	

};

