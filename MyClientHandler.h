//
// Created by aharon on 24/01/2020.
//

#ifndef EX4__MYCLAIENTHANDLER_H_
#define EX4__MYCLAIENTHANDLER_H_

#include "Solver.h"

typedef vector<vector<int>> matrix;


class MyClientHandler : public ClientHandler {

private:
    Solver<matrix, vector<string>>* solver;
    CacheManager<string, vector<string>> *cache;

public:
    MyClientHandler(Solver<matrix, vector<string>>* sol, CacheManager<string, vector<string>>* cacheManager): solver(sol),
                                                                                                              cache(cacheManager){};
    void handleClient(int socket);
    ~MyClientHandler() {}
};
#endif //EX4__MYCLAIENTHANDLER_H_
