#include "class_sql.h"


Data_base::Data_base(const std::string& connection) : connection_{ connection } { std::cout << "Connected to database successfully!" << std::endl; };

void Data_base::createDatabase() // Creating a database structure (tables)
{
    try
    {
        pqxx::work txn(connection_);
        txn.exec(R"(CREATE TABLE IF NOT EXISTS clients(id SERIAL PRIMARY KEY, name TEXT, surname TEXT, email TEXT);  
            CREATE TABLE IF NOT EXISTS phones(id SERIAL PRIMARY KEY, client_id INT REFERENCES clients(id), phone TEXT);)");
        txn.commit();
    }
    catch (const std::exception& ex)
    {
        //setlocale(LC_ALL, "Russian");
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        std::cerr << "Exception happened: " << ex.what() << std::endl;
    }
}

void Data_base::addClient(const std::string& name, const std::string& surname, const std::string& email) //Method for adding a new client
{
    //void Data_base::addClient(const std::string & name, const std::string & surname, const std::string & email); //Method for adding a new client
    
    try
    {
        pqxx::work txn(connection_);
        pqxx::result res = txn.exec_params("INSERT INTO clients (name, surname, email) VALUES ($1, $2, $3) RETURNING id", name_, surname_, email_);
        
        
        
        if (!res.empty()) {
            int client_id = res[0][0].as<int>();
            txn.commit();
            std::cout << "Client added with ID: " << client_id << std::endl;
        }
        else {
            txn.abort();
            std::cerr << "Failed to add client" << std::endl;
        }
    }
    catch (const std::exception& ex)
    {
        //setlocale(LC_ALL, "Russian");
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        std::cout << "Exception happened: " << ex.what() << std::endl;
    }
}