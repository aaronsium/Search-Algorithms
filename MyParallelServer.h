//
// Created by omer on 1/24/20.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

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
  int client_socket = 0;
  int server_socket = 0;
  int liveCounter=0;
  int temp_socket=0;
 public:
  void open(int port, ClientHandler *myHandler) {
    //opening a new thread which will run the server
    vector<thread> treadVector;
    for(int i=0; i<10;i++) {
      // copy myHandler
      ClientHandler *newHandler = myHandler->Clone();
      thread serverThread(&MyParallelServer::start, this, newHandler);
      treadVector.push_back(serverThread);
    }
    newSocket(port);
    for(int i=0; i<10;i++) {
      treadVector[i].join();
    }

  }

  void stop() {
    this->isOpen = false;
    close(this->server_socket);
  }

  int newSocket(int port) {
    this->server_socket = server_socket;
    if (server_socket==-1) {
      cerr << "Could not create a socket" << endl;
      return -1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *) &address, sizeof(address))==-1) {
      cerr << "Could not bind the socket to an IP" << endl;
      return -2;
    }

    if (listen(server_socket, 10)==-1) {
      cerr << "Error during listening command" << endl;
      return -3;
    } else {
      this->isOpen = true;
    }
    while (isOpen) {
      cout << "waiting" << endl;
//            timeout
      struct timeval tv;
      tv.tv_sec = 120;
      setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
      //updating the socket by getting a new client
      while (isOpen) {}
    }
  }

  void start(ClientHandler *myHandler) {
    //when server opened we can open client thread
    while(!isOpen){}
    while (isOpen) {
      cout << "newThread" << endl;
      temp_socket = socket(AF_INET, SOCK_STREAM, 0);
      if (temp_socket==-1) {
        cerr << "Error accepting client" << endl;
      } else {
        cout << "client connected" << endl;
      }
      //waiting till client connect
      while (client_socket==0) {}
      myHandler->handleClient(this->client_socket); // need to check about arguments
      cout << "client disconnected" << endl;
      //reset socket
//      client_socket = 0;
    }

    liveCounter++;
    while(liveCounter<10){}
    stop();
  }

  ~MyParallelServer() override {}
  //once server has been opened handel client by calling myHandler.handleClient
};

#endif //EX4_MYSERIALSERVER_H
