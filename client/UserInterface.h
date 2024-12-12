#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>

class UserInterface {
public:
    void display_help();
    void display_error(const std::string& message);
};

#endif // USER_INTERFACE_H









