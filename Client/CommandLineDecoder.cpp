#include "CommandLineDecoder.h"

CommandLineDecoder::CommandLineDecoder(int argc, char* argv[])
{
    parse(argc, argv);
}

std::string CommandLineDecoder::getServerAddress() const
{
    return serverAddress;
}

uint16_t CommandLineDecoder::getServerPort() const
{
    return serverPort;
}

std::string CommandLineDecoder::getInputFilePath() const
{
    return inputFilePath;
}

std::string CommandLineDecoder::getOutputFilePath() const
{
    return outputFilePath;
}

std::string CommandLineDecoder::getConfigFilePath() const
{
    return configFilePath;
}

void CommandLineDecoder::parse(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-a" && i + 1 < argc)
        {
            this->serverAddress = argv[++i];
        }
        else if (arg == "-p" && i + 1 < argc)
        {
            this->serverPort = static_cast<uint16_t>(std::stoi(argv[++i]));
        }
        else if (arg == "-i" && i + 1 < argc)
        {
            this->inputFilePath = argv[++i];
        }
        else if (arg == "-o" && i + 1 < argc)
        {
            this->outputFilePath = argv[++i];
        }
        else if (arg == "-c" && i + 1 < argc)
        {
            this->configFilePath = argv[++i];
        }
        else if (arg == "-h")
        {
            showHelp();
            exit(0);
        }
        else
        {
            throw Error("Invalid argument: " + arg, __func__);
        }
    }

    if (this->serverAddress.empty() || this->serverPort == 0 || this->inputFilePath.empty() || this->outputFilePath.empty() || this->configFilePath.empty())
    {
        throw Error("Missing required arguments. Use -h for help.", __func__);
    }
}

void CommandLineDecoder::showHelp() const
{
    std::cout << "Usage: program [options]\n"
              << "Options:\n"
              << "  -a <address>      Server address\n"
              << "  -p <port>         Server port\n"
              << "  -i <input file>   Path to input file\n"
              << "  -o <output file>  Path to output file\n"
              << "  -c <config file>  Path to config file\n"
              << "  -h                Show help\n";
}

