#pragma once

#include <stdexcept>
#include <string>
#include <ctime>

using namespace std;

/**
 * @class Error
 * @brief Класс для обработки ошибок, наследуемый от std::runtime_error.
 *
 * Этот класс предоставляет методы для получения имени функции, в которой произошла ошибка,
 * и временной метки ошибки.
 */
class Error : public runtime_error
{
public:
    /**
     * @brief Конструктор класса Error.
     * @param what_arg Сообщение об ошибке.
     * @param func_name Имя функции, в которой произошла ошибка.
     */
    explicit Error(const string &what_arg, const string &func_name);
    
    /**
     * @brief Конструктор класса Error.
     * @param what_arg Сообщение об ошибке.
     * @param func_name Имя функции, в которой произошла ошибка.
     */
    explicit Error(const char *what_arg, const string &func_name);

    /**
     * @brief Получает имя функции, в которой произошла ошибка.
     * @return Имя функции.
     */
    string getFuncName() const;

    /**
     * @brief Получает временную метку ошибки.
     * @return Временная метка.
     */
    string getTimestamp() const;

private:
    string func_name; ///< Имя функции, в которой произошла ошибка.
    string timestamp; ///< Временная метка ошибки.
};
