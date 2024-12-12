#include "DataReader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

std::vector<std::vector<int16_t>> DataReader::read_vectors_from_file(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file) {
        throw std::runtime_error("Error: Unable to open input file.");
    }

    int num_vectors;
    file >> num_vectors;

    std::vector<std::vector<int16_t>> vectors;
    for (int i = 0; i < num_vectors; ++i) {
        int vec_size;
        file >> vec_size;

        std::vector<int16_t> vec(vec_size);
        for (int j = 0; j < vec_size; ++j) {
            file >> vec[j];
        }
        vectors.push_back(vec);
    }

    return vectors;
}









