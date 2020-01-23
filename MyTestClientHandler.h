//
// Created by omer on 1/24/20.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

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
#include "Solver.h"
#include "CacheManager.h"

using namespace std;
using namespace std::literals::chrono_literals;
typedef vector<vector<int>> matrix;
typedef vector<string> strVector;

class MyTestClientHandler : public ClientHandler {

private:
    Solver<string, string> *solver;
    CacheManager<string, string> *cache;

public:
    MyTestClientHandler(Solver<string, string>* sol, CacheManager<string, string>* cacheManager);
    void handleClient(int socket) ;
    ~MyTestClientHandler() override = default;
};

#endif //EX4_MYTESTCLIENTHANDLER_H
