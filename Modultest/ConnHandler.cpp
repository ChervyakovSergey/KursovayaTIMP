#include <cstring>
#include <unistd.h>
#include <iostream>

#include "ConnHandler.h"
#include "Error.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/osrng.h>

#include "sha256.h"

// Конструктор
Client::Client(const string &address, uint16_t port)
    : address(address), port(port), socket(-1) {}

string Client::getAddress() const
{
    return this->address;
}
uint16_t Client::getPort() const
{
    return this->port;
}

// Метод для установки соединения
void Client::connect()
{
    this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket < 0)
    {
        throw Error("Failed to create socket", __func__);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);

    if (inet_pton(AF_INET, this->address.c_str(), &server_addr.sin_addr) <= 0)
    {
        throw Error("Invalid address/ Address not supported", __func__);
    }

    if (::connect(this->socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        throw Error("Connection failed", __func__);
    }
}

// Метод для аутентификации
void Client::authenticate(const string &login, const string &password)
{
    // Отправка логина серверу
    if (send(this->socket, login.c_str(), login.size(), 0) < 0)
    {
        throw Error("Failed to send login", __func__);
    }

    // Получение соли от сервера
    char salt[17]; // Соль должна быть 16 символов
    int salt_length = recv(this->socket, salt, sizeof(salt) - 1, 0);
    if (salt_length < 0)
    {
        throw Error("Failed to receive salt", __func__);
    }
    salt[salt_length] = '\0';

    string hash_hex = sha256(string(salt) + password);

    // Отправка хеша серверу
    if (send(this->socket, hash_hex.c_str(), hash_hex.size(), 0) < 0)
    {
        throw Error("Failed to send hash", __func__);
    }

    // Получение ответа от сервера
    char response[1024];
    int response_length = recv(this->socket, response, sizeof(response) - 1, 0);
    if (response_length < 0)
    {
        throw Error("Failed to receive auth response", __func__);
    }

    response[response_length] = '\0';
    if (string(response) != "OK")
    {
        throw Error("Authentication failed", __func__);
    }
}

// Метод для вычислений
vector<int16_t> Client::calculate(const vector<vector<int16_t>> &data)
{
    // Передача количества векторов
    uint32_t num_vectors = data.size();
    if (send(this->socket, &num_vectors, sizeof(num_vectors), 0) < 0)
    {
        throw Error("Failed to send number of vectors", __func__);
    }

    // Передача каждого вектора
    for (const auto &vec : data)
    {
        uint32_t vec_size = vec.size();
        if (send(this->socket, &vec_size, sizeof(vec_size), 0) < 0)
        {
            throw Error("Failed to send vector size", __func__);
        }
        if (send(this->socket, vec.data(), vec_size * sizeof(int16_t), 0) < 0)
        {
            throw Error("Failed to send vector data", __func__);
        }
    }

    // Получение результатов
    vector<int16_t> results(num_vectors);
    for (uint32_t i = 0; i < num_vectors; ++i)
    {
        if (recv(this->socket, &results[i], sizeof(int16_t), 0) < 0)
        {
            throw Error("Failed to receive result", __func__);
        }
    }

    // Логирование результата
    cout << "Log: \"Client.calculate()\"\n";
    cout << "Results: {";
    for (const auto &val : results)
    {
        cout << val << ", ";
    }
    if (!results.empty())
    {
        cout << "\b\b"; // Удалить последнюю запятую и пробел
    }
    cout << "}\n";

    return results;
}

// Метод для закрытия соединения
void Client::disconnect()
{
    if (this->socket >= 0)
    {
        ::close(this->socket);
        this->socket = -1;
    }
}
