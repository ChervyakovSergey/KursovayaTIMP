#include <iostream>
#include <vector>
#include <string>

#include "CommandLineDecoder.h"
#include "DataHandler.h"
#include "ConnHandler.h"
#include "Error.h"

using namespace std;

int main(int argc, char* argv[])
{
    try
    {
        // Декодирование параметров командной строки
        CommandLineDecoder cmdDecoder(argc, argv);
        string serverAddress = cmdDecoder.getServerAddress();
        uint16_t serverPort = cmdDecoder.getServerPort();
        string inputFilePath = cmdDecoder.getInputFilePath();
        string outputFilePath = cmdDecoder.getOutputFilePath();
        string configFilePath = cmdDecoder.getConfigFilePath();

        // Чтение данных из файлов
        DataHandler dataHandler(inputFilePath, outputFilePath, configFilePath);
        auto inputData = dataHandler.loadVectors();
        auto configData = dataHandler.loadConfig();

        // Подключение к серверу
        Client client(serverAddress, serverPort);
        client.connect();

        // Аутентификация
        client.authenticate(configData[0], configData[1]);

        // Выполнение расчетов
        auto results = client.calculate(inputData);

        // Закрытие соединения
        client.disconnect();

        // Сохранение результатов в файл
        dataHandler.saveVector(results);

        cout << "Работа завершена успешно." << endl;
    }
    catch (const Error& e)
    {
        cerr << "Error: " << e.what() << endl;
        cerr << "Function: " << e.getFuncName() << endl;
        cerr << "Timestamp: " << e.getTimestamp() << endl;
        return 1;
    }
    catch (const exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}
