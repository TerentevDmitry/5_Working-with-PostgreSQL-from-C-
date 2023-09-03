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
	pqxx::connection connection_;
	
public:
	DataBase(const std::string& connection);

    void createDatabaseTables();
	void addClient(const std::string& name, const std::string& surname, const std::string& email, const std::string& phone);
	void addPhone(const std::string& name, const std::string& phone);
	void updateClient(const std::string& email, const std::string& newName, const std::string& newSurname, const std::string& newEmail);
	void removePhone(const std::string& email, const std::string& phone);
	void removeClient(const std::string& email);

	std::vector<Client> findClients(const std::string& query);
	
	void show();
};