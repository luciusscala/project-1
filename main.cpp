#include <sys/socket.h> //socket functions and constants
#include <netdb.h> // addrinfo 
#include <netinet/in.h> //sockaddr_in and sockaddr_in6
#include <iostream> // print
#include <arpa/inet.h> //internet networkto to presentation
#include <unistd.h> //standard functions for unix like systems

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

       int socketfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol); //creates the socket endpoint with requirements given by addrinfo of domain

       if (connect(socketfd, ptr->ai_addr, ptr->ai_addrlen) == 0) {
            std::cout << "success";
            close(socketfd);
            break; //successful connection that can be used
       }
       std::cout << "fail";
       close(socketfd); //didn't work so close


    }
}   