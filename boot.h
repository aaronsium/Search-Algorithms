//
// Created by aharon on 30/01/2020.
//

#ifndef EX4__BOOT_H_
#define EX4__BOOT_H_

#include "ClientHandler.h"
#include "BFS.h"
#include "BestFirstSearch.h"
#include "AStar.h"
#include "DFS.h"
#include "BFS.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "MyClientHandler.h"
#include "MySerialServer.h"
#include "OA.h"
#include "Point.h"
#include "Searcher.h"
#include "StringReverser.h"
#include "MyParallelServer.h"
namespace boot {
class Main;
}

class boot::Main {
 public:
  Main() {};
  ~Main() {};
  int main(int arg, char *args[]) {
    MyParallelServer server;

    Searcher<Point, vector<string>> *search;
    search = new AStar<Point, vector<string>>();
    Solver<Matrix, vector<string>> *solv;
    CacheManager<string, vector<string>> *cash2;
    cash2 = new FileCacheManager<vector<string>>();
    vector<ClientHandler *> *handlers = new vector<ClientHandler *>();
    for (int i = 0; i < 10; i++) {
      search = new AStar<Point, vector<string>>();
      solv = new OA<Matrix, vector<string>, Point>(search);
      handlers->push_back(new MyClientHandler(solv, cash2));
    }
    server.open(atoi(args[1]), handlers);
    return 0;
  }
};

#endif //EX4__BOOT_H_
