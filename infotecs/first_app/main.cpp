#include "server.h"
#include <iostream>
#include <thread>

int main() {
    DataSender task;
    while (true) {
        try {
            std::thread thread_one(&DataSender::runTask, std::ref(task));
            std::thread thread_two(&DataSender::runSender, std::ref(task));

            thread_one.join();
            thread_two.join();
        } catch (std::exception &ex) {
            std::cout << ex.what() << '\n';
        }
    }

    return 0;
}
