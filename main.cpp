#include "utils.h"
#include <string>
#include <iostream>

int main() {
    std::string hostname;
    char* result;

    std::cout << "Enter a hostname: " << std::endl;
    std::cin >> hostname;

    const char* host_cstr = hostname.c_str();

    int status = get_root(host_cstr, &result);

    if (status == 0){
        std::cout << result << std::endl;
        return 0;
    }
    else {
        std::cout << "failed" << std::endl;
    }
    return 1;
}   