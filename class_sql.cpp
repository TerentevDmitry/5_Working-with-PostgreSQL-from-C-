#include "class_sql.h"


DataBase::DataBase(const std::string& connection) : connection_{ connection } { std::cout << "Connected to database successfully!" << std::endl; };



void DataBase::createDatabase() // Creating a database structure (tables)
{
    try
    {
        pqxx::work txn(connection_);
        txn.exec(R"(CREATE TABLE IF NOT EXISTS clients(id SERIAL PRIMARY KEY, name TEXT, surname TEXT, email TEXT);  
            CREATE TABLE IF NOT EXISTS phones(id SERIAL PRIMARY KEY, client_id INT REFERENCES clients(id), phone TEXT);)");
        txn.commit();
        std::cout << "А database structure (tables) created" << std::endl;
    }
    catch (const std::exception& ex)
    {
        //setlocale(LC_ALL, "Russian");
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        std::cerr << "Exception happened: " << ex.what() << std::endl;
    }
}

void DataBase::addClient() //Method for adding a new client
{
    Client client;
    std::cin.clear();

    std::cout << "Adding a new client " << std::endl; 
    std::cout << "Please, enter name:> ";
    
    std::getline(std::cin, client.name_);
    std::cin.clear();
    
    std::cout << "Please, enter surname:> ";
    std::getline(std::cin, client.surname_);
    std::cin.clear();

    std::cout << "Please, enter email:> ";
    std::getline(std::cin, client.email_);
    std::cin.clear();

    try
    {
        pqxx::work txn(connection_);
        //connection_.set_client_encoding("UTF8");
        pqxx::result res = txn.exec_params("INSERT INTO clients (name, surname, email) VALUES ($1, $2, $3) RETURNING id", client.name_, client.surname_, client.email_);
        
        if (!res.empty()) {
            int client_id = res[0][0].as<int>();

            std::string phone;
            std::cout << "Please, enter phone number:> ";
            std::getline(std::cin, phone);
            std::cin.clear();
            client.phones_.push_back(phone);
            bool oneMorePhone = false;
            do
            {
                std::cout << std::endl << "Enter one more phone number(enter to skip):> ";
                std::getline(std::cin, phone);
                std::cin.clear();
                if (phone != "") client.phones_.push_back(phone);
                else oneMorePhone = true;
                
            } while (!oneMorePhone);
          
            txn.exec_params("INSERT INTO phones (client_id, phone) VALUES ($1, $2);", client_id, client.phones_);

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
        std::cerr << "Exception happened: " << ex.what() << std::endl;
    }
}

void DataBase::addPhone(const std::string& name, const std::string& phone) // Adding a Phone for an Existing Customer
{
    pqxx::work txn(connection_);
    pqxx::result res = txn.exec_params("SELECT id FROM clients WHERE name = $1", name);
    if (!res.empty()) {
        int client_id = res[0][0].as<int>();
        txn.exec_params("INSERT INTO phones (client_id, phone) VALUES ($1, $2)", client_id, phone);
        txn.commit();
        std::cout << "Phone added for client: " << name << std::endl;
    }
    else {
        txn.abort();
        std::cerr << "Client not found: " << name << std::endl;
    }
}
















void DataBase::show()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    pqxx::work txn(connection_);
    
    // Получаем список таблиц в базе данных
    pqxx::result tables = txn.exec("SELECT table_name FROM information_schema.tables WHERE table_schema='public'");

    // Для каждой таблицы выводим все ее данные
    for (auto row : tables) 
    {
        std::string table_name = row[0].as<std::string>();

        // Выполняем SELECT-запрос для выборки данных из таблицы
        std::string query = "SELECT * FROM " + table_name;
        pqxx::result data = txn.exec(query);

        // Выводим данные из таблицы в консоль
        std::cout << "Table: " << table_name << std::endl;
        for (auto& row : data) {
            for (auto& field : row) {
                std::cout << field.c_str() << "  ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    txn.commit();
    std::cout << "Done" << std::endl;
};