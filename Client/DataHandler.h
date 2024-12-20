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

class DataHandler
{
public:
    DataHandler(string &inputPath, string &outputPath, string &configPath);
    string getInputPath();
    string getOutputPath();
    string getConfigPath();
    void saveVector(const vector<int16_t> &data);
    vector<vector<int16_t>> loadVectors();
    array<string, 2> loadConfig();

private:
    string inputPath;
    string outputPath;
    string configPath;
};

void displayVector(const vector<int16_t> &vec);
void displayVectors(const vector<vector<int16_t>> &vec);
