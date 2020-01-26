//
// Created by omer on 1/24/20.
//

#ifndef EX4_MyParallelServer_H
#define EX4_MyParallelServer_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
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
#include "MyTestClientHandler.h"
#include "ClientHandler.h"
#include "server_side"

class MyParallelServer : public server_side::Server {
 private:
  bool isOpen = false;
  int PORT = 0;
//  int client_socket = 0;
  int server_socket = 0;
  int liveCounter=0;
  vector<thread> *treadVector = new vector<thread>();
  sockaddr_in address = {0};
  int temp_socket=0;
 public:
  void open(int port, ClientHandler *myHandler) {
    //opening a new thread which will run the server
    for(int i=0; i<10;i++) {

      // copy myHandler
      ClientHandler *newHandler = myHandler->clone();

      treadVector->push_back(thread(&MyParallelServer::start, this, &(*newHandler)));
    }
    newSocket(port);
    for(int i=0; i<10;i++) {
      (*treadVector)[i].join();
    }

  }

  void stop() {
    this->isOpen = false;
    close(this->server_socket);
  }

  int newSocket(int port) {
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);;
    if (server_socket==-1) {
      cerr << "Could not create a socket" << endl;
      return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *) &address, sizeof(address))==-1) {
      cerr << "Could not bind the socket to an IP" << endl;
      return -2;
    }

    if (listen(server_socket, 10)==-1) {
      cerr << "Error during listening command" << endl;
    } else {
      this->isOpen = true;
      cout << "waiting" << endl;
    }
    while (isOpen) {}
  }

  void start(ClientHandler *myHandler) {
    //when server opened we can open client thread
    while (!isOpen) {}
    if (isOpen) {
      //waiting till client connect
//            timeout
      struct timeval tv;
      tv.tv_sec = 20;
      setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
     int  client_socket = accept(server_socket, (struct sockaddr *) &address, (socklen_t *) &address);
      if (client_socket==-1) {
        cerr << "Error accepting client" << endl;
        liveCounter++;
      } else {
        cout << "client connected" << endl;
        isOpen = true;
        myHandler->handleClient(client_socket);; // need to check about arguments
// current client is disconnecting
        cout << "client disconnected" << endl;
      }
      liveCounter++;
      while (liveCounter < 10) {}
      stop();
    }
  }
  ~MyParallelServer() override {
    delete treadVector;
  }
  //once server has been opened handel client by calling myHandler.handleClient
};

#endif //EX4_MyParallelServer_H
