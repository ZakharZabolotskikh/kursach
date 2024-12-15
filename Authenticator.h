/** @file
* @author Заболотских З.В.
* @version 1.0
* @date 15.12.2024
* @copyright ИБСТ ПГУ
* @warning Это учебный пример
*/
#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <string>
#include <openssl/sha.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>
#include <sys/socket.h>

namespace CPP = CryptoPP;

/**
 * @class Authenticator
 * @brief A class responsible for handling user authentication.
 */
class Authenticator {
public:
    /**
     * @brief Constructs an Authenticator object with provided login and password.
     * @param login The user's login.
     * @param password The user's password.
     */
    Authenticator(const std::string& login, const std::string& password);

    /**
     * @brief Performs authentication using a socket.
     * @param socket The socket descriptor used for communication.
     * @throws std::runtime_error if authentication fails.
     */
    void authenticate(int socket);

private:
    /**
     * @brief Computes a random salt.
     * @return A 16-byte random string used as a salt.
     */
    std::string compute_salt();

    /**
     * @brief Generates a hash using the provided salt.
     * @param salt16 A 16-byte salt used in hash generation.
     * @return A hash of the password concatenated with the salt.
     */
    std::string generate_hash(const std::string& salt16);

    std::string login;   ///< The user's login.
    std::string password;///< The user's password.
};

#endif // AUTHENTICATOR_H
