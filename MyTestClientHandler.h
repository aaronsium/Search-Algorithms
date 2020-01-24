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
    MyTestClientHandler(Solver<string, string>* sol, CacheManager<string, string>* cacheManager){
        this->solver= sol;
        this->cache = cacheManager;
    }

    void handleClient(int socket) {

        char buffer[1024] = {0};
        string solution;

        while (read(socket, buffer, 1024)) {
            if (!strcmp(buffer, "end")) {
                break;
            }

            //searching for solution in the cache
            if (this->cache->inCache(buffer)) {
                solution = this->cache->getSolution(buffer);
                //if solution wasn't found create one
            } else {
                solution = solver-> solve(buffer);
                this->cache->intoCache(buffer, solution);
            }

            write(socket, solution.c_str(), solution.length());
        }
    }

    ~MyTestClientHandler() override = default;
};

#endif //EX4_MYTESTCLIENTHANDLER_H
