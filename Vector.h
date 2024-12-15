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

class Vector {
public:
    Vector(uint32_t size, const std::vector<uint64_t>& values)
        : size(size), values(values) {}

    uint32_t size;
    std::vector<uint64_t> values;
};

#endif // VECTOR_H
