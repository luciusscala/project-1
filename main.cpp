#include <sys/socket.h> //socket functions and constants
#include <netdb.h> // addrinfo 
#include <netinet/in.h> //sockaddr_in and sockaddr_in6
#include <iostream> // print
#include <arpa/inet.h> //internet networkto to presentation

int main() {

    const char* hostname = "fbref.com";

    //initialize input filter; brackets ensure no garbage values, intialize with 0s. 
    struct addrinfo hints{};
    hints.ai_family = AF_UNSPEC; //either ipv4 or ipv6
    hints.ai_socktype = SOCK_STREAM; //tcp socket type (not udp)

    //pointer to results
    struct addrinfo* res;

    //function call to resolve hostname and set res to potential addresses
    getaddrinfo(hostname, "80", &hints, &res); //uses port 80 because that is used for HTTP

    for (struct addrinfo* ptr = res; ptr != nullptr; ptr = ptr->ai_next) {

        char ip[INET6_ADDRSTRLEN];
        void* addr;

        if (ptr->ai_family == AF_INET){
            addr = &((struct sockaddr_in*)ptr->ai_addr)->sin_addr;
        }
        else {
            addr = &((struct sockaddr_in6*)ptr->ai_addr)->sin6_addr;
        }

        inet_ntop(ptr->ai_family, addr, ip, sizeof(ip));

        std::cout << "IP: " << ip << "\n";

    }
}   