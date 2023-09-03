//Домашнее задание к занятию «Работа с PostgreSQL из C++»
//Задание 1. Создайте программу для управления клиентами на C++.

#include "class_sql.h"

int main()
{
    //setlocale(LC_ALL, "Russian");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

	try
	{
		std::string connection_string = "host=127.0.0.1 port=5432 dbname=Task1_clients user=postgres password=222322";
		DataBase db(connection_string);

        db.addClient();
        db.show();

        db.addPhone("name", "phone");
        db.show();





	}
	catch (const std::exception& ex)
	{
		setlocale(LC_ALL, "Russian");
		std::cout << "Exception happened: " << ex.what() << std::endl;
	}

	std::cout << std::endl << std::endl << "Hello, World";

	/*
    ```cpp
*#include <iostream>
*#include <pqxx/pqxx>

struct Client {
    std::string name;
    std::string surname;
    std::string email;
    std::vector<std::string> phones;
};

class Database {
private:
    pqxx::connection connection;

public:
    Database(const std::string& connectionString) : connection(connectionString) {
        // Подключение к базе данных
    }

    //void createDatabase() 
    //{
    //    // Создание структуры БД (таблиц)
    //    pqxx::work txn(connection);
    //    txn.exec(R"(
    //        CREATE TABLE clients (
    //            id SERIAL PRIMARY KEY,
    //            name TEXT,
    //            surname TEXT,
    //            email TEXT
    //        );
    //        CREATE TABLE phones (
    //            id SERIAL PRIMARY KEY,
    //            client_id INT REFERENCES clients(id),
    //            phone TEXT
    //        );
    //    )");
    //    txn.commit();
    }

    void addClient(const std::string& name, const std::string& surname, const std::string& email) 
    {
        // Добавление нового клиента
        pqxx::work txn(connection);
        pqxx::result res = txn.exec_params("INSERT INTO clients (name, surname, email) VALUES ($1, $2, $3) RETURNING id",
            name, surname, email);
        if (!res.empty()) {
            int client_id = res[0][0].as<int>();
            txn.commit();
            std::cout << "Client added with ID: " << client_id << std::endl;
        } else {
            txn.abort();
            std::cerr << "Failed to add client" << std::endl;
        }
    }

    void addPhone(const std::string& name, const std::string& phone) 
    {
        // Добавление телефона для существующего клиента
        pqxx::work txn(connection);
        pqxx::result res = txn.exec_params("SELECT id FROM clients WHERE name = $1", name);
        if (!res.empty()) {
            int client_id = res[0][0].as<int>();
            txn.exec_params("INSERT INTO phones (client_id, phone) VALUES ($1, $2)", client_id, phone);
            txn.commit();
            std::cout << "Phone added for client: " << name << std::endl;
        } else {
            txn.abort();
            std::cerr << "Client not found: " << name << std::endl;
        }
    }

    void updateClient(const std::string& name, const std::string& newSurname, const std::string& newEmail) 
    {
        // Изменение данных о клиенте
        pqxx::work txn(connection);
        pqxx::result res = txn.exec_params("SELECT id FROM clients WHERE name = $1", name);
        if (!res.empty()) {
            int client_id = res[0][0].as<int>();
            txn.exec_params("UPDATE clients SET surname = $1, email = $2 WHERE id = $3",
                newSurname, newEmail, client_id);
            txn.commit();
            std::cout << "Client updated: " << name << std::endl;
        } else {
            txn.abort();
            std::cerr << "Client not found: " << name << std::endl;
        }
    }

    void removePhone(const std::string& name, const std::string& phone) 
    {
        // Удаление телефона для существующего клиента
        pqxx::work txn(connection);
        pqxx::result res = txn.exec_params("SELECT id FROM clients WHERE name = $1", name);
        if (!res.empty()) {
            int client_id = res[0][0].as<int>();
            txn.exec_params("DELETE FROM phones WHERE client_id = $1 AND phone = $2",
                client_id, phone);
            txn.commit();
            std::cout << "Phone removed for client: " << name << std::endl;
        } else {
            txn.abort();
            std::cerr << "Client not found: " << name << std::endl;
        }
    }

    void removeClient(const std::string& name) 
    {
        // Удаление существующего клиента
        pqxx::work txn(connection);
        pqxx::result res = txn.exec_params("SELECT id FROM clients WHERE name = $1", name);
        if (!res.empty()) {
            int client_id = res[0][0].as<int>();
            txn.exec_params("DELETE FROM phones WHERE client_id = $1", client_id);
            txn.
    
	    exec_params("DELETE FROM clients WHERE id = $1", client_id);
            txn.commit();
            std::cout << "Client removed: " << name << std::endl;
        } else {
            txn.abort();
            std::cerr << "Client not found: " << name << std::endl;
        }
    }

    std::vector<Client> findClients(const std::string& query) {
        // Найти клиента по его данным (имени, фамилии, email-у или телефону)
        std::vector<Client> result;
        pqxx::work txn(connection);
        pqxx::result res = txn.exec_params("SELECT * FROM clients WHERE name = $1 OR surname = $1 OR email = $1", query);
        txn.commit();
        for (auto row : res) {
            Client client;
            client.name = row["name"].as<std::string>();
            client.surname = row["surname"].as<std::string>();
            client.email = row["email"].as<std::string>();
            result.push_back(client);
        }
        return result;
    }
};
```

Пример использования класса:

```cpp
int main() {
    std::string connectionString = "postgresql://user:password@localhost/testdb";
    Database db(connectionString);
    db.createDatabase();

    db.addClient("John", "Doe", "john.doe@example.com");
    db.addPhone("John", "123456789");
    db.addPhone("John", "987654321");

    db.addClient("Jane", "Smith", "jane.smith@example.com");
    db.addPhone("Jane", "555555555");

    std::vector<Client> foundClients = db.findClients("john.doe@example.com");
    for (const auto& client : foundClients) {
        std::cout << "Found client: " << client.name << " " << client.surname << std::endl;
    }

    return 0;
}
```
	*/






};