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
#include <algorithm>

typedef vector<vector<int>> matrix;

class MyClientHandler : public ClientHandler {

 private:
  Solver<Matrix, vector<string>> *solver;
  CacheManager<string, vector<string>> *cache;

 public:
  MyClientHandler(Solver<Matrix, vector<string>> *sol, CacheManager<string, vector<string>> *cacheManager)
      : solver(sol),
        cache(cacheManager) {};
  void handleClient(int socket) {

    char buffer[1024] = {0};
    matrix problem;
    vector<string> solution;
    string message = " ";
    string strProblem = " ";
    bool isN = false;
    int countStr = 0;
    bool check = true;
    string tempStr;
    int maxLine = 0;
    int colCounter = 0;
      int rowCounter = 0;
    while (check) {
      char buffer[1024] = {0};
      read(socket, buffer, 1024);
      string copy(buffer);
      if (copy.find("end")!=std::string::npos) {
        check = false;
      }
      tempStr = tempStr + copy;
    }
    char *temp12 = const_cast<char *>(tempStr.c_str());
    char *tempBuffer = strtok(temp12, "\n");
    while (tempBuffer!=NULL) {
      char delimiter = ',';
      int m = 0;
      int j = 0;
      if (!strcmp(tempBuffer, "end")) {
          tempBuffer = NULL;
          continue;
      } else {
        string str = tempBuffer;
        str = str + "\n";
          int i = 0;
        for (i; str[m - 1]!='\n'; i++) {
          vector<int> v;
          // find next value
          while ((str[j]!=delimiter) && (str[j]!='\n')) {
            j++;
          }
          // separate value from the rest of the string
          string token = "";
          while (m < j) {
            token += str[m];
            m++;
          }
          m++;
          if (colCounter == 0 || i > colCounter) {
              while (v.size() < rowCounter){
                  v.push_back(-1);
              }
            v.push_back(atoi(token.c_str()));
            problem.push_back(v);
          } else {
            problem[i].push_back(atoi(token.c_str()));
          }
          j++;
          strProblem += token + " ";
            if(i > colCounter){
                colCounter = i;
            }
        }
          rowCounter++;
//          cout << strProblem << endl;
        strProblem = "";
      }
      tempBuffer = strtok(NULL, "\n");
    }
      for(int q = rowCounter-2; q < problem[0].size(); q++){
          for(int p = 2; p < problem.size();p++){
              problem[p].push_back(-1);
          }}

      for(int q = 0; q < problem[0].size(); q++){
          for(int p = 0; p < problem.size();p++){
              cout << problem[p][q] << " ";
          }
          cout << endl;
      }
    cout << "yyyyy" << endl;
    //searching for solution in the cache
    if (this->cache->inCache(strProblem)) {
      solution = this->cache->getSolution(strProblem);
      //if solution wasn't found create one
    } else {///// אולי בלבול יכול להיות שהצריך לשלוח את המטריצה הגדולה (סולבר)
      solution = this->solver->solve(Matrix(problem));
      this->cache->intoCache(strProblem, solution);//////hash להוסיף
    }

    for (int i = 0; i < solution.size(); i++) {
      message = message + solution[i];/// להוסיך רווח
    }

    write(socket, message.c_str(), message.length());
  }
  ~MyClientHandler() {}
};
#endif //EX4__MYCLAIENTHANDLER_H_
