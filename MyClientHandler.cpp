//
// Created by yaffa on 13/01/2020.
//

#include "General.h"


MyClientHandler<P,S>::MyClientHandler(const Solver<matrix, matrix> &sol, const CacheManager<matrix, matrix> cacheManager):
        solver(sol), cache(cacheManager) {}


void MyTestClientHandler<matrix, matrix>::handleClient(int socket) {

    char buffer[1024] = {0};
    matrix problem;
    matrix solution;
    string message = " ";

    while (read(client_socket, buffer, 1024)) {
        char delimiter = ',';
        int m = 0;
        int j = 0;
        if (!strcmp(buffer, "end")) {
            break;
        }

        vector<char> v;
        for (int i = 0; buffer[i] != '\n'; i++) {
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

            v.push_back(strtof((string(token)).c_str(), 0));

            j++;
        }

        problem.push_back(v);
    }

    //searching for solution in the cache
    if (buffer.inCache) {
        solution = cacheManager.solution(problem);
        //if solution wasn't found create one
    } else {
        solution = solver.solve(problem);
        cache.intoCache(problem, solution);
    }

    for (int i = 0; i < solution.size; i++) {
        for (int j = 0; j < solution[i].size; j++) {
            message += solution[j];
        }
    }

    write(socket, message.c_str(), message.length());
}