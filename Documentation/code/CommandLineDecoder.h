#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdint> // Добавлено включение для uint16_t
#include "Error.h"

using namespace std;

/**
 * @class CommandLineDecoder
 * @brief Класс для обработки аргументов командной строки.
 *
 * Этот класс предоставляет методы для парсинга и получения значений аргументов командной строки,
 * таких как адрес сервера, порт, пути к файлам входных данных, выходных данных и конфигурационному файлу.
 */
class CommandLineDecoder
{
public:
    /**
     * @brief Конструктор класса CommandLineDecoder.
     * @param argc Количество аргументов командной строки.
     * @param argv Массив аргументов командной строки.
     * @throws Error Если аргументы командной строки некорректны или отсутствуют.
     */
    CommandLineDecoder(int argc, char* argv[]);
    
    /**
     * @brief Получает адрес сервера.
     * @return Адрес сервера.
     */
    string getServerAddress() const;
    
    /**
     * @brief Получает порт сервера.
     * @return Порт сервера.
     */
    uint16_t getServerPort() const;
    
    /**
     * @brief Получает путь к файлу входных данных.
     * @return Путь к файлу входных данных.
     */
    string getInputFilePath() const;
    
    /**
     * @brief Получает путь к файлу выходных данных.
     * @return Путь к файлу выходных данных.
     */
    string getOutputFilePath() const;
    
    /**
     * @brief Получает путь к конфигурационному файлу.
     * @return Путь к конфигурационному файлу.
     */
    string getConfigFilePath() const;

private:
    string serverAddress; ///< Адрес сервера.
    uint16_t serverPort; ///< Порт сервера.
    string inputFilePath; ///< Путь к файлу входных данных.
    string outputFilePath; ///< Путь к файлу выходных данных.
    string configFilePath; ///< Путь к конфигурационному файлу.

    /**
     * @brief Парсинг аргументов командной строки.
     * @param argc Количество аргументов командной строки.
     * @param argv Массив аргументов командной строки.
     * @throws Error Если аргументы командной строки некорректны или отсутствуют.
     */
    void parse(int argc, char* argv[]);
    
    /**
     * @brief Показ справочной информации о программе.
     */
    void showHelp() const;
};

