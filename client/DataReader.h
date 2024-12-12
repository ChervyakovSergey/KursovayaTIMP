#ifndef DATA_READER_H
#define DATA_READER_H

#include <vector>
#include <string>

class DataReader {
public:
    std::vector<std::vector<int16_t>> read_vectors_from_file(const std::string& input_file);
};

#endif // DATA_READER_H





