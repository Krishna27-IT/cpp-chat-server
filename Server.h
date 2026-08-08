#pragma once

#include<winsock2.h>
#include<vector>

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

        bool acceptConnection();

    public:
        Server(int port);
        bool startServer();
        bool run();
};