#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class DataParser {
public:
    bool validStr(std::string &str) {
        if (str.size() >= 64) {
            return false;
        }
//        if (std::all_of(str.begin(), str.end(), [](char i) { return std::isdigit(i); })) {
//            return false;
//        }
        for (char symb: str) {
            if ((int) symb - 48 > 9)
                return false;
        }
        return true;
    }

    std::queue<char> strToKb(std::string &str) {
        std::queue<char> kbStr;
        for (auto sym: str) {
            if ((int(sym) - 48) % 2 == 0) {
                kbStr.push('K');
                kbStr.push('B');
            } else {
                kbStr.push(sym);
            }
        }
        return kbStr;
    }
};

class DataSender : public DataParser {
private:
    std::queue<char> buffer_;
    std::mutex mu_;
    std::condition_variable cond_;
    bool isReady_ = false;
    int sockfd;
    struct sockaddr_in address;

    void launchSocket() {
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&address, 0, sizeof(address));

        
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(3000);

        // if (bind(sockfd, (const struct sockaddr *) &address, sizeof(address)) < 0) {
        //     perror("Bind failed");
        //     exit(EXIT_FAILURE);
        // }
    }

public:
    void runTask() {
        std::string str;
        std::cout << "Enter string: " << '\n';
        std::getline(std::cin, str);
        if (validStr(str)) {
            std::sort(str.begin(), str.end(), [](char a, char b) { return a > b; });
            std::queue<char> kbStr = strToKb(str);
            std::unique_lock<std::mutex> ul(mu_);
            buffer_ = std::move(kbStr);
            isReady_ = true;
            cond_.notify_one();
        }
    }

    void runSender() {
        std::unique_lock<std::mutex> ul(mu_);
        cond_.wait(ul, [&]() { return isReady_; });
        std::queue<char> buffer = std::move(buffer_);
        isReady_ = false;
        unsigned sum = 0;
        char symb;
        while (!buffer.empty()) {
            symb = buffer.front();
            std::cout << symb;
            int num = int(symb) - 48;
            if (num <= 9) {
                sum += num;
            }
            buffer.pop();
        }
        std::cout << '\n';
        ul.unlock();
        auto str_sum = std::to_string(sum);
        launchSocket();
        sendto(sockfd, &sum, sizeof(int),
               MSG_CONFIRM, (const struct sockaddr *) &address,
               sizeof(address));
    }
};

int main() {
    DataSender task;
    try {
        while (true) {
            std::thread thread_one(&DataSender::runTask, std::ref(task));
            std::thread thread_two(&DataSender::runSender, std::ref(task));

            thread_one.join();
            thread_two.join();
        }
    } catch (std::exception &ex) {
        std::cout << ex.what() << '\n';
    }

    return 0;
}
