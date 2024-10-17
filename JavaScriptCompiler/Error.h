#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>

class Error {
public:
    static void reportError(int line, int column, const std::string& message) {
        std::cerr << "Error at line " << line << ", column " << column << ": " << message << std::endl;
    }
};

#endif
