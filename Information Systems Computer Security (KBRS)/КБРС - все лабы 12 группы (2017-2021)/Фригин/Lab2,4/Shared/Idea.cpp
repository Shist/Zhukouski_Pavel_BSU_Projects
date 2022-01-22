#include "Idea.hpp"
#include <cstdint>
#include <boost/random.hpp>
#include <boost/multiprecision/cpp_int.hpp>

typedef void (*idea_gen_key) (uint16_t[52], const uint16_t[8]);

uint16_t mulMod65537 (uint16_t a, uint16_t b)
{
    uint32_t c;
    uint16_t hi, lo;

    if (a == 0)
        return -b + 1;
    if (b == 0)
        return -a + 1;

    c = (uint32_t) a * (uint32_t) b;
    hi = c >> 16;
    lo = c;

    if (lo > hi)
        return lo - hi;
    return lo - hi + 1;
}

int modInverse (int a, int m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1)
    {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process same as
        // Euclid's algo
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

void encrypt (uint16_t subKey[52], const uint16_t key[8])
{
    int i;

    // Generate encryption keys
    for (i = 0; i < 52; i++)
    {
        if (i < 8)
            subKey[i] = key[i];
        else if (i % 8 == 6)
            subKey[i] = (subKey[i - 7] << 9) | (subKey[i - 14] >> 7);
        else if (i % 8 == 7)
            subKey[i] = (subKey[i - 15] << 9) | (subKey[i - 14] >> 7);
        else
            subKey[i] = (subKey[i - 7] << 9) | (subKey[i - 6] >> 7);
    }
}

void decrypt (uint16_t subKey[52], const uint16_t key[8])
{
    int i;
    uint16_t K[52];

    // Compute encryption keys
    encrypt (K, key);

    // Generate dencryption keys
    subKey[0] = modInverse (K[48], 65537);
    subKey[1] = -K[49];
    subKey[2] = -K[50];
    subKey[3] = modInverse (K[51], 65537);

    for (i = 4; i < 52; i += 6)
    {
        subKey[i + 0] = K[52 - i - 2];
        subKey[i + 1] = K[52 - i - 1];

        subKey[i + 2] = modInverse (K[52 - i - 6], 65537);
        if (i == 46)
        {
            subKey[i + 3] = -K[52 - i - 5];
            subKey[i + 4] = -K[52 - i - 4];
        }
        else
        {
            subKey[i + 3] = -K[52 - i - 4];
            subKey[i + 4] = -K[52 - i - 5];
        }

        subKey[i + 5] = modInverse (K[52 - i - 3], 65537);
    }
}

void IDEA (uint16_t data[4], const uint16_t key[8], idea_gen_key func)
{
    int i;
    uint16_t subKey[52];

    // Generate keys
    func (subKey, key);

    uint16_t X0 = data[0];
    uint16_t X1 = data[1];
    uint16_t X2 = data[2];
    uint16_t X3 = data[3];
    uint16_t tmp1, tmp2;

    // Apply 8 rounds
    for (i = 0; i < 8; i++)
    {
        X0 = mulMod65537 (X0, subKey[6 * i + 0]);        // Step 1
        X1 += subKey[6 * i + 1];                        // Step 2
        X2 += subKey[6 * i + 2];                        // Step 3
        X3 = mulMod65537 (X3, subKey[6 * i + 3]);        // Step 4

        tmp1 = X0 ^ X2;                                    // Step 5
        tmp2 = X1 ^ X3;                                    // Step 6

        tmp1 = mulMod65537 (tmp1, subKey[6 * i + 4]);    // Step 7
        tmp2 += tmp1;                                    // Step 8
        tmp2 = mulMod65537 (tmp2, subKey[6 * i + 5]);    // Step 9
        tmp1 += tmp2;                                    // Step 10

        X0 ^= tmp2;
        X1 ^= tmp1;
        X2 ^= tmp2;
        X3 ^= tmp1;

        // Swap X1 and X2
        tmp1 = X1;
        X1 = X2;
        X2 = tmp1;
    }

    tmp1 = X1;
    tmp2 = X2;

    // Apply the half round
    data[0] = mulMod65537 (X0, subKey[6 * i + 0]);
    data[1] = tmp2 + subKey[6 * i + 1];
    data[2] = tmp1 + subKey[6 * i + 2];
    data[3] = mulMod65537 (X3, subKey[6 * i + 3]);
}

namespace Idea
{
void EncodeBlock (Block &block, const Key &key)
{
    IDEA ((uint16_t *) block.data (), (const uint16_t *) key.data (), encrypt);
}

void DecodeBlock (Block &block, const Key &key)
{
    IDEA ((uint16_t *) block.data (), (const uint16_t *) key.data (), decrypt);
}

void GenerateInitialBlock (Block &output)
{
    boost::random::mt11213b base_gen (clock ());
    boost::random::independent_bits_engine <boost::random::mt11213b,
                                            BLOCK_SIZE * 8, uint64_t> gen (base_gen);

    uint64_t initialBlock = gen ();
    *(uint64_t *) &output[0] = initialBlock;
}

StreamProducer::StreamProducer (std::istream &stream)
    : stream_ (stream)
{
}

bool StreamProducer::operator() (Block &block)
{
    if (stream_)
    {
        block.fill (0);
        stream_.read ((char *) &block[0], block.size ());

        if (stream_)
        {
            return true;
        }
        else
        {
            return stream_.gcount () > 0;
        }
    }
    else
    {
        return false;
    }
}

StreamConsumer::StreamConsumer (std::ostream &stream)
    : stream_ (stream)
{
}

void StreamConsumer::operator() (const Block &block)
{
    stream_.write ((const char *) &block[0], block.size ());
}
}

