#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

void sortAndReplace(std::string& input) {
    std::sort(input.begin(), input.end(), std::greater<char>());
    for (char& c : input) {
        if (c % 2 == 0) c = 'К';
    }
}

int sumOfDigits(const std::string& input) {
    int sum = 0;
    for (char c : input) {
        if (std::isdigit(c)) sum += c - '0';
    }
    return sum;
}

bool isValidLength(const std::string& input) {
    if (input.length() > 2 && input.length() % 32 == 0) return true;
    return false;
}
