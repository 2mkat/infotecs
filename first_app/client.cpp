#include "client.h"
#include <iostream>
#include <cstring>
#include <algorithm>

bool DataParser::validStr(std::string &str) {
    if (str.size() > 64) {
        return false;
    }
    auto isDigit = [](const auto& i) {return std::isdigit(i); };
    if (!std::all_of(str.begin(), str.end(), isDigit)) {
        return false;
    }

    //for (char symb: str) {
    //    if (!std::isdigit(symb)) {
    //        return false;
    //    }
    //}
    return true;
}

std::queue<char> DataParser::strToKb(std::string &str) {
    std::queue<char> kbStr;
    for (auto sym: str) {
        if (int(sym) % 2 == 0) {
            kbStr.push('K');
            kbStr.push('B');
        } else {
            kbStr.push(sym);
        }
    }
    return kbStr;
}

void DataSender::launchSocket() {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));

    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(1337);
}

void DataSender::runTask() {
    std::string str;
    std::cout << "Enter string: " << '\n';
    std::getline(std::cin, str);
    while (!validStr(str)) {
        std::cout << "This string doesn't correct. It has to consist only from digits and with size <= 64.\nEnter msg again: \n";
        std::getline(std::cin, str);
    } 
    std::sort(str.begin(), str.end(), std::greater<char>());
    std::queue<char> kbStr = strToKb(str);
    std::unique_lock<std::mutex> ul(mu_);
    buffer_ = std::move(kbStr);
    isReady_ = true;
    cond_.notify_one();
}

void DataSender::runSender() {
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

    std::cout << '\n' << "Sum: " << sum << '\n';
    ul.unlock();
    launchSocket();
    sendto(sockfd, &sum, sizeof(int),
            MSG_CONFIRM, (const struct sockaddr *) &address,
            sizeof(address));
}