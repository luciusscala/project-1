The purpose of this project was to send an http request without using any high level libraries. The program reads in a user specified domain, resolves it with libc's getaddrinfo, then opens a tcp connection with the resolved ip and sends a get request to the root. If there is an error (e.g couldn't resolve domain name, tcp connection failed, etc..) the program returns "failed". Otherwise, it prints the web server's response.

To compile and run the program, do g++ main.cpp utils.cpp -o main followed by ./main in your terminal.
