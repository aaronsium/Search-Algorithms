//
// Created by yaffa on 13/01/2020.
//

#include "General.h"

template<class P, class S>
MyClientHandler<P, S>::MyClientHandler(const Solver<P,S> &sol, const CacheManager<P,S> cacheManager):solver(sol),
cache(cacheManager) {}

template<class P, class S>
void MyClientHandler<P,S>::handleClient(ifstream input, ofstream output){
    P problem[1024];

    while(input >> problem) {
        if (strcmp(problem, "end")){
            return;
        }
        output << "problem received" << endl;
        //searching for solution in the cache
        if (problem.inCache) {
            output << problem << endl;
        //if solution wasn't found create one
        } else {
            S solution = solver.solve(problem);
            output << solution << endl;
            cache.intoCache(problem, solution);
        }
    }
}


