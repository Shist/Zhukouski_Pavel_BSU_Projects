#pragma once
#include <boost/multiprecision/cpp_int.hpp>

namespace RSA
{
static const uint8_t MESSAGE_SIZE = 32;

struct PublicKey
{
    static const uint8_t N_SIZE = 32;
    static const uint8_t E_SIZE = 16;

    boost::multiprecision::int256_t n;
    boost::multiprecision::int256_t e;
};

struct PrivateKey
{
    boost::multiprecision::int256_t n;
    boost::multiprecision::int256_t d;
};

void GenerateKeys (PublicKey &publicKey, PrivateKey &privateKey);
void Encode (const PublicKey &publicKey, boost::multiprecision::int256_t &value);
void Decode (const PrivateKey &privateKey, boost::multiprecision::int256_t &value);
}
