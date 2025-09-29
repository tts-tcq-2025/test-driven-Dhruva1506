#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int add(const std::string &numbers);

private:
    std::vector<std::string> split(const std::string &s, const std::string &delimiter);
};

#endif
