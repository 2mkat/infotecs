#include "server.h"
#include <iostream>

int main() {
    Server ser;
    ser.launchSocket();
    
    while (true) {
        try {
            ser.RunReviewer();
        }
        catch (std::exception &ex) {
            std::cout << ex.what() << '\n';
        }
    }
    

    return 0;
}