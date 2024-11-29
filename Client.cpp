#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <boost/program_options.hpp>
#include "FileManager.h"
#include "Authenticator.h"
#include "ServerConnection.h"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    // Определяем переменные для параметров
    std::string server_ip;
    uint16_t server_port;
    std::string input_file;
    std::string output_file;
    std::string credentials_file;

    // Определяем параметры командной строки
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("server_ip", po::value<std::string>(&server_ip)->required(), "IP address of the server")
        ("server_port", po::value<uint16_t>(&server_port)->required(), "Port of the server")
        ("input_file", po::value<std::string>(&input_file)->required(), "Input file containing vectors")
        ("output_file", po::value<std::string>(&output_file)->required(), "Output file for results")
        ("credentials_file", po::value<std::string>(&credentials_file)->required(), "File containing login and password");

    // Парсим параметры командной строки
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    
    } catch (const po::error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << desc << std::endl;
        return EXIT_FAILURE;
    }

    // Читаем учетные данные
    std::string login, password;
    {
        std::ifstream cred_file(credentials_file);
        if (!cred_file || !(cred_file >> login >> password)) {
            std::cerr << "Failed to read credentials" << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Читаем векторы из файла
    std::vector<Vector> vectors = FileManager::read_vectors(input_file);
    
    // Устанавливаем соединение с сервером
    ServerConnection server_connection(server_ip, server_port);
    server_connection.connect();

    // Аутентификация и отправка векторов
    Authenticator authenticator(login, password);
    try {
        authenticator.authenticate(server_connection.get_socket());
        server_connection.send_vectors(vectors);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        server_connection.close();
        return EXIT_FAILURE;
    }

    // Здесь вы можете реализовать получение результатов и запись их в файл

    server_connection.close();
    return EXIT_SUCCESS;
}
