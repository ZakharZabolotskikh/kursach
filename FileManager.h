/** @file
* @author Заболотских З.В.
* @version 1.0
* @date 15.12.2024
* @copyright ИБСТ ПГУ
* @warning Это учебный пример
*/
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include <cstdint>
#include "Vector.h"

/**
 * @class FileManager
 * @brief A utility class for handling file operations related to vectors and results.
 */
class FileManager {
public:
    /**
     * @brief Reads vectors from a specified file.
     * @param filename The name of the file to read from.
     * @return A vector of Vector objects read from the file.
     */
    static std::vector<Vector> read_vectors(const std::string& filename);

    /**
     * @brief Writes results to a specified file.
     * @param filename The name of the file to write to.
     * @param results A vector of uint64_t results to be written to the file.
     */
    static void write_results(const std::string& filename, const std::vector<uint64_t>& results);
};

#endif // FILE_MANAGER_H
