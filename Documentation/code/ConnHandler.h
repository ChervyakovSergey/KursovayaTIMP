#pragma once

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

/**
 * @class Client
 * @brief Класс для работы с клиентом, который подключается к серверу.
 *
 * Этот класс предоставляет методы для установки соединения, аутентификации, 
 * выполнения вычислений и закрытия соединения с сервером.
 */
class Client
{
public:
    /**
     * @brief Конструктор класса Client.
     * @param address Адрес сервера.
     * @param port Порт сервера.
     */
    Client(const string &address, uint16_t port);

    /**
     * @brief Получает адрес сервера.
     * @return Адрес сервера.
     */
    string getAddress() const;

    /**
     * @brief Получает порт сервера.
     * @return Порт сервера.
     */
    uint16_t getPort() const;

    /**
     * @brief Устанавливает соединение с сервером.
     * @throws Error В случае ошибки при создании или установке соединения.
     */
    void connect();

    /**
     * @brief Выполняет аутентификацию на сервере.
     * @param login Логин пользователя.
     * @param password Пароль пользователя.
     * @throws Error В случае ошибки аутентификации.
     */
    void authenticate(const string &login, const string &password);

    /**
     * @brief Выполняет вычисления на сервере.
     * @param data Данные для вычислений в виде вектора векторов.
     * @return Результат вычислений в виде вектора.
     * @throws Error В случае ошибки при отправке данных или получении результатов.
     */
    vector<int16_t> calculate(const vector<vector<int16_t>> &data);

    /**
     * @brief Закрывает соединение с сервером.
     */
    void disconnect();

private:
    string address; ///< Адрес сервера.
    uint16_t port; ///< Порт сервера.
    int socket; ///< Сокет для соединения с сервером.
};
