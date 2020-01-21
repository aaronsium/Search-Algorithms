//
// Created by yaffa on 13/01/2020.
//

#include "General.h"


MyClientHandler::MyClientHandler(Solver<matrix, vector<string>>* sol, CacheManager<matrix, vector<string>>* cacheManager){
        this->solver= sol;
        this->cache = cacheManager;
}


void MyClientHandler::handleClient(int socket) {

    char buffer[1024] = {0};
    matrix problem;
    vector<string> solution;
    string message = " ";
    int colRow = 3;

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

            vector<int> v;
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
    }

    //searching for solution in the cache
    if (this->cache->inCache(problem)) {
        solution = this->cache->solution(problem);
        //if solution wasn't found create one
    } else {
        solution = this->solver->solve(problem);
      this->cache->intoCache(problem, solution);
    }

    for (int i = 0; i < solution.size(); i++) {
        message = message + solution[i];
    }

    write(socket, message.c_str(), message.length());
}