cmake_minimum_required(VERSION 3.2)

set(PostgreSQL_ADDITIONAL_VERSIONS "15")

project(Task1_clients)

add_executable(Task1_clients main.cpp "class_sql.cpp" "class_sql.h")

add_subdirectory("C:\\Users\\Zabey\\Desktop\\CPP\\libpqxx-7.8.1" libpqxx-build)

target_compile_features(Task1_clients PRIVATE cxx_std_17)

target_link_libraries(Task1_clients PRIVATE pqxx)