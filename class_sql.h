#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <Windows.h>
#include <string>
#include <codecvt>


struct Client
{
	std::string name_;
	std::string surname_;
	std::string email_;
	std::vector<std::string> phones_;
};






class DataBase
{
private:
	//std::string name_;
	//std::string surname_;
	//std::string email_;
	//std::vector<std::string> phones_;
	
	pqxx::connection connection_;
	


public:
	DataBase(const std::string& connection);
    void createDatabase();
	void addClient();
	void addPhone(const std::string& name, const std::string& phone);

	void show();

	//connection_.set_client_encoding("UTF8");

};


//Client DataInput(const std::string& name, const std::string& surname, const std::string& email)
//{
//	return ;
//};