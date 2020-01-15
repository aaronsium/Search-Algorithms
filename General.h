//
// Created by yaffa on 13/01/2020.
//

#ifndef EX4_GENERAL_H
#define EX4_GENERAL_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <thread>
#include <mutex>
#include <cstddef>


using namespace std;
using namespace std::literals::chrono_literals;

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
 * Server Interface
 */
class Server {
 public:
  virtual void open(int port, ClientHandler *myHandler) = 0;
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
  virtual bool inCache(P problem) = 0; //if problem is in the cache return 1
  virtual S solution(P problem) = 0; //returning solution to problem that is in the cache
  virtual void intoCache(P problem,S solution) = 0; //inserting new solution
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

class MySerialServer : public server_side::Server{
 private:
  bool isOpen = false;
  int PORT=0;
  int client_socket=0;
  int server_socket=0;
 public:
  void open(int port,ClientHandler *myHandler) override ;
  void stop() override ;
  int newSocket(int port);
  void start(ClientHandler *myHandler) ;
  virtual ~MySerialServer() {}
  //once server has been opened handel client by calling myHandler.handleClient

};
template <class P, class S>
class FileCacheManager: public CacheManager {

 public:
  virtual int handleClient(ifstream input, ofstream output) = 0;
  virtual bool inCache(P problem) = 0;
  virtual S solution(P problem) = 0;
  virtual void intoCache(P problem,S solution) = 0;
  virtual ~FileCacheManager() {}
};
#endif //EX4_GENERAL_H