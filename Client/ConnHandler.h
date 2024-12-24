#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

class Client
{
public:
    // Конструктор
    Client(const string &address, uint16_t port);

    // Методы для получения адреса сервера
    string getAddress() const;

    // Методы для получения порта сервера
    uint16_t getPort() const;

    // Метод для установки соединения
    void connect();

    // Метод для аутентификации
    void authenticate(const string &login, const string &password);

    // Метод для вычислений
    vector<int16_t> calculate(const vector<vector<int16_t>> &data);

    // Метод для закрытия соединения
    void disconnect();

private:
    string address;
    uint16_t port;
    int socket;
};
