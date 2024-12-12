#include "Communicator.h"
#include <openssl/sha.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

// Function to hash a string with a salt
std::string hash_with_salt(const std::string& salt, const std::string& password) {
    std::string salted_input = salt + password;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(salted_input.c_str()), salted_input.size(), hash);

    std::ostringstream oss;
    oss << std::uppercase;
    for (unsigned char c : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return oss.str();
}

// Function to authenticate with the server
bool Communicator::authenticate(const std::string& login, const std::string& password) {
    // Send login
    if (send(socketFd, login.c_str(), login.size(), 0) <= 0) {
        throw std::runtime_error("Error: Failed to send login.");
    }

    // Receive salt from server
    char salt_buffer[SALT_SIZE + 1] = {0};
    if (recv(socketFd, salt_buffer, SALT_SIZE, 0) <= 0) {
        throw std::runtime_error("Error: Failed to receive salt.");
    }
    std::string salt(salt_buffer);
    if (salt == "ERR") {
        throw std::runtime_error("Authentication error: Server responded with ERR.");
    }

    // Calculate hash and send it to the server
    std::string hash = hash_with_salt(salt, password);
    if (send(socketFd, hash.c_str(), hash.size(), 0) <= 0) {
        throw std::runtime_error("Error: Failed to send hash.");
    }

    // Receive authentication response from server
    char auth_response[3] = {0};
    if (recv(socketFd, auth_response, 2, 0) <= 0) {
        throw std::runtime_error("Error: Failed to receive auth response.");
    }
    return std::string(auth_response) == "OK";
}

// Function to send vectors to the server and receive results
void Communicator::send_vectors(const std::vector<std::vector<int16_t>>& vectors) {
    uint16_t num_vectors = vectors.size();
    if (send(socketFd, &num_vectors, sizeof(num_vectors), 0) != sizeof(num_vectors)) {
        throw std::runtime_error("Error: Failed to send number of vectors.");
    }

    for (const auto& vec : vectors) {
        uint16_t vec_size = vec.size();
        if (send(socketFd, &vec_size, sizeof(vec_size), 0) != sizeof(vec_size)) {
            throw std::runtime_error("Error: Failed to send vector size.");
        }

        ssize_t data_size = vec.size() * static_cast<ssize_t>(sizeof(int16_t));
        ssize_t bytes_sent = 0;
        while (bytes_sent < data_size) {
            ssize_t chunk_size = send(socketFd, vec.data() + bytes_sent, data_size - bytes_sent, 0);
            if (chunk_size <= 0) {
                throw std::runtime_error("Error: Failed to send vector data.");
            }
            bytes_sent += chunk_size;
        }
        std::cout << "Sent " << bytes_sent << " bytes.\n";

        int16_t result;
        if (recv(socketFd, &result, sizeof(result), 0) != sizeof(result)) {
            throw std::runtime_error("Error: Failed to receive result.");
        }
        std::cout << "Result for vector: " << result << "\n";
    }
}

Communicator::Communicator(const std::string& serverAddress, int serverPort)
    : socketFd(-1), serverAddress(serverAddress), serverPort(serverPort) {}

Communicator::~Communicator() {
    closeSocket();
}

void Communicator::connectToServer() {
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1) {
        throw std::runtime_error("Failed to create socket.");
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid server address.");
    }

    if (connect(socketFd, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        throw std::runtime_error("Failed to connect to server.");
    }
}

void Communicator::sendMessage(const std::string& message) {
    sendMessage(message.c_str(), message.size());
}

void Communicator::sendMessage(const char* data, size_t size) {
    if (send(socketFd, data, size, 0) == -1) {
        throw std::runtime_error("Failed to send data.");
    }
}

std::string Communicator::receiveMessage(size_t bufferSize) {
    std::string buffer(bufferSize, '\0');
    ssize_t bytesRead = recv(socketFd, buffer.data(), bufferSize, 0);
    if (bytesRead == -1) {
        throw std::runtime_error("Failed to receive data.");
    }
    buffer.resize(bytesRead);
    return buffer;
}

void Communicator::receiveMessage(char* buffer, size_t size) {
    ssize_t bytesRead = recv(socketFd, buffer, size, 0);
    if (bytesRead != static_cast<ssize_t>(size)) {
        throw std::runtime_error("Failed to receive the expected amount of data.");
    }
}

void Communicator::closeSocket() {
    if (socketFd != -1) {
        close(socketFd);
        socketFd = -1;
    }
}































