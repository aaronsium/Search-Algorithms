//
// Created by yaffa on 13/01/2020.
//

#include "General.h"


MyTestClientHandler<strring, string>::MyClientHandler(const Solver<strring, string> &sol, const CacheManager<strring, string> cacheManager):solver(sol),
cache(cacheManager) {}

void MyTestClientHandler<strring, string>::handleClient(int socket) {

    char buffer[1024] = {0};
    vector <vector<char>> problem;
    string solution;

    while (read(client_socket, buffer, 1024)) {
        if (strcmp(buffer, "end")) {
            break;
        }

        //searching for solution in the cache
        if (buffer.inCache) {
            solution = cacheManager.solution(buffer);
            //if solution wasn't found create one
        } else {
            solution = solver.solve(problem);
            cache.intoCache(buffer, solution);
        }

        write(socket, message.c_str(), message.length());
    }
}
//    vector<char> v;
//    for(int i = 0; buffer[i] != '\n'; i++){
//        v.push_back(buffer[i]);
//    }
//
//    problem.push_back(v);



