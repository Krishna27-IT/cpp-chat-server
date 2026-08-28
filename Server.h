#pragma once

#include<winsock2.h>
#include<vector>
#include<string>
#include<thread>

class Server{
    private: 
        WSADATA wsaData;
        SOCKET listenSocket;
        sockaddr_in serverAddr;
        int port;
        std::vector<SOCKET> clients;
        
    private:
        bool initializeWinsock();

        bool createSocket();

        bool bindSocket();

        bool startListening();

        SOCKET acceptConnection();

    public:
        Server(int port);
        bool startServer();
        bool run();
        void showClientCount();
        bool receiveMessage(SOCKET clientSocket);
        bool sendMessage(SOCKET clientSocket, const std::string& message);
        void handleClient(SOCKET clientSocket);
};