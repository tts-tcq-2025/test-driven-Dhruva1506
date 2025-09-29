#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <regex>
#include <iostream>

std::vector<std::string> StringCalculator::split(const std::string &s, const std::string &delimiter) {
    std::vector<std::string> tokens;
    std::regex re(delimiter);
    std::sregex_token_iterator first{s.begin(), s.end(), re, -1}, last;
    for (auto it = first; it != last; ++it) {
        if (!it->str().empty())
            tokens.push_back(it->str());
    }
    return tokens;
}

int StringCalculator::add(const std::string &numbers) {
    if (numbers.empty())
        return 0;

    std::string nums = numbers;
    std::string delimiter = ",|\n";

    // Handle custom delimiter
    if (nums.substr(0, 2) == "//") {
        std::smatch match;
        std::regex re("//(\\[.*\\]|.)\\n(.*)", std::regex::dotall);
        if (std::regex_match(nums, match, re)) {
            std::string delimDef = match[1].str();
            nums = match[2].str();
            // Remove brackets for multi-char delimiter
            if (delimDef.front() == '[' && delimDef.back() == ']')
                delimDef = delimDef.substr(1, delimDef.size() - 2);
            delimiter = std::regex_replace(delimDef, std::regex(R"([.^$|()\\+*?{}[\]])"), R"(\\$&)");
        }
    }

    auto tokens = split(nums, delimiter);
    int result = 0;
    std::vector<int> negatives;

    for (const auto &token : tokens) {
        int num = std::stoi(token);
        if (num < 0)
            negatives.push_back(num);
        else if (num <= 1000)
            result += num;
    }

    if (!negatives.empty()) {
        std::string msg = "negatives not allowed: ";
        for (auto n : negatives)
            msg += std::to_string(n) + " ";
        throw std::runtime_error(msg);
    }

    return result;
}
