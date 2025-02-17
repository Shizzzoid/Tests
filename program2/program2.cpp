#include "../lib/library.h"
#include "../lib/library.cpp"
#include <iostream>
#include <thread>
#include <string>

void waitForData()
{
    while (true)
    {
        std::string input;
        std::cout << "Введите строку: ";
        std::cin >> input;

        if (isValidLength(input))
        {
            std::cout << "Получены валидные данные: " << input << std::endl;
        }
        else 
        {
            std::cout << "Ошибка: неверная длина данных!" << std::endl;
        }
    }
}

int main() 
{
    std::thread t(waitForData);
    t.join();

    return 0;
}