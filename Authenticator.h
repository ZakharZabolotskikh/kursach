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
 * @brief A class to handle user authentication using password hashing and salting.
 */
class Authenticator {
public:
    /**
     * @brief Constructs an Authenticator object with the specified login and password.
     * 
     * @param login The user's login/username.
     * @param password The user's password.
     */
    Authenticator(const std::string& login, const std::string& password);
    
    /**
     * @brief Performs the authentication process over a given socket.
     * 
     * @param socket The socket descriptor through which the authentication data will be transmitted.
     * @throws std::runtime_error If the authentication process fails.
     */
    void authenticate(int socket);

private:
    /**
     * @brief Computes a random salt value.
     * 
     * @return A hexadecimal representation of the salt.
     */
    std::string compute_salt();

    /**
     * @brief Generates a hashed value of the password combined with the given salt.
     * 
     * @param salt16 A 16-character hexadecimal salt value.
     * @return A hexadecimal representation of the resultant hash.
     */
    std::string generate_hash(const std::string& salt16);

    std::string login;    ///< The user's login/username.
    std::string password; ///< The user's password.

    friend class TestAuthenticator; ///< Allows TestAuthenticator to access private methods for testing.
};

#endif // AUTHENTICATOR_H



 
