#include "StringCalculator.h"
#include <vector>
#include <string>
#include <regex>
#include <stdexcept>
#include <algorithm>

int StringCalculator::add(const std::string &numbers) {
  if (numbers.empty()) return 0;

  std::string nums = numbers;
  std::string delimiter = ",|\n";

  // Handle custom delimiter
  if (nums.rfind("//", 0) == 0) {
    std::smatch match;
    std::regex re("//(\\[.*\\]|.)\\n(.*)");
    if (std::regex_match(nums, match, re)) {
      std::string delimDef = match[1].str();
      nums = match[2].str();
      if (delimDef.front() == '[' && delimDef.back() == ']')
        delimDef = delimDef.substr(1, delimDef.size() - 2);

      // Escape regex special characters
      delimiter = std::regex_replace(delimDef,
                                     std::regex(R"([.^$|()\\+*?{}[\]])"),
                                     R"(\\$&)");
    }
  }

  std::regex re_delim(delimiter);
  std::sregex_token_iterator it(nums.begin(), nums.end(), re_delim, -1);
  std::sregex_token_iterator end;

  int result = 0;
  std::vector<int> negatives;

  // Iterate tokens using lambda
  std::for_each(it, end, [&](const std::string &token) {
    if (token.empty()) return;
    int num = std::stoi(token);
    if (num < 0) {
      negatives.push_back(num);
    } else if (num <= 1000) {
      result += num;
    }
  });

  if (!negatives.empty()) {
    std::string msg = "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
      msg += std::to_string(negatives[i]);
      if (i != negatives.size() - 1) msg += " ";
    }
    throw std::runtime_error(msg);
  }

  return result;
}
