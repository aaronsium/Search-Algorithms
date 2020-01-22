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
#include <string>
#include <functional>

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
namespace boot {
class Main{
 public:
  void main(int arg, char *argv[]);
};

}


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
  virtual S solve(P problem) = 0;
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
  virtual S getSolution(P problem) = 0; //returning solution to problem that is in the cache
  virtual void intoCache(P problem, S solution) = 0; //inserting new solution
  virtual ~CacheManager() {}
};

class MyClientHandler : public ClientHandler {

 private:
  Solver<matrix, vector<string>>* solver;
  CacheManager<matrix, vector<string>> *cache;

 public:
  MyClientHandler(Solver<matrix, vector<string>>* sol, CacheManager<matrix, vector<string>>* cacheManager): solver(sol),
                                                                                                            cache(cacheManager){};
  void handleClient(int socket);
  ~MyClientHandler() {}
};

class MyTestClientHandler : public ClientHandler {

private:
  Solver<string, string> *solver;
  CacheManager<string, string> *cache;

public:
    MyTestClientHandler(Solver<string, string>* sol, CacheManager<string, string>* cacheManager);
    void handleClient(int socket) ;
    ~MyTestClientHandler() {}
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
template<class P, class S>
class FileCacheManager : public CacheManager<P, S> {
 private:
  list<pair<string, strVector>> cacheList;
  map<string, typename list<pair<string, strVector>>::iterator> mapPointers;
  unsigned int capacity = 5;

 public:
  FileCacheManager();
  string hashing(P problem);
  string Convertstr(size_t sz);// convert size_t to string
  virtual bool inCache(P problem);
  virtual S getSolution(P problem);
  virtual void intoCache(P problem, S solution) ;
  void lru(string key);
  void wFile(string key, S solution);
  S rFile(string key);
  virtual ~FileCacheManager() {}
};

class StringReverser : public Solver<string, string> {

 public:
  virtual string solve(string problem) override;
  ~StringReverser() {}
};

class Point {

 private:
  double x;
  double y;

 public:
  Point(double x, double y);
  double getX();
  double getY();
  bool compare(Point other);
};

template<class T>
class State {

private:
    T status;
    double cost;
    State<T> *cameFrom;

public:
    State(T state, State<T>* came_from, double cost);
    bool equals(State<T> s);
    void SetCameFrom(State<T>* came_from);
    double GetCost() const;
    void SetCost(double cost);
    State<T>* getPrevious();
    bool operator<(State<T>* s1);
    T getStatus();
};


namespace std {

template<class T>
struct hash<State<T>> {
  size_t operator ()(State<T> value) const {
    return static_cast<size_t>(value);
  }
};
}

template<class T>
class Searchable {
protected:
    State<Point> initial;
    State<Point> goal;
 public:
    Searchable();
  virtual State<T> getInitialState() = 0;
  virtual bool isGoalState(State<T>) = 0;
  virtual list<State<T>> getAllPossibleStates(State<T> s) = 0;
  virtual int NodesEvaluated() = 0;
  virtual vector<string> adaptSolution(vector<State<Point>> stateVector)=0;
  virtual ~Searchable() {}
};

template<class T, class S>

class Searcher {
 protected:
  int evaluatedNodes;

 public:
  Searcher();
  virtual S search(Searchable<T>* searchable) = 0;
  int NodesEvaluated();
  virtual ~Searcher() {}
  void SetEvaluatedNodes(int evaluated_nodes);
};

template<class T, class S>
class BestFirstSearch : public Searcher<T, S> {

private:
    priority_queue<State<T>> openList;
    list<State<T>> opened;
    unordered_set<State<T>> closed;

public:
    virtual S search(Searchable<T>* searchable);
    vector<State<T>> backTrace();
    virtual ~BestFirstSearch() {}
};

template<class T, class S>
class BFS : public Searcher<T, S> {
 private:
  unordered_set<State<T>> visited;
 public:
    virtual S search(Searchable<T>* searchable);
  unordered_set<State<T>> backTrace();
  virtual ~BFS() {}
};

class Matrix : public Searchable<Point> {
 private:
  matrix field;
  State<Point> initial;
  State<Point> goal;

 public:
  Matrix(matrix field);
  State<Point> getInitialState() override;
  bool isGoalState(State<Point> current) override;
  vector<State<Point>> getAllPossibleState(State<Point> current);
  int pointCost(State<Point> current);
  vector<string> adaptSolution(vector<State<Point>>);
  string direction(State<Point> s1, State<Point> s2);
  ~Matrix() {};
};


template<class P, class S, class T>
class OA : public Solver<P, S> {
 private:
  Searcher<P, S>* searcher;
 public:
    OA(Searcher<P, S>* searcher1);
  S solve(P problem);
  virtual ~OA() {};
};

template<class T, class S>
class DFS : public Searcher<T, S> {
private:
    stack<State<T>> myStack;
    unordered_set<State<T>> closed;
    list<State<T>> trace;

public:
    virtual S search(Searchable<T>* searchable);
    list<State<T>> backTrace(State<T>);
    virtual ~DFS() {}

};

template<class T, class S>
class AStar : public Searcher<T, S> {
private:
    unordered_set<State<T>> closed;
    priority_queue<State<T>> openList;
    list<State<T>> trace;
    list<State<T>> opened;


 public:
    virtual S search(Searchable<T>* searchable);
    list<State<T>> backTrace(State<T>);

    virtual ~AStar() {}

};

#endif //EX4_GENERAL_H