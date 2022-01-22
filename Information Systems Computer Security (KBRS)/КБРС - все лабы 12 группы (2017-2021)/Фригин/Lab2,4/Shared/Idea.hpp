#pragma once
#include <iostream>
#include <cstdint>
#include <functional>
#include <array>

namespace Idea
{
static const uint8_t BLOCK_SIZE = 8;

static const uint8_t KEY_SIZE = 16;

typedef std::array <uint8_t, BLOCK_SIZE> Block;

typedef std::array <uint8_t, KEY_SIZE> Key;

void EncodeBlock (Block &block, const Key &key);
void DecodeBlock (Block &block, const Key &key);
void GenerateInitialBlock (Block &output);

template <typename ProducerFunctor, typename ConsumerFunctor>
Block EncodeCBC (const Block &initial, const Key &key, ProducerFunctor producer, ConsumerFunctor consumer)
{
    Block state = initial;
    Block working;

    while (producer (working))
    {
        for (uint32_t index = 0; index < working.size (); ++index)
        {
            working[index] ^= state[index];
        }

        EncodeBlock (working, key);
        state = working;
        consumer (working);
    }

    return state;
}

template <typename ProducerFunctor, typename ConsumerFunctor>
Block DecodeCBC (const Block &initial, const Key &key, ProducerFunctor producer, ConsumerFunctor consumer)
{
    Block state = initial;
    Block working;

    while (producer (working))
    {
        Block previousState = state;
        state = working;

        DecodeBlock (working, key);
        for (uint32_t index = 0; index < working.size (); ++index)
        {
            working[index] ^= previousState[index];
        }

        consumer (working);
    }

    return state;
}

class StreamProducer final
{
public:
    explicit StreamProducer (std::istream &stream);
    bool operator() (Block &block);

private:
    std::istream &stream_;
};

class StreamConsumer final
{
public:
    explicit StreamConsumer (std::ostream &stream);
    void operator() (const Block &block);

private:
    std::ostream &stream_;
};

template <typename Iterator> class ByteIteratorProducer final
{
public:
    ByteIteratorProducer (Iterator begin, Iterator end)
        : current_ (begin), end_ (end)
    {
    }

    bool operator() (Block &block)
    {
        if (current_ == end_)
        {
            return false;
        }

        block.fill (0);
        for (auto &byte : block)
        {
            byte = *current_;
            ++current_;

            if (current_ == end_)
            {
                break;
            }
        }

        return true;
    }

private:
    Iterator current_;
    Iterator end_;
};
}
