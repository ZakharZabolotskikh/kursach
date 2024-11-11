// Authenticator.cpp
#include "Authenticator.h"
#include <cstring>
#include <unistd.h>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

std::string generate_hash(const std::string &salt) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)salt.c_str(), salt.length(), hash);

    // Преобразование хэша в шестнадцатеричную строку
    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return oss.str();
}

void Authenticator::authenticate(int socket) {
    std::string salt16 = compute_salt();
    std::string hash_sha256 = generate_hash(salt16);

    std::string msg = login + salt16 + hash_sha256;
    send(socket, msg.c_str(), msg.length(), 0);

    char response[8];
    recv(socket, response, sizeof(response), 0);
    if (std::string(response) != "OK") {
        throw std::runtime_error("Authentication failed");
    }
}
