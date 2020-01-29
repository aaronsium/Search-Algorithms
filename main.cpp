
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

int main(int arg, char *args[]) {
  MyParallelServer server;

  Searcher<Point, vector<string>> *search;
  search = new BFS<Point, vector<string>>();

  Solver<Matrix, vector<string>> *solv;
  solv = new OA<Matrix, vector<string>, Point>(search);

  CacheManager<string, vector<string>> *cash2;
  cash2 = new FileCacheManager<vector<string>>();
  vector<ClientHandler*>* handlers =new vector<ClientHandler*>();

  MyClientHandler client1(solv, cash2);

  search = new BFS<Point, vector<string>>();
  solv = new OA<Matrix, vector<string>, Point>(search);
  MyClientHandler client2(solv, cash2);

  search = new BFS<Point, vector<string>>();
  solv = new OA<Matrix, vector<string>, Point>(search);
  MyClientHandler client3(solv, cash2);

  search = new BFS<Point, vector<string>>();
  solv = new OA<Matrix, vector<string>, Point>(search);
  MyClientHandler client4(solv, cash2);

  search = new BFS<Point, vector<string>>();
  solv = new OA<Matrix, vector<string>, Point>(search);
  MyClientHandler client5(solv, cash2);

  search = new BFS<Point, vector<string>>();
  solv = new OA<Matrix, vector<string>, Point>(search);
  MyClientHandler client6(solv, cash2);

  search = new BFS<Point, vector<string>>();
  solv = new OA<Matrix, vector<string>, Point>(search);
  MyClientHandler client7(solv, cash2);

  search = new BFS<Point, vector<string>>();
  solv = new OA<Matrix, vector<string>, Point>(search);
  MyClientHandler client8(solv, cash2);

  search = new BFS<Point, vector<string>>();
  solv = new OA<Matrix, vector<string>, Point>(search);
  MyClientHandler client9(solv, cash2);

  search = new BFS<Point, vector<string>>();
  solv = new OA<Matrix, vector<string>, Point>(search);
  MyClientHandler client10(solv, cash2);

  handlers->push_back(&client1);
  handlers->push_back(&client2);
  handlers->push_back(&client3);
  handlers->push_back(&client4);
  handlers->push_back(&client5);
  handlers->push_back(&client6);
  handlers->push_back(&client7);
  handlers->push_back(&client8);
  handlers->push_back(&client9);
  handlers->push_back(&client10);

  server.open(atoi(args[1]),handlers);
  return 0;
}