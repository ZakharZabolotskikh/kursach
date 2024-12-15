/** @file
* @author Заболотских З.В.
* @version 1.0
* @date 15.12.2024
* @copyright ИБСТ ПГУ
* @warning Это учебный пример
*/
#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Vector.h"

class ServerConnection {
public:
    ServerConnection(const std::string& ip, uint16_t port);
    void connect();
    void send_vectors(const std::vector<Vector>& vectors);
    void close();
    int get_socket() const { return sock; }

private:
    std::string ip;
    uint16_t port;
    int sock;
};

#endif // SERVER_CONNECTION_H
