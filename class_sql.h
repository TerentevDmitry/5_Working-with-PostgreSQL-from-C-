#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <Windows.h>

class Data_base
{
private:
	std::string name_;
	std::string surname_;
	std::string email_;
	std::vector<std::string> phones_;
	
	pqxx::connection connection_;

public:
	Data_base(const std::string& connection);
    void createDatabase();

	void addClient(const std::string& name, const std::string& surname, const std::string& email);

	



};