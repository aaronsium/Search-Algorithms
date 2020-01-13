//
// Created by yaffa on 13/01/2020.
//

#ifndef EX4_GENERAL_H
#define EX4_GENERAL_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * ClientHandler Interface
 */

class ClientHandler {

 public:
  virtual int handleClient(ifstream input, ofstream output) = 0;
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
  virtual ~CacheManager() {}
};

template <class P, class S>
class MyClientHandler: public ClientHandler{

 private:
  Solver solver;

 public:
  MyClientHandler(Solver &solver);

  virtual int handleClient(ifstream input, ofstream output) = 0;
  virtual ~MyClientHandler() {}
};

class SerialServer : public server_side::Server{

 public:
  void open(int port,ClientHandler myHandler) override ;
  virtual ~SerialServer() {}



};

#endif //EX4_GENERAL_H