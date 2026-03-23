#include <netdb.h>
#include <iostream>
#include <unistd.h>

const char* PORT = "80";

int get_root(const char* hostname, char** result){

    if (result == nullptr){
        return 1;
    }

    const std::string request = 
        "GET / HTTP/1.1\r\n"
        "Host: " + std::string(hostname) + "\r\n"
        "Connection: close\r\n"
        "\r\n";
    
    struct addrinfo hints{};
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM; 
    struct addrinfo* res;

    if (getaddrinfo(hostname, PORT, &hints, &res) != 0){
        return 1;
    }

    

    for (struct addrinfo* ptr = res; ptr != nullptr; ptr = ptr->ai_next){

        int socketfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (socketfd == -1){
            continue;
        }

        if (connect(socketfd, ptr->ai_addr, ptr->ai_addrlen) == 0) {

            ssize_t sendbytes = send(socketfd, request.c_str(), request.size(), 0);
            if (sendbytes == -1){
                if (ptr->ai_next != nullptr){
                    continue;
                }
                else{
                    return 1;
                }
            }

            ssize_t recvbytes;
            
            char buffer[1024];
            std::string received;

            while ((recvbytes = recv(socketfd, buffer, sizeof(buffer), 0)) > 0) {
                received.append(buffer, recvbytes);
            }

            close(socketfd);

            if (recvbytes == -1) {
                freeaddrinfo(res);
                return 1;
            }
            
            size_t rsize = received.size();
            *result = new char[rsize + 1];
            std::memcpy(*result, (received.c_str()), rsize);
            (*result)[rsize] = '\0';
            break;
        }
        else{
            close(socketfd);
            if (ptr->ai_next != nullptr){
                continue;
            }
            else{
                freeaddrinfo(res);
                return 1;
            }
        }
    }
    freeaddrinfo(res);
    return 0;

}