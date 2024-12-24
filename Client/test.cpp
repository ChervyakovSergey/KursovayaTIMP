#include "UnitTest++/UnitTest++.h"
#include "CommandLineDecoder.h"
#include "DataHandler.h"
#include "ConnHandler.h"
#include "sha256.h"
#include <cstdio>
#include <fstream>

// Тесты для CommandLineDecoder
SUITE(CommandLineDecoderTests)
{
    TEST(ParseValidArguments)
    {
        const char *argv[] = {"program", "-a", "127.0.0.1", "-p", "1234", "-i", "input.txt", "-o", "output.txt", "-c", "config.cfg"};
        CommandLineDecoder cmdDecoder(11, const_cast<char **>(argv));
        CHECK_EQUAL("127.0.0.1", cmdDecoder.getServerAddress());
        CHECK_EQUAL(1234, cmdDecoder.getServerPort());
        CHECK_EQUAL("input.txt", cmdDecoder.getInputFilePath());
        CHECK_EQUAL("output.txt", cmdDecoder.getOutputFilePath());
        CHECK_EQUAL("config.cfg", cmdDecoder.getConfigFilePath());
    }

    TEST(MissingArguments)
    {
        const char *argv[] = {"program", "-a", "127.0.0.1"};
        CHECK_THROW(CommandLineDecoder cmdDecoder(3, const_cast<char **>(argv)), runtime_error);
    }

    TEST(InvalidArguments)
    {
        const char *argv[] = {"program", "-x", "127.0.0.1"};
        CHECK_THROW(CommandLineDecoder cmdDecoder(3, const_cast<char **>(argv)), runtime_error);
    }
}

// Тесты для DataHandler
SUITE(DataHandlerTests)
{
    TEST(SaveVector)
    {
        vector<int16_t> testVector = {1, 2, 3, 4, 5};
        string inputPath = "input.txt";
        string outputPath = "output.txt";
        string configPath = "config.cfg";

        DataHandler dataHandler(inputPath, outputPath, configPath);
        dataHandler.saveVector(testVector);

        // Проверка содержимого выходного файла
        ifstream outfile(outputPath);
        string line;
        getline(outfile, line);
        CHECK_EQUAL("5", line);
        getline(outfile, line);
        CHECK_EQUAL("1 2 3 4 5", line);
        outfile.close();

        // Удаление файлов
        remove(outputPath.c_str());
        remove(configPath.c_str());
    }

    TEST(LoadVector)
    {
        string inputPath = "input.txt";
        string outputPath = "output.txt";
        string configPath = "config.cfg";

        // Создание файлов для тестирования
        ofstream inputFile(inputPath);
        inputFile << "1\n5\n1 2 3 4 5\n";
        inputFile.close();

        DataHandler dataHandler(inputPath, outputPath, configPath);
        auto resultVector = dataHandler.loadVectors();

        CHECK_EQUAL(1, resultVector.size());
        CHECK_EQUAL(5, resultVector[0].size());
        CHECK_ARRAY_EQUAL(vector<int16_t>({1, 2, 3, 4, 5}), resultVector[0], 5);

        // Удаление файлов
        remove(inputPath.c_str());
        remove(outputPath.c_str());
        remove(configPath.c_str());
    }

    TEST(LoadInvalidVectorPath)
    {
        string inputPath = "invalid_input.txt";
        string outputPath = "output.txt";
        string configPath = "config.cfg";

        DataHandler dataHandler(inputPath, outputPath, configPath);
        CHECK_THROW(dataHandler.loadVectors(), Error);
    }

    TEST(ReadLargeValues)
    {
        string inputPath = "large_values_input.txt";
        string outputPath = "output.txt";
        string configPath = "config.cfg";

        // Запись данных, превышающих диапазон int16_t, в файл для тестирования
        ofstream infile(inputPath);
        infile << "1\n32768\n";
        infile.close();

        DataHandler dataHandler(inputPath, outputPath, configPath);
        CHECK_THROW(dataHandler.loadVectors(), Error);

        // Удаление файлов
        remove(inputPath.c_str());
    }

    TEST(LoadValidConfig)
    {
        string inputPath = "input.txt";
        string outputPath = "output.txt";
        string configPath = "config.cfg";

        // Создание файла конфигурации с валидными данными
        ofstream configFile(configPath);
        configFile << "user:password\n";
        configFile.close();

        DataHandler dataHandler(inputPath, outputPath, configPath);
        auto configData = dataHandler.loadConfig();

        CHECK_EQUAL("user", configData[0]);
        CHECK_EQUAL("password", configData[1]);

        // Удаление файлов
        remove(inputPath.c_str());
    }

    TEST(LoadInvalidConfigPath)
    {
        string inputPath = "input.txt";
        string outputPath = "output.txt";
        string configPath = "invalid_config.cfg";

        DataHandler dataHandler(inputPath, outputPath, configPath);
        CHECK_THROW(dataHandler.loadConfig(), Error);
    }

    TEST(LoadInvalidConfig)
    {
        string inputPath = "input.txt";
        string outputPath = "output.txt";
        string configPath = "config.cfg";

        // Создание файла конфигурации с валидными данными
        ofstream configFile(configPath);
        configFile << "userpassword\n";
        configFile.close();

        DataHandler dataHandler(inputPath, outputPath, configPath);
        CHECK_THROW(dataHandler.loadConfig(), Error);

        // Удаление файлов
        remove(inputPath.c_str());
    }
}
// Тесты для Client
SUITE(ClientTests)
{
    TEST(ConnectionInitialization)
    {
        Client client("127.0.0.1", 1234);
        CHECK_EQUAL("127.0.0.1", client.getAddress());
        CHECK_EQUAL(1234, client.getPort());
    }
}

// Тесты для SHA256
SUITE(SHA256Tests)
{
    TEST(SameHashForSameInput)
    {
        string input = "test input";
        string hash1 = sha256(input);
        string hash2 = sha256(input);

        CHECK_EQUAL(hash1, hash2);
    }

    TEST(DifferentHashForDifferentInput)
    {
        string input1 = "test input 1";
        string input2 = "test input 2";
        string hash1 = sha256(input1);
        string hash2 = sha256(input2);

        CHECK(hash1 != hash2);
    }
}

int main(int argc, char *argv[])
{
    return UnitTest::RunAllTests();
}
