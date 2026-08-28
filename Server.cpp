#include "Server.h"
#include <iostream>
#include <ws2tcpip.h>
#include <cstring>

Server::Server(int port){
    this->port = port;
    listenSocket = INVALID_SOCKET;
}

bool Server::initializeWinsock(){
    int status = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(status == 0) return true;
    return false;
}

bool Server::createSocket(){
    listenSocket = socket(AF_INET,SOCK_STREAM,0);
    if(listenSocket == INVALID_SOCKET) return false;
    return true;
}

bool Server::bindSocket(){
    ZeroMemory(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(port);

    int result = bind(listenSocket,(SOCKADDR *) &serverAddr,sizeof(serverAddr));
    if(result == SOCKET_ERROR) return false;
    return true;
}

bool Server::startListening(){
    if(listen(listenSocket,SOMAXCONN) == SOCKET_ERROR) return INVALID_SOCKET;
    return true;
}

SOCKET Server::acceptConnection(){
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket;
    clientSocket = accept(listenSocket,(SOCKADDR *) &clientAddr, &clientAddrSize);
    if(clientSocket == INVALID_SOCKET) return false;
    return clientSocket;
}

bool Server::startServer(){
    if(!initializeWinsock()){
        std::cerr<<"WSAStartup failed!\n";
        return false;
    }

    if(!createSocket()){
        std::cerr<<"Socket creation failed!\n";
        return false;
    }

    if(!bindSocket()){
        std::cerr<<"Bind failed!\n";
        return false;
    }

    if(!startListening()){
        std::cerr<<"Listen failed!\n";
        return false;
    }

    return true;
}

bool Server::run(){
    while(true){
        SOCKET clientSocket = acceptConnection();
        if(clientSocket == INVALID_SOCKET){
            return false;
        }

        clients.push_back(clientSocket);
        showClientCount();

        std::thread clientThread(&Server::handleClient,this,clientSocket);
        clientThread.detach();
    }
}

void Server::showClientCount(){
    std::cout << "Connected clients: " << clients.size() << '\n';
}

bool Server::receiveMessage(SOCKET clientSocket){
    char buffer[1024];
    int bytesReceived = recv(clientSocket,buffer,sizeof(buffer)-1,0);

    if(bytesReceived > 0){
        buffer[bytesReceived] = '\0';
        std::cout<<"Message: "<<buffer<<'\n';
        return true;
    }else if(bytesReceived == 0){
        std::cout<<"Connection Closed!"<<std::endl;
        return false;
    }else{
        std::cout<<"recv Failed: "<<WSAGetLastError()<<std::endl;
        return false;
    }

    return true;
}

bool Server::sendMessage(SOCKET clientSocket, const std::string& message){
    int bytesSent = send(clientSocket, message.c_str(), message.length(),0);

    if(bytesSent == SOCKET_ERROR){
        return false;
    }

    return true;
}

void Server::handleClient(SOCKET clientSocket){
    receiveMessage(clientSocket);
    sendMessage(clientSocket, "Welcome to Server!");
}