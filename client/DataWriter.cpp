#include "DataWriter.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

void DataWriter::write_results_to_file(const std::string& output_file, const std::vector<int16_t>& results) {
    std::ofstream file(output_file);
    if (!file) {
        throw std::runtime_error("Error: Unable to open output file.");
    }

    file << results.size() << " ";
    for (int16_t result : results) {
        file << result << " ";
    }
}









