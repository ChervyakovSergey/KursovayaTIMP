#include "Communicator.h"
#include "DataReader.h"
#include "DataWriter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 6) {
        std::cerr << "Usage: " << argv << " <server_address> <port> <input_file> <login_file> <output_file>\n";
        return 1;
    }

    std::string server_address = argv[1];
    int port = std::stoi(argv[2]);
    std::string input_file = argv[3];
    std::string login_file = argv[4];
    std::string output_file = argv[5];

    // Check if the login file exists
    if (access(login_file.c_str(), F_OK) != 0) {
        std::cerr << "Error: Login file " << login_file << " does not exist.\n";
        return 1;
    }

    // Read login data
    std::ifstream login_data(login_file);
    if (!login_data) {
        std::cerr << "Error: Unable to open login file " << login_file << ".\n";
        return 1;
    }

    std::string login, password;
    login_data >> login >> password;

    // Establish connection with the server
    Communicator communicator(server_address, port);
    try {
        communicator.connectToServer();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    // Authenticate with the server
    if (!communicator.authenticate(login, password)) {
        std::cerr << "Authentication failed.\n";
        return 1;
    }

    // Read vectors from input file
    DataReader reader;
    try {
        std::vector<std::vector<int16_t>> vectors = reader.read_vectors_from_file(input_file);
        communicator.send_vectors(vectors);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    // Close the socket
    communicator.closeSocket();

    return 0;
}

















