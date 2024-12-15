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

/**
 * @class ServerConnection
 * @brief Manages a connection to a server for sending vectors.
 */
class ServerConnection {
public:
    /**
     * @brief Constructs a ServerConnection object with specified IP and port.
     * @param ip The IP address of the server.
     * @param port The port number to connect to.
     */
    ServerConnection(const std::string& ip, uint16_t port);

    /**
     * @brief Establishes a connection to the server.
     * @throws std::runtime_error if the connection fails.
     */
    void connect();

    /**
     * @brief Sends a collection of vectors to the server.
     * @param vectors The vectors to be sent.
     * @throws std::runtime_error if sending fails.
     */
    void send_vectors(const std::vector<Vector>& vectors);

    /**
     * @brief Closes the connection to the server.
     */
    void close();

    /**
     * @brief Retrieves the socket descriptor.
     * @return The socket file descriptor.
     */
    int get_socket() const { return sock; }

private:
    std::string ip;    ///< The IP address of the server.
    uint16_t port;     ///< The port number to connect to.
    int sock;          ///< The socket file descriptor.
};

#endif // SERVER_CONNECTION_H
