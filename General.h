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


typedef vector<vector<int>> matrix;
typedef vector<string> strVector;

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

class Point {

private:
    double x;
    double y;

public:
    Point(int x, int y);
    double getX();
    double getY();
    bool compare(Point other);
};

template<typename T>
class State {

private:
    T status;
    double cost;
    State<T> cameFrom;

public:
    State(T status);
    bool equals(State<T> s);
    T getStatus();
};

template<typename T>
class Searchable {
 public:
  virtual State<T> getInitialState() = 0;
  virtual bool isGoalState(State<T>) = 0;
  virtual list<State<T>> getAllPossibleStates(State<T> s) = 0;
  virtual int NodesEvaluated() = 0;
  virtual ~Searchable() {}
};

template<typename T, typename S>

class Searcher {
 private:
  priority_queue<State<T>> openList;
  int evaluatedNodes;

 public:
  Searcher();
  virtual S search(Searchable<T> searchable) = 0;
  int listSize();
  int NodesEvaluated();
  virtual ~Searcher() {}
};

template<class T>
class Searchable{

public:
    virtual T getInitialState() = 0;
    virtual bool isGoalState(state T) = 0;
    virtual T getAllPossibleState(State T) = 0;
    ~searchable(){};
};

class Matrix:Searchable{

private:
    matrix field;
    State initial;
    State goal;

public:
    Matrix(matrix field, State Initial, State goal);
    virtual State getInitialState();
    virtual bool isGoalState(State current);
    virtual vector<State> getAllPossibleState(State current);
    int getCost(State current);
    ~Matrix(){};
};

#endif //EX4_GENERAL_H