//
// Created by yaffa on 13/01/2020.
//

#include "General.h"


MyTestClientHandler::MyTestClientHandler(const Solver<string, string> &sol, const CacheManager<string, string> cacheManager):solver(sol),
cache(cacheManager) {}

void MyTestClientHandler<string, string>::handleClient(int socket) {

    char buffer[1024] = {0};
    vector <vector<char>> problem;
    string solution;

    while (read(client_socket, buffer, 1024)) {
        if (!strcmp(buffer, "end")) {
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
