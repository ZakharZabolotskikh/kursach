#include "Authenticator.h"
#include "FileManager.h"
#include "ServerConnection.h"
#include "Vector.h"
#include <UnitTest++/UnitTest++.h>
#include <fstream>

// Extend Authenticator for testing purposes
class TestAuthenticator : public Authenticator {
public:
    using Authenticator::Authenticator;

    std::string test_compute_salt() {
        return compute_salt();
    }

    std::string test_generate_hash(const std::string& salt) {
        return generate_hash(salt);
    }
};

SUITE(AuthenticatorTests) {
    TEST(ComputeSaltTest) {
        TestAuthenticator auth("user", "pass");
        std::string salt1 = auth.test_compute_salt();
        std::string salt2 = auth.test_compute_salt();
        CHECK_EQUAL(16, salt1.size());
        CHECK_EQUAL(16, salt2.size());
        CHECK(salt1 != salt2);
    }

    TEST(GenerateHashTest) {
        TestAuthenticator auth("user", "pass");
        std::string salt = auth.test_compute_salt();
        std::string hash = auth.test_generate_hash(salt);
        CHECK(!hash.empty());
    }

    TEST(AuthenticationFailureTest) {
        Authenticator auth("user", "pass");
        CHECK_THROW(auth.authenticate(-1), std::runtime_error);
    }

    TEST(EmptyLoginOrPasswordTest) {
        Authenticator auth("", "pass");
        CHECK_THROW(auth.authenticate(-1), std::runtime_error);

        Authenticator auth2("user", "");
        CHECK_THROW(auth2.authenticate(-1), std::runtime_error);
    }
}

SUITE(FileManagerTests) {
    TEST(ReadVectorsTest) {
        try {
            std::vector<Vector> vectors = FileManager::read_vectors("test_vectors.bin");
            CHECK_EQUAL(2, vectors.size());
            CHECK_EQUAL(3, vectors[0].size);  // Assuming test data is correct
        } catch (const std::runtime_error& e) {
            CHECK_EQUAL("Failed to open input file", std::string(e.what()));
        }
    }

    TEST(WriteResultsTest) {
        std::vector<uint64_t> results = {1, 2, 3, 4, 5};
        FileManager::write_results("test_results.bin", results);

        std::ifstream file("test_results.bin", std::ios::binary);
        CHECK(file.is_open());
        uint32_t count;
        file.read(reinterpret_cast<char*>(&count), sizeof(uint32_t));
        CHECK_EQUAL(results.size(), count);
    }

    TEST(WriteAndReadResultsTest) {
        std::vector<uint64_t> results = {10, 20, 30, 40};
        FileManager::write_results("temp_results.bin", results);

        std::ifstream file("temp_results.bin", std::ios::binary);
        CHECK(file.is_open());

        uint32_t count;
        file.read(reinterpret_cast<char*>(&count), sizeof(uint32_t));
        CHECK_EQUAL(results.size(), count);

        std::vector<uint64_t> read_results(count);
        file.read(reinterpret_cast<char*>(read_results.data()), count * sizeof(uint64_t));

        for (size_t i = 0; i < results.size(); ++i) {
            CHECK_EQUAL(results[i], read_results[i]);
        }
    }

    TEST(ReadNonExistentFileTest) {
        CHECK_THROW(FileManager::read_vectors("non_existent_vector_file.bin"), std::runtime_error);
    }
}

SUITE(ServerConnectionTests) {
    TEST(ConnectionTest) {
        ServerConnection connection("127.0.0.1", 12345);
        CHECK_THROW(connection.connect(), std::runtime_error);
    }

    TEST(SendVectorsTest) {
        ServerConnection connection("127.0.0.1", 12345);
        try {
            connection.connect();
            std::vector<Vector> vectors = {Vector(3, {1, 2, 3})};
            connection.send_vectors(vectors);
        } catch (const std::runtime_error& e) {
            CHECK_EQUAL("Connection failed", std::string(e.what()));
        }
    }

    TEST(CloseConnectionTest) {
        ServerConnection connection("127.0.0.1", 12345);
        try {
            connection.connect();
        } catch (const std::runtime_error&) {
            // Expected due to no server
        }
        connection.close();
    }

    TEST(InvalidIPAddressTest) {
        ServerConnection connection("invalid_ip", 12345);
        CHECK_THROW(connection.connect(), std::runtime_error);
    }
}

// Main function for running tests
int main() {
    return UnitTest::RunAllTests();
}
