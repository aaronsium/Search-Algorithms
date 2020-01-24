
#include "AStar.h"
#include "BestFirstSearch.h"
#include "BFS.h"
#include "CacheManager.h"
#include "ClientHandler.h"
#include "DFS.h"
#include "FileCacheManager.h"
#include "Matrix.h"
#include "MyClientHandler.h"
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "OA.h"
#include "Point.h"
#include "Searchable.h"
#include "Searcher.h"
#include "server_side"
#include "State.h"
#include "State.h"
#include "StringReverser.h"






int main(int arg, char *args[]) {
  MySerialServer server;


  Searcher<Point,vector<string>> *search;
  search = new BestFirstSearch<Point,vector<string>> ();

  Solver<matrix,vector<string>> *solv;
  solv = new OA<matrix,vector<string>,Point>(search);

  CacheManager<string,vector<string>> *cash2;
  cash2 = new FileCacheManager<vector<string>> ();

  MyClientHandler client(solv,cash2);


  server.open(stoi(args[0]),&client);
  return 0;
}