//
// Created by yaffa on 13/01/2020.
//

#include "General.h"


MyTestClientHandler::MyTestClientHandler(Solver<string, string>* sol, CacheManager<string, string>* cacheManager){
  this->solver= sol;
  this->cache = cacheManager;}


void MyTestClientHandler:: handleClient(int socket) {

    char buffer[1024] = {0};
    string solution;

    while (read(socket, buffer, 1024)) {
        if (!strcmp(buffer, "end")) {
            break;
        }

        //searching for solution in the cache
        if (this->cache->inCache(buffer)) {
            solution = this->cache->getSolution(buffer);
            //if solution wasn't found create one
        } else {
            solution = solver-> solve(buffer);
          this->cache->intoCache(buffer, solution);
        }

        write(socket, solution.c_str(), solution.length());
    }
}
