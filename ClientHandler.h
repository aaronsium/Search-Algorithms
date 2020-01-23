//
// Created by omer on 1/24/20.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

/**
 * ClientHandler Interface
 */

class ClientHandler {

public:
    virtual void handleClient(int socket) = 0;
    virtual ~ClientHandler() {}
};

#endif //EX4_CLIENTHANDLER_H
