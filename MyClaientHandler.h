//
// Created by aharon on 24/01/2020.
//

#ifndef EX4__MYCLAIENTHANDLER_H_
#define EX4__MYCLAIENTHANDLER_H_

#include "ClientHandler.h"

typedef vector<vector<int>> matrix;


class MyClientHandler : public ClientHandler {

 private:
  Solver<matrix, vector<string>>* solver;
  CacheManager<string, vector<string>> *cache;

 public:
  ~MyClientHandler() {}

  //////////////////////////////////////////////////

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
};

#endif //EX4__MYCLAIENTHANDLER_H_
