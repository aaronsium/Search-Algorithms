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
#include <stdlib.h>


using namespace std;
using namespace std::literals::chrono_literals;

/**
 * ClientHandler Interface
 */

class ClientHandler {

 public:
  virtual void handleClient(int socket) = 0;
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

template<class P, class S>
class Solver {

 public:
  S solve(P problem) = 0;
  virtual ~Solver() {}
};

/**
 * CacheManager Interface
 */
typedef vector<vector<int>> matrix;
typedef vector<string> strVector;

template<class P, class S>
class CacheManager {

 public:
  virtual bool inCache(P problem) = 0; //if problem is in the cache return 1
  virtual S solution(P problem) = 0; //returning solution to problem that is in the cache
  virtual void intoCache(P problem, S solution) = 0; //inserting new solution
  virtual ~CacheManager() {}
};

class MyTestClientHandler : public ClientHandler {

 private:
  Solver<string, string> solver;
  CacheManager<string, string> cache;

 public:
  MyClientHandler(const Solver<string, string> &sol, CacheManager<string, string> cacheManager);
  void handleClient(int socket);
  ~MyClientHandler() {}
};

class MySerialServer : public server_side::Server {
 private:
  bool isOpen = false;
  int PORT = 0;
  int client_socket = 0;
  int server_socket = 0;
 public:
  void open(int port, ClientHandler *myHandler) override;
  void stop() override;
  int newSocket(int port);
  void start(ClientHandler *myHandler);
  virtual ~MySerialServer() {}
  //once server has been opened handel client by calling myHandler.handleClient

};
template<typename P, typename S>
class FileCacheManager : public CacheManager<P, S> {
 private:
  list<pair<string, strVector>> cacheList;
  map<string, typename list<pair<string, strVector>>::iterator> mapPointers;
  unsigned int capacity = 5;

 public:
  string hashing(P problem);
  string Convertstr(size_t sz);// convert size_t to string
  virtual bool inCache(P problem);
  virtual S getSolution(P problem);
  virtual void intoCache(string problem, S solution) = 0;
  void lru(string key);
  void wFile(string key, S solution);
  S rFile(string key);
  virtual ~FileCacheManager() {}
};



class StringReverser : public Solver {

 public:
  virtual string solve(string problem) override;
  ~StringReverser() {}
};
#endif //EX4_GENERAL_H