//
// Created by omer on 1/24/20.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <thread>
#include <mutex>
#include <cstddef>
#include <stdlib.h>
#include <string>
#include <functional>
#include "MyTestClientHandler.h"
#include "ClientHandler.h"
#include "server_side::Server.h"

class MySerialServer : public server_side::Server {
private:
    bool isOpen = false;
    int PORT = 0;
    int client_socket = 0;
    int server_socket = 0;
public:
    void open(int port, ClientHandler *myHandler) override;
    void stop() override;
    int newSocket(int port);
    void start(ClientHandler *myHandler);
    ~MySerialServer() override {}
    //once server has been opened handel client by calling myHandler.handleClient
};

#endif //EX4_MYSERIALSERVER_H
