#include <iostream>
#include <thread>
#include <string>
#include <atomic>
#include "../lib/library.cpp"

std::atomic<bool> bufferReady(false);
std::string sharedBuffer;

void inputThread() {
    while (true) {
        std::string input;
        std::cout << "Введите строку: ";
        std::cin >> input;

        if (input.length() > 64 || !std::all_of(input.begin(), input.end(), ::isdigit)) {
            std::cout << "Некорректная строка!" << std::endl;
            continue;
        }

        sortAndReplace(input);
        sharedBuffer = input;
        bufferReady = true;
    }
}

void processThread() {
    while (true) {
        if (bufferReady) {
            std::cout << "Получено: " << sharedBuffer << std::endl;
            int sum = sumOfDigits(sharedBuffer);
            std::cout << "Сумма чисел: " << sum << std::endl;
            bufferReady = false;
        }
    }
}

int main() {
    std::thread t1(inputThread);
    std::thread t2(processThread);

    t1.join();
    t2.join();

    return 0;
}
