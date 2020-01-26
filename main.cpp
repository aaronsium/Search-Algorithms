
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

  Searcher<Point,vector<string>> *search;
  search = new BFS<Point,vector<string>> ();

  Solver<Matrix,vector<string>> *solv;
  solv = new OA<Matrix,vector<string>,Point>(search);

  CacheManager<string,vector<string>> *cash2;
  cash2 = new FileCacheManager<vector<string>> ();

  MyClientHandler client(solv,cash2);



  server.open(atoi(args[1]),&client);
  return 0;
}