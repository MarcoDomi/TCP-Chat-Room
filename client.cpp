#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <limits>


sockaddr_in init_sockaddr(){
    //returns a completed sockaddr_in object 
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    return serverAddress;
}


void get_response(int &client_sock){
    //recives and prints a response from server
    char buffer[1024] = {0};
    recv(client_sock, buffer, sizeof(buffer), 0);
    std::cout << "Message from server: " << buffer << std::endl;
}


void socket_communicate(int clientSock, const char *message){
    //handles communication with server

    send(clientSock, message, strlen(message), 0);
    get_response(clientSock);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


int client(){
    //performs main functionality of client program
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress = init_sockaddr();

    connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    const char *message = "Hello, buddy!";
    
    while (true)
        socket_communicate(clientSocket, message);
    
    close(clientSocket);

    return 0;
}


int main(int argc, char* argv[]){

    client();
    return 0;
}