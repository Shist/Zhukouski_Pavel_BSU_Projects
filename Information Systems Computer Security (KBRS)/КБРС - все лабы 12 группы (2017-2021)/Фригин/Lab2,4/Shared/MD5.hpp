#pragma once

#include <cstdint>
#include <string>
#include <array>

namespace MD5
{
typedef std::array<uint8_t, 16> Hash;
Hash FromString(const std::string &string);
}
