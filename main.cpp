//Домашнее задание к занятию «Работа с PostgreSQL из C++»
//Задание 1. Создайте программу для управления клиентами на C++.

#include "class_sql.h"

int main()
{
	try
	{
		std::string connection_string = "host=127.0.0.1 port=5432 dbname=Task1_clients user=postgres password=222322";
		DataBase db(connection_string);

        db.createDatabaseTables();

        db.addClient("Dimadsw", "Tere23eds", "DiTe@ma.r", "118927521265589");
        db.show();
        

        db.addClient("Dima", "Tere", "Tere@mail.ru11", "1189275265589");
        db.show();

        db.addClient("Dima31", "Tere31", "Tere@mail.ru31", "118959265589");
        db.show();

        db.addClient("Dima21", "Tere21", "Tere@mail.ru21", "1289875265589");
        db.show();

        try
        {
            db.addPhone("Dima", "89658756541");
            db.show();

            db.addPhone("Dima55", "89658756541");
            db.show();
        }
        catch (const std::exception& ex)
        {
            SetConsoleCP(CP_UTF8);
            SetConsoleOutputCP(CP_UTF8);
            std::cout << "Exception happened: " << ex.what() << std::endl;
        }

        try
        {
            db.updateClient("Tere@mail.ru31", "Diman", "Terentev", "Diman@mail.ru");
            db.show();

            db.updateClient("Dim@mail.ru", "Diman", "Terent", "Diman@mail.ru");
            db.show();
        }
        catch (const std::exception& ex)
        {
            SetConsoleCP(CP_UTF8);
            SetConsoleOutputCP(CP_UTF8);
            std::cout << "Exception happened: " << ex.what() << std::endl;
        }

        db.removePhone("Diman@mail.ru", "89658756541");
            
        db.removeClient("DiTe@ma.r");

        std::vector<Client> foundClients = db.findClients("Dima11");
        for (const auto& client : foundClients) 
        {
            std::cout << "Found client: " << client.name_ << " " << client.surname_ << " " << client.email_ << " " << std::endl;
        }

	}
	catch (const std::exception& ex)
	{
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
		std::cout << "Exception happened: " << ex.what() << std::endl;
	}

	std::cout << std::endl << std::endl << "Goodbay, World";
};