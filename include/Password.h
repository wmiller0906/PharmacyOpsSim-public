#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>

class Password {
    public:
        // Generates a random alphanumeric 8-character password
        static std::string generate();

        // Hashes a plaintext password using libsodium
        static std::string hash(const std::string& password);

        // Verifies a plaintext password against a stored hash
        static bool verify(const std::string& hash, const std::string& input);
};

#endif