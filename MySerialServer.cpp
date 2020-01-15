//
// Created by aharon on 13/01/2020.
//

#include "General.h"
void MySerialServer::open(int port, ClientHandler *myHandler) {
  //opening a new thread which will run the server
  newSocket(port);
  thread serverThread(&MySerialServer::start, this, myHandler);
  serverThread.detach();

}

int MySerialServer::newSocket(int port) {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
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

  if (listen(server_socket, 5)==-1) {
    cerr << "Error during listening command" << endl;
    return -3;
  } else {
    this->isOpen = true;
  }
  while (isOpen) {
    cout << "waiting" << endl;
    //timeout
    struct timeval tv;
    tv.tv_sec = 120;
    setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

    int client_socket = accept(server_socket, (struct sockaddr *) &address, (socklen_t *) &address);
    if (client_socket==-1) {
      cerr << "Error accepting client" << endl;
      return -4;
    } else {
      isOpen = true;
    }
    //updating the socket by getting a new client
    this->client_socket = client_socket;
    while (client_socket==0) {}
  }
}

void MySerialServer::start(ClientHandler *myHandler) {
  cout << "Server is now listening" << endl;
  //when server opened we can open client thread
  while (isOpen) {
    cout << "Server is now listening" << endl;
    //waiting till client connect
    while (client_socket==0) {}

myHandler->handleClient(this->client_socket);   ; // need to check about arguments
// current client is disconnecting
cout << "client disconnected" << endl;
    //reset socket
    client_socket = 0;
  }
  stop();
}

void MySerialServer::stop() {
  this->isOpen = false;
  close(this->server_socket);
}
