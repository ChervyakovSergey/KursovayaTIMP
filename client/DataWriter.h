#ifndef DATA_WRITER_H
#define DATA_WRITER_H

#include <vector>
#include <string>

class DataWriter {
public:
    void write_results_to_file(const std::string& output_file, const std::vector<int16_t>& results);
};

#endif // DATA_WRITER_H






