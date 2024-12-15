/** @file
* @author Заболотских З.В.
* @version 1.0
* @date 15.12.2024
* @copyright ИБСТ ПГУ
* @warning Это учебный пример
*/
#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <vector>

/**
 * @class Vector
 * @brief Represents a mathematical vector with a specified size and values.
 */
class Vector {
public:
    /**
     * @brief Constructs a Vector with given size and values.
     * @param size The number of elements in the vector.
     * @param values The values stored in the vector.
     */
    Vector(uint32_t size, const std::vector<uint64_t>& values)
        : size(size), values(values) {}

    uint32_t size;              ///< The number of elements in the vector.
    std::vector<uint64_t> values; ///< The values of the vector elements.
};

#endif // VECTOR_H
