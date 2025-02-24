#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include "../lib/mylib.h"

void send_to_server(const std::string& msg);

std::string buffer;
std::atomic<bool> input_done(false);
std::atomic<bool> process_done(false);
std::mutex mtx;
std::condition_variable cv;

bool is_number(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void send_to_server(const std::string& msg) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Ошибка сокета!" << std::endl;
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка подключения!" << std::endl;
        close(sock);
        return;
    }

    send(sock, msg.c_str(), msg.size(), 0);
    close(sock);
}

void input_thread() {
    while (!input_done) {
        std::cout << "Введите строку (не более 64 символов, только цифры): ";
        std::getline(std::cin, buffer);

        if (buffer.length() > 64 || !is_number(buffer)) {
            std::cout << "Ошибка! Строка должна содержать только цифры и быть не более 64 символов." << std::endl;
            continue;
        }

        input_done = true;
        cv.notify_all();
    }
}

void process_thread() {
    while (!input_done) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::lock_guard<std::mutex> lock(mtx);

    sort_and_replace(buffer);
    std::cout << "Обработанная строка: " << buffer << std::endl;

    int sum = sum_of_numbers(buffer);
    std::cout << "Сумма чисел: " << sum << std::endl;

    send_to_server(buffer);

    process_done = true;
    cv.notify_all();
}

int main() {
    std::thread input_thread_obj(input_thread);
    std::thread process_thread_obj(process_thread);

    input_thread_obj.join();
    process_thread_obj.join();

    return 0;
}
