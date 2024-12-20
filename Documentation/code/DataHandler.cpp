#include "DataHandler.h"

// Конструктор
DataHandler::DataHandler(string &inputPath, string &outputPath, string &configPath)
{
    this->inputPath = inputPath;
    this->outputPath = outputPath;
    this->configPath = configPath;
}

// Метод для получения пути входного файла
string DataHandler::getInputPath()
{
    return this->inputPath;
}

// Метод для получения пути выходного файла
string DataHandler::getOutputPath()
{
    return this->outputPath;
}

// Метод для получения пути файла конфигурации
string DataHandler::getConfigPath()
{
    return this->configPath;
}

// Метод для записи
void DataHandler::saveVector(const vector<int16_t> &data)
{
    ofstream outfile(this->outputPath);
    if (!outfile.is_open())
    {
        throw Error("Unable to open output file", __func__);
    }
    int16_t vec_size = data.size();
    outfile << vec_size << "\n";
    for (size_t i = 0; i < data.size(); ++i)
    {
        outfile << data[i];
        if (i < data.size() - 1)
        {
            outfile << " ";
        }
    }
    outfile << "\n";
    if (!outfile)
    {
        throw Error("Error writing to output file", __func__);
    }
    outfile.close();

    // Вывод записанных данных
    cout << "log: write vector complete.\nvec: ";
    displayVector(data);
}

// Метод для чтения
vector<vector<int16_t>> DataHandler::loadVectors()
{
    ifstream infile(this->inputPath);
    if (!infile.is_open())
    {
        throw Error("Unable to open input file", __func__);
    }

    string line;
    int16_t num_vectors;
    vector<vector<int16_t>> vectors;

    // Чтение количества векторов
    if (getline(infile, line))
    {
        stringstream ss(line);
        ss >> num_vectors;
    }
    else
    {
        throw Error("Error reading number of vectors", __func__);
    }

    // Чтение каждого вектора
    for (int16_t i = 0; i < num_vectors; ++i)
    {
        vector<int16_t> vec;
        int16_t vec_size;

        // Чтение размера вектора
        if (getline(infile, line))
        {
            stringstream ss(line);
            ss >> vec_size;
        }
        else
        {
            throw Error("Error reading vector size", __func__);
        }

        // Чтение значений вектора
        if (getline(infile, line))
        {
            stringstream ss(line);
            int16_t value;
            for (int16_t j = 0; j < vec_size; ++j)
            {
                if (!(ss >> value))
                {
                    throw Error("Error reading vector values", __func__);
                }
                vec.push_back(value);
            }
        }
        else
        {
            throw Error("Error reading vector values", __func__);
        }

        vectors.push_back(vec);
    }

    infile.close();

    // Вывод считанных данных
    cout << "log: read vectors complete.\nvec: ";
    displayVectors(vectors);
    return vectors;
}

// Метод для чтения конфигурации
array<string, 2> DataHandler::loadConfig()
{
    ifstream infile(this->configPath);
    if (!infile.is_open())
    {
        throw Error("Unable to open config file", __func__);
    }

    array<string, 2> configArray;
    string line;

    if (getline(infile, line))
    {
        stringstream ss(line);
        if (!(getline(ss, configArray[0], ':') && getline(ss, configArray[1])))
        {
            throw Error("Error reading config data", __func__);
        }
    }
    else
    {
        throw Error("Error reading config file", __func__);
    }

    infile.close();
    cout << "log: read config complete.\n"
         << "cfg: " << configArray[0]
         << ":" << configArray[1] << "\n";
    return configArray;
}

// Функция для вывода вектора int16_t
void displayVector(const vector<int16_t> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// Функция для рекурсивного вывода вложенных векторов
void displayVectors(const vector<vector<int16_t>> &vec)
{
    cout << "[";
    if (!vec.empty()) {
        cout << endl;
        for (const auto &subVec : vec) {
            cout << "\t";
            displayVector(subVec);
        }
    }
    cout << "]" << endl;
}
