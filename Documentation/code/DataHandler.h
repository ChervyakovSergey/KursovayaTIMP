#pragma once

#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Error.h"

using namespace std;

/**
 * @class DataHandler
 * @brief Класс для обработки данных, включая чтение и запись векторов и конфигурационных данных.
 *
 * Этот класс предоставляет методы для работы с файлами данных и конфигураций, 
 * такие как сохранение и загрузка векторов, а также чтение конфигурационных данных.
 */
class DataHandler
{
public:
    /**
     * @brief Конструктор класса DataHandler.
     * @param inputPath Путь к файлу входных данных.
     * @param outputPath Путь к файлу выходных данных.
     * @param configPath Путь к конфигурационному файлу.
     */
    DataHandler(string &inputPath, string &outputPath, string &configPath);

    /**
     * @brief Получает путь к файлу входных данных.
     * @return Путь к файлу входных данных.
     */
    string getInputPath();

    /**
     * @brief Получает путь к файлу выходных данных.
     * @return Путь к файлу выходных данных.
     */
    string getOutputPath();

    /**
     * @brief Получает путь к конфигурационному файлу.
     * @return Путь к конфигурационному файлу.
     */
    string getConfigPath();

    /**
     * @brief Сохраняет вектор данных в файл.
     * @param data Вектор данных для сохранения.
     * @throws Error В случае ошибки при записи в файл.
     */
    void saveVector(const vector<int16_t> &data);

    /**
     * @brief Загружает векторы данных из файла.
     * @return Вектор векторов данных.
     * @throws Error В случае ошибки при чтении из файла.
     */
    vector<vector<int16_t>> loadVectors();

    /**
     * @brief Загружает конфигурационные данные из файла.
     * @return Массив строк, содержащий данные конфигурации.
     * @throws Error В случае ошибки при чтении из файла.
     */
    array<string, 2> loadConfig();

private:
    string inputPath; ///< Путь к файлу входных данных.
    string outputPath; ///< Путь к файлу выходных данных.
    string configPath; ///< Путь к конфигурационному файлу.
};

/**
 * @brief Функция для вывода вектора int16_t.
 * @param vec Вектор для вывода.
 */
void displayVector(const vector<int16_t> &vec);

/**
 * @brief Функция для рекурсивного вывода вложенных векторов.
 * @param vec Вектор векторов для вывода.
 */
void displayVectors(const vector<vector<int16_t>> &vec);
