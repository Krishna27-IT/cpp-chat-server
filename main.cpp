#include "Server.h"
#include <iostream>

int main(){
    Server server(8080);
    bool started = server.startServer();

    if(started == true){
        std::cout<<"Server started successfully."<<std::endl;
    }else{
        std::cout<<"Server failed to start."<<std::endl;
    }

    return 0;
}