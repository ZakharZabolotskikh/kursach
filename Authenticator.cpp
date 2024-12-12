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
    namespace CPP = CryptoPP;
    std::string HashAndPass = salt16 + password;

    // Удаляем пробелы и символы переноса строки
    HashAndPass.erase(remove_if(HashAndPass.begin(), HashAndPass.end(), [](unsigned char x) { 
        return std::isspace(x); 
    }), HashAndPass.end());

    CPP::SHA256 hash;
    CPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(digest, (const CPP::byte*)HashAndPass.data(), HashAndPass.size());
    std::string Hash;
    CryptoPP::StringSource(digest, sizeof(digest), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(Hash)));
    std::cout << HashAndPass << "#" << std::endl;
    return Hash;
}
void Authenticator::authenticate(int socket) {
    std::string salt16 = compute_salt();
    std::string hash_sha256 = generate_hash(salt16);

    std::string msg = login + salt16 + hash_sha256;
    send(socket, msg.c_str(), msg.length(), 0);
std::cout<<msg<<"#"<<std::endl;
    char response[8];
    recv(socket, response, sizeof(response), 0);
    if (std::string(response) != "OK") {
        throw std::runtime_error("Authentication failed");
    }
}
