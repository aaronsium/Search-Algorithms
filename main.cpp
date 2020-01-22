

#include "General.h"


int main(int arg, char *args[]) {
  MySerialServer server;


  Searcher<matrix,vector<string>> *search;
  search = new BFS<matrix,vector<string>> ();

  Solver<matrix,vector<string>> *solv;
  solv = new OA<matrix,vector<string>,Point>> (search);

  CacheManager<matrix,vector<string>> *cash2;
  cash2 = new FileCacheManager<matrix,vector<string>> ();

  MyClientHandler client(solv,cash2);


  server.open(stoi(args[0]),&client);
  return 0;
}