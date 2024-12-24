#ifndef COMMANDLINEDECODER_H
#define COMMANDLINEDECODER_H

#include <string>
#include <iostream>
#include <cstdint> // Включите эту строку для определения uint16_t
#include "Error.h"

class CommandLineDecoder {
public:
    CommandLineDecoder(int argc, char* argv[]);
    std::string getServerAddress() const;
    uint16_t getServerPort() const; // Теперь uint16_t определён
    std::string getInputFilePath() const;
    std::string getOutputFilePath() const;
    std::string getConfigFilePath() const;

private:
    void parse(int argc, char* argv[]);
    void showHelp() const;

    std::string serverAddress;
    uint16_t serverPort; ///< Порт сервера.
    std::string inputFilePath;
    std::string outputFilePath;
    std::string configFilePath;
};

#endif // COMMANDLINEDECODER_H

