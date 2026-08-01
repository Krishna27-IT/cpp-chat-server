#pragma once

#include<winsock2.h>

class Server{
    private: 
        WSADATA wsaData;
        SOCKET listenSocket;
        sockaddr_in serverAddr;
        int port;
        
    private:
        bool initializeWinsock();

        bool createSocket();

        bool bindSocket();

        bool startListening();

    public:
        Server(int port);
        bool startServer();
};