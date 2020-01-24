//
// Created by aharon on 24/01/2020.
//

#ifndef EX4__MYCLAIENTHANDLER_H_
#define EX4__MYCLAIENTHANDLER_H_

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
#include "MyClientHandler.h"
#include "Solver.h"
#include "ClientHandler.h"
#include "Matrix.h"


typedef vector<vector<int>> matrix;


class MyClientHandler : public ClientHandler {

private:
    Solver<Matrix, vector<string>>* solver;
    CacheManager<string, vector<string>> *cache;

public:
    MyClientHandler(Solver<Matrix, vector<string>>* sol, CacheManager<string, vector<string>>* cacheManager): solver(sol),
                                                                                                              cache(cacheManager){};
    void handleClient(int socket) {

        char buffer[1024] = {0};
        matrix problem;
        vector<string> solution;
        string message = " ";
        string strProblem = " ";
        int colRow = 3;
        int lineNum = 0;

        while ((read(socket, buffer, 1024)) && (colRow > 0)) {
            char delimiter = ',';
            int m = 0;
            int j = 0;
            if (!strcmp(buffer, "end")) {
                colRow--;
            } else {
                if (colRow < 3) {
                    colRow--;
                }

                for (int i = 0; buffer[i] != '\n'; i++) {
                    vector<int> v;
                    // find next value
                    while ((buffer[j] != delimiter) && (buffer[j] != '\0')) {
                        j++;
                    }
                    // separate value from the rest of the string
                    string token = "";
                    while (m < j) {
                        token += buffer[m];
                        m++;
                    }
                    m++;
                    if(lineNum == 0) {
                        v.push_back(stoi(token));
                        problem.push_back(v);
                    } else{
                        problem[i].push_back(stoi(token));
                    }
                    j++;
                    strProblem += token + " ";
                }
            }
            lineNum ++;
        }

        //searching for solution in the cache
        if (this->cache->inCache(strProblem)) {
            solution = this->cache->getSolution(strProblem);
            //if solution wasn't found create one
        } else {
            solution = this->solver->solve(problem);
            this->cache->intoCache(strProblem, solution);
        }

        for (int i = 0; i < solution.size(); i++) {
            message = message + solution[i];
        }

        write(socket, message.c_str(), message.length());
    }
    ~MyClientHandler() {}
};
#endif //EX4__MYCLAIENTHANDLER_H_
