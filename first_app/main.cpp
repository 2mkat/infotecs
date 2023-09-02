#include "client.h"
#include <iostream>
#include <thread>

// Test string: 1253861794201345684590134913469308656340523450982453247592391237
// After transform -> 9999999KBKBKBKB777KBKBKBKBKB55555555KBKBKBKBKBKBKBKBKB3333333333KBKBKBKBKBKBKB111111KBKBKBKBKB
// Sum of only digits -> 160 (is more than 2 digits and multiple to 32)


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
