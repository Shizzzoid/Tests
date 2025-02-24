#include "mylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

void sort_and_replace(std::string& str) {
    std::vector<int> numbers;
    std::string temp;

    for (char c : str) {
        if (std::isdigit(c)) {
            temp += c;
        } else {
            if (!temp.empty()) {
                numbers.push_back(std::stoi(temp));
                temp.clear();
            }
        }
    }
    if (!temp.empty()) {
        numbers.push_back(std::stoi(temp));
    }

    std::sort(numbers.rbegin(), numbers.rend());

    for (int num : numbers) {
        std::string num_str = std::to_string(num);
        size_t pos = str.find(num_str);
        if (pos != std::string::npos && num % 2 == 0) {
            str.replace(pos, num_str.length(), "КВ");
        }
    }
}

int sum_of_numbers(const std::string& str) {
    int sum = 0;
    for (char c : str) {
        if (std::isdigit(c)) {
            sum += c - '0';
        }
    }
    return sum;
}

bool check_length(const std::string &str) {
    return str.length() > 2 && str.length() % 32 == 0;
}
