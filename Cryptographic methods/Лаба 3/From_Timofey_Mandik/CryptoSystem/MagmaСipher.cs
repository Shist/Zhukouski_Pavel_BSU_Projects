using System;
using System.Collections;

namespace CryptoSystem
{
    // ГОСТ 34.12—2018
    static class MagmaСipher
    {
        #region Const
        public const int KeyBitLength = 256;
        public const int KeySegmentsCount = 8;
        public const int KeySegmentBitLength = 32;
        public const int BlockBitLength = 64;
        #endregion

        #region Const stuff
        const ulong LeftUlongHalfMask = 0x00000000FFFFFFFF;
        const ulong RightUlongHalfMask = 0xFFFFFFFF00000000;
        const byte LeftByteHalfMask = 0xF0;
        const byte RightByteHalfMask = 0x0F;
        const ulong Pow_2_32 = 0x100000000;
        const int CycleCount = 32;

        //  id-tc26-gost-28147-param-Z
        static readonly byte[][] SubstitutionBlock = new byte[8][]
        {          
            //              0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f
            new byte[16] {0xC, 0x4, 0x6, 0x2, 0xA, 0x5, 0xB, 0x9, 0xE, 0x8, 0xD, 0x7, 0x0, 0x3, 0xF, 0x1}, // 0
            new byte[16] {0x6, 0x8, 0x2, 0x3, 0x9, 0xA, 0x5, 0xC, 0x1, 0xE, 0x4, 0x7, 0xB, 0xD, 0x0, 0xF}, // 1
            new byte[16] {0xB, 0x3, 0x5, 0x8, 0x2, 0xF, 0xA, 0xD, 0xE, 0x1, 0x7, 0x4, 0xC, 0x9, 0x6, 0x0}, // 2
            new byte[16] {0xC, 0x8, 0x2, 0x1, 0xD, 0x4, 0xF, 0x6, 0x7, 0x0, 0xA, 0x5, 0x3, 0xE, 0x9, 0xB}, // 3
            new byte[16] {0x7, 0xF, 0x5, 0xA, 0x8, 0x1, 0x6, 0xD, 0x0, 0x9, 0x3, 0xE, 0xB, 0x4, 0x2, 0xC}, // 4
            new byte[16] {0x5, 0xD, 0xF, 0x6, 0x9, 0x2, 0xC, 0xA, 0xB, 0x7, 0x8, 0x1, 0x4, 0x3, 0xE, 0x0}, // 5
            new byte[16] {0x8, 0xE, 0x2, 0x5, 0x6, 0x9, 0x1, 0xC, 0xF, 0x4, 0xB, 0x0, 0xD, 0xA, 0x3, 0x7}, // 6
            new byte[16] {0x1, 0x7, 0xE, 0xD, 0x0, 0x5, 0x8, 0x3, 0x4, 0xF, 0xA, 0x6, 0x9, 0xC, 0xB, 0x2}  // 7
        };
        #endregion

        #region Sup methods
        static uint ReverseBytes(uint value)
        {
            var bytes = BitConverter.GetBytes(value);

            Array.Reverse(bytes);

            return BitConverter.ToUInt32(bytes, 0);
        }
        static ulong ReverseBytes(ulong value)
        {
            var bytes = BitConverter.GetBytes(value);

            Array.Reverse(bytes);

            return BitConverter.ToUInt64(bytes, 0);
        }
        static uint CircularShiftLeft(uint arg, int n)
        {
            return (uint)(arg << n) | (arg >> (32 - n)) & (uint)((1 << n) - 1);
        }
        static uint[] GetKeyArray(BitArray key)
        {
            uint[] arr = new uint[KeySegmentsCount];

            uint mask;

            for (int i = 0; i < KeySegmentsCount; i++)
            {
                mask = 1;

                for (int j = 0; j < KeySegmentBitLength; j++)
                {
                    if (key.Get(i * KeySegmentBitLength + j))
                    {
                        arr[i] |= mask;
                    }

                    mask <<= 1;
                }
            }

            return arr;
        }
        #endregion

        #region Core
        static uint Conv_t(uint A)
        {
            byte[] bytes = BitConverter.GetBytes(A);
            byte[] parts = new byte[8];
            byte[] res = new byte[4];

            for (int i = 0; i < 4; i++)
            {
                parts[2 * i] = SubstitutionBlock[2 * i][(byte)(bytes[i] & RightByteHalfMask)];
            }
            for (int i = 0; i < 4; i++)
            {
                parts[2 * i + 1] = SubstitutionBlock[2 * i + 1][(byte)((bytes[i] & LeftByteHalfMask) >> 4)];
            }

            Array.Reverse(parts);

            for (int i = 0; i < 4; i++)
            {
                res[i] = (byte)((parts[2 * i] << 4) | parts[2 * i + 1]);
            }

            Array.Reverse(res);

            return BitConverter.ToUInt32(res, 0);
        }
        static uint Conv_g(uint A, uint K)
        {
            return CircularShiftLeft(Conv_t((uint)(((ulong)A + K) % Pow_2_32)), 11);
        }
        static Tuple<uint, uint> Conv_G(uint A_1, uint A_0, uint K)
        {
            return new Tuple<uint, uint>(A_0, Conv_g(A_0, K) ^ A_1);
        }
        #endregion

        public static ulong[] Encode(ulong[] source, uint[] key)
        {
            if (key.Length != 8)
            {
                throw new ArgumentException();
            }

            uint[] sub_keys = new uint[32];
            ulong[] encoded = new ulong[source.Length];

            for (int i = 0; i < 24; i++)
            {
                sub_keys[i] = ReverseBytes(key[i % 8]);
            }
            for (int i = 24, j = 7; i < 32; i++, j--)
            {
                sub_keys[i] = ReverseBytes(key[j]);
            }

            for (int block_i = 0; block_i < source.Length; block_i++)
            {
                ulong block = source[block_i];

                Tuple<uint, uint> pair = new Tuple<uint, uint>(ReverseBytes((uint)(block ^ RightUlongHalfMask)), ReverseBytes((uint)((block ^ LeftUlongHalfMask) >> 32)));

                for (int cycle = 1; cycle < CycleCount; cycle++)
                {
                    pair = Conv_G(pair.Item1, pair.Item2, sub_keys[cycle - 1]);
                }

                encoded[block_i] = ReverseBytes(((ulong)(Conv_g(pair.Item2, sub_keys[31]) ^ pair.Item1)) << 32) | ReverseBytes((ulong)pair.Item2);
            }

            return encoded;
        }
        public static ulong[] Encode(ulong[] source, BitArray key)
        {
            return Encode(source, GetKeyArray(key));
        }
        public static ulong Encode(ulong source, uint[] key)
        {
            return Encode(new ulong[] { source }, key)[0];
        }
        public static ulong Encode(ulong source, BitArray key)
        {
            return Encode(source, GetKeyArray(key));
        }

        public static ulong[] Decode(ulong[] source, uint[] key)
        {
            if (key.Length != 8)
            {
                throw new ArgumentException();
            }

            uint[] syb_key = new uint[32];

            for (int i = 0; i < 24; i++)
            {
                syb_key[i] = ReverseBytes(key[i % 8]);
            }

            for (int i = 24, j = 7; i < 32; i++, j--)
            {
                syb_key[i] = ReverseBytes(key[j]);
            }

            ulong[] encoded = new ulong[source.Length];

            for (int block_i = 0; block_i < source.Length; block_i++)
            {
                ulong block = source[block_i];

                Tuple<uint, uint> pair = new Tuple<uint, uint>(ReverseBytes((uint)(block ^ RightUlongHalfMask)), ReverseBytes((uint)((block ^ LeftUlongHalfMask) >> 32)));

                for (int cycle = CycleCount - 1; cycle > 0; cycle--)
                {
                    pair = Conv_G(pair.Item1, pair.Item2, syb_key[cycle]);
                }

                encoded[block_i] = ReverseBytes(((ulong)(Conv_g(pair.Item2, syb_key[0]) ^ pair.Item1)) << 32) | ReverseBytes((ulong)pair.Item2);
            }

            return encoded;
        }
        public static ulong[] Decode(ulong[] source, BitArray key)
        {
            return Decode(source, GetKeyArray(key));
        }
        public static ulong Decode(ulong source, uint[] key)
        {
            return Decode(new ulong[] { source }, key)[0];
        }
        public static ulong Decode(ulong source, BitArray key)
        {
            return Decode(source, GetKeyArray(key));
        }
    }
}