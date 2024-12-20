#pragma once

#include <stdexcept>
#include <string>
#include <ctime>

using namespace std;

class Error : public runtime_error
{
public:
    explicit Error(const string &what_arg, const string &func_name);
    explicit Error(const char *what_arg, const string &func_name);

    string getFuncName() const;
    string getTimestamp() const;

private:
    string func_name;
    string timestamp;
};
