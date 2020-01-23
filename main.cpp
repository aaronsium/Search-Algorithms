
#include "OA.cpp"
#include "Matrix.cpp"
#include "State.cpp"
#include "Point.cpp"
#include "AStar.cpp"
#include "BFS.cpp"
#include "BestFirstSearch.cpp"
#include "DFS.cpp"
#include "FileCacheManager.cpp"
#include "MyClientHandler.cpp"
#include "MySerialServer.cpp"
#include "Searcher.cpp"
#include "StringReverser.cpp"




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