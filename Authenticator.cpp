#include "Authenticator.h"

Authenticator::Authenticator(const std::string& login, const std::string& password)
    : login(login), password(password) {}

std::string Authenticator::compute_salt() {
    uint64_t salt = (static_cast<uint64_t>(rand()) << 32) | rand();
    std::ostringstream oss;
    oss << std::setw(16) << std::setfill('0') << std::hex << salt;
    return oss.str();
}

std::string Authenticator::generate_hash(const std::string& salt16) {
    std::string combined = salt16 + password;
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(combined.c_str()), combined.length(), digest);
    
    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
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
