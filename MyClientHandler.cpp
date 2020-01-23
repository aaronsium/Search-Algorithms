//
// Created by yaffa on 13/01/2020.
//

#include "General.h"


void MyClientHandler::handleClient(int socket) {

    char buffer[1024] = {0};
    matrix problem;
    vector<string> solution;
    string message = " ";
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
                } else{
                    problem[i].push_back(stoi(token));
                }

                j++;
                if(lineNum == 0) {
                    problem.push_back(v);
                }
            }
        }
        lineNum ++;
    }

    //searching for solution in the cache
    if (this->cache->inCache(problem)) {
        solution = this->cache->getSolution(problem);
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