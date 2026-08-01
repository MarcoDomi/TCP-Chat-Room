#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

sockaddr_in init_sockaddr() {
    // fills and returns a sockaddr_in for socket address info
    sockaddr_in serveraddress;

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(8080);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    return serveraddress;
}

void client_communication(int clientSocket){
    //used to send and recieve data from client

    char buffer[1024] = {0}; //buffer is init to all zeroes
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Message from client: " << buffer << std::endl;
    send(clientSocket, buffer, sizeof(buffer), 0);
}

void server(){
    //primary function for server functionality
    
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress = init_sockaddr();

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    while(true){
        client_communication(clientSocket);
    }

    close(clientSocket);
    close(serverSocket);
}


int main(int argc, char* argv[]){
    server();

    return 0;
}