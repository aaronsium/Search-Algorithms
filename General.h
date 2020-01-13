//
// Created by yaffa on 13/01/2020.
//

#ifndef EX4_GENERAL_H
#define EX4_GENERAL_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/**
 * ClientHandler Interface
 */

class ClientHandler {

 public:
  virtual void handleClient(ifstream input, ofstream output) = 0;
  virtual ~ClientHandler() {}
};


namespace server_side {
/**
 * ClientHandler Interface
 */
class Server {
 public:
  virtual void open(int port, ClientHandler myHandler) = 0;
  virtual void stop() = 0;
  virtual ~Server() {}
};
}

/**
 * Solver Interface
 */

template <class P, class S>
class Solver {

 public:
  S solve (P) = 0;
  virtual ~Solver() {}
};

/**
 * CacheManager Interface
 */

template <class P, class S>
class CacheManager {

 public:
  virtual int handleClient(ifstream input, ofstream output) = 0;
  virtual int inCache() = 0; //if problem is in the cache return 1
  virtual S solution(P) = 0; //returning solution to problem that is in the cache
  virtual void intoCache(P,S) = 0; //inserting new solution
  virtual ~CacheManager() {}
};

template <class P, class S>
class MyClientHandler: public ClientHandler{

 private:
  Solver<P,S> solver;
  CacheManager<P,S> cache;

 public:
  MyClientHandler(const Solver<P,S> &sol, CacheManager<P,S> cacheManager);
  void handleClient(ifstream input, ofstream output);
  ~MyClientHandler() {}
};

class SerialServer : public server_side::Server{

 public:
  void open(int port,ClientHandler myHandler) override ;
  virtual ~SerialServer() {}
  //once server has been opened handel client by calling myHandler.handleClient

};

#endif //EX4_GENERAL_H