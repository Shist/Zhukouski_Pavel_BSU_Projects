#include "RSA.hpp"
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/integer/mod_inverse.hpp>
#include <boost/random.hpp>

namespace RSA
{
static boost::multiprecision::uint128_t random_prime ()
{

    boost::random::mt11213b base_gen (clock ());
    boost::random::independent_bits_engine <boost::random::mt11213b, 128, boost::multiprecision::uint128_t>
        gen (base_gen);
    //
    // We must use a different generator for the tests and number generation, otherwise
    // we get false positives.
    //
    boost::random::mt19937 gen2 (clock ());

    while (true)
    {
        boost::multiprecision::uint128_t n = gen ();
        if (n > UINT64_MAX && miller_rabin_test (n, 25, gen2))
        {
            // Value n is probably prime, see if (n-1)/2 is also prime:
            if (miller_rabin_test ((n - 1) / 2, 25, gen2))
            {
                return n;
            }
        }
    }

    BOOST_ASSERT(false);
    return 0;
}

void GenerateKeys (PublicKey &publicKey, PrivateKey &privateKey)
{
    boost::multiprecision::int256_t q = random_prime ();
    boost::multiprecision::int256_t p = random_prime ();

    publicKey.n = p * q;
    privateKey.n = publicKey.n;
    boost::multiprecision::int256_t secret = (p - 1) * (q - 1);

    do
    {
        publicKey.e = random_prime ();
    }
    while (publicKey.e >= secret || boost::multiprecision::gcd (publicKey.e, secret) > 1);

    privateKey.d = boost::integer::mod_inverse (publicKey.e, secret);
}

void Encode (const PublicKey &publicKey, boost::multiprecision::int256_t &value)
{
    value = boost::multiprecision::powm (value, publicKey.e, publicKey.n);
}

void Decode (const PrivateKey &privateKey, boost::multiprecision::int256_t &value)
{
    value = boost::multiprecision::powm (value, privateKey.d, privateKey.n);
}
}
