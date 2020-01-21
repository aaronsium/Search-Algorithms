

#include "General.h"


int main(int arg, char *args[]) {
  MySerialServer server;
  OA <matrix,matrix,Point> oa(BFS<Point,vector<string>>);
  FileCacheManager <matrix,vector<string>> cash(BFS<Point,vector<string>>);
  MyClientHandler client(reinterpret_cast<Solver<matrix, vector<std::__cxx11::string>> *>(oa),
                         reinterpret_cast<CacheManager<matrix, vector<std::__cxx11::string>> *>(cash));


  server.open(stoi(args[0]),&client);
  return 0;
}