#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <string>
#include <vector>

class Communicator {
public:
    Communicator(const std::string& serverAddress, int serverPort);
    ~Communicator();

    void connectToServer();
    void sendMessage(const std::string& message);
    void sendMessage(const char* data, size_t size);
    std::string receiveMessage(size_t bufferSize);
    void receiveMessage(char* buffer, size_t size);

    bool authenticate(const std::string& login, const std::string& password);
    void send_vectors(const std::vector<std::vector<int16_t>>& vectors);
    void closeSocket();

private:
    int socketFd;
    std::string serverAddress;
    int serverPort;

    static constexpr size_t SALT_SIZE = 16;
};

#endif // COMMUNICATOR_H












