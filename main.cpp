#include <iostream>
#include <pqxx/pqxx>
#include <Windows.h>


int main()
{
	// Set console code page to UTF-8 so console known how to interpret string data
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	try
	{
		pqxx::connection conn("host=127.0.0.1 "
			"port=5432 "
			"dbname=Task1_clients "
			"user=postgres "
			"password=222322");


		pqxx::work transaction{ conn };
		transaction.query<int, std::string>
			(
				"select track_name, album_name "
				"from track_list tl "
				"join album_list al on al.id_album_list = tl.id_album_list; "
			);

		for (auto& [track_name, album_name] : transaction.query<std::string, std::string>
			(
				"select track_name, album_name "
				"from track_list tl "
				"join album_list al on al.id_album_list = tl.id_album_list; "
			))
		{
			std::cout << track_name << "\t\t" << album_name << std::endl;
		}

	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception happened: " << ex.what() << std::endl;
	}
	



	std::cout << "Hello, World";
};