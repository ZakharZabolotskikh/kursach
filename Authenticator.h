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
class Authenticator {
public:
    Authenticator(const std::string& login, const std::string& password);

    void authenticate(int socket);

private:
    std::string compute_salt();
    std::string generate_hash(const std::string& salt16);

    std::string login;
    std::string password;
};

#endif // AUTHENTICATOR_H
