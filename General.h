//
// Created by aharon on 13/01/2020.
//

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

namespace server_side {
// namespace Q::V { // C++17 alternative to the above two lines
class Server {
  virtual void open(int port, ClientHandler myHandler) = 0;
  virtual void stop() = 0;

};
}


class SerialServer : public server_side::Server{

 public:
  void open(int port,ClientHandler myHandler) override ;



};

CacheManager
class CacheManager {

 public:
  bool isExist(int port,ClientHandler myHandler) override ;



};