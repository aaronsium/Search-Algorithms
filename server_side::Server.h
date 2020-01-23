//
// Created by omer on 1/24/20.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include "ClientHandler.h"

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

#endif //EX4_SERVER_H
