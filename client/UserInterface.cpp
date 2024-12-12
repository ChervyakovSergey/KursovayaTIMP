#include "UserInterface.h"
#include <iostream>

void UserInterface::display_help() {
    std::cout << "Usage: client <server_address> <port> <input_file> <login_file> <output_file>\n";
}

void UserInterface::display_error(const std::string& message) {
    std::cerr << "Error: " << message << "\n";
}






