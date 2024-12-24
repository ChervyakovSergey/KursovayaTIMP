#include "Error.h"

// Конструктор с аргументом string
Error::Error(const string &what_arg, const string &func_name)
    : runtime_error(what_arg), func_name(func_name)
{
    time_t now = time(0);
    this->timestamp = ctime(&now);
}

// Конструктор с аргументом char*
Error::Error(const char *what_arg, const string &func_name)
    : runtime_error(what_arg), func_name(func_name)
{
    time_t now = time(0);
    this->timestamp = ctime(&now);
}

// Метод для получения имени функции
string Error::getFuncName() const
{
    return this->func_name;
}

// Метод для получения временной метки
string Error::getTimestamp() const
{
    return this->timestamp;
}
