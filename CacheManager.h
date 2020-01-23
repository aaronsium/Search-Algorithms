//
// Created by omer on 1/24/20.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

template<class P, class S>
class CacheManager {

public:
    virtual bool inCache(P problem) = 0; //if problem is in the cache return 1
    virtual S getSolution(P problem) = 0; //returning solution to problem that is in the cache
    virtual void intoCache(P problem, S solution) = 0; //inserting new solution
    virtual ~CacheManager() {}
};

#endif //EX4_CACHEMANAGER_H
