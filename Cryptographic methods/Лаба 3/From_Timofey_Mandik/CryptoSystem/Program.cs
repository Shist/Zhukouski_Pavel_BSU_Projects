using System;
using System.Collections;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using static CryptoSystem.Scenarios;

namespace CryptoSystem
{
    static class Program
    {
        static void Main(string[] args)
        {
            var RandomTextKey_Result = RandomTextKey();
            var SpecialTextKey_LowHWTextRandomKey_Result = SpecialTextKey(SpecialTextKeyMode.LowHWTextRandomKey);
            var SpecialTextKey_HighHWTextRandomKey_Result = SpecialTextKey(SpecialTextKeyMode.HighHWTextRandomKey);
            var SpecialTextKey_RandomTextLowHWKey_Result = SpecialTextKey(SpecialTextKeyMode.RandomTextLowHWKey);
            var SpecialTextKey_RandomTextHighHWKey_Result = SpecialTextKey(SpecialTextKeyMode.RandomTextHighHWKey);
            var ErrorPropagationKey_Result = ErrorPropagationKey();
            var ErrorPropagationText_Result = ErrorPropagationText();
            var TextsCorrelation_Result = TextsCorrelation();
            var ProbabilisticProperties_Result = ProbabilisticProperties();

            StoreData(RandomTextKey_Result, "RandomTextKey_Result.txt");
            StoreData(SpecialTextKey_LowHWTextRandomKey_Result, "SpecialTextKey_LowHWTextRandomKey_Result.txt");
            StoreData(SpecialTextKey_HighHWTextRandomKey_Result, "SpecialTextKey_HighHWTextRandomKey_Result.txt");
            StoreData(SpecialTextKey_RandomTextLowHWKey_Result, "SpecialTextKey_RandomTextLowHWKey_Result.txt");
            StoreData(SpecialTextKey_RandomTextHighHWKey_Result, "SpecialTextKey_RandomTextHighHWKey_Result.txt");
            StoreData(ErrorPropagationKey_Result, "ErrorPropagationKey_Result.txt");
            StoreData(ErrorPropagationText_Result, "ErrorPropagationText_Result.txt");
            StoreData(TextsCorrelation_Result, "TextsCorrelation_Result.txt");
            StoreData(ProbabilisticProperties_Result, "ProbabilisticProperties_Result.txt");

            Stopwatch sw = Stopwatch.StartNew();

            Console.WriteLine("\n[RandomTextKey]");
            Console.WriteLine(RunsTest.Test(RandomTextKey_Result));

            Console.WriteLine("\n[SpecialTextKey]");
            Console.WriteLine($"{SpecialTextKeyMode.LowHWTextRandomKey}  : {RunsTest.Test(SpecialTextKey_LowHWTextRandomKey_Result)}");
            Console.WriteLine($"{SpecialTextKeyMode.HighHWTextRandomKey} : {RunsTest.Test(SpecialTextKey_HighHWTextRandomKey_Result)}");
            Console.WriteLine($"{SpecialTextKeyMode.RandomTextLowHWKey}  : {RunsTest.Test(SpecialTextKey_RandomTextLowHWKey_Result)}");
            Console.WriteLine($"{SpecialTextKeyMode.RandomTextHighHWKey} : {RunsTest.Test(SpecialTextKey_RandomTextHighHWKey_Result)}");

            Console.WriteLine("\n[ErrorPropagationKey]");
            Console.WriteLine(RunsTest.Test(ErrorPropagationKey_Result));

            Console.WriteLine("\n[ErrorPropagationText]");
            Console.WriteLine(RunsTest.Test(ErrorPropagationText_Result));

            Console.WriteLine("\n[TextsCorrelation]");
            Console.WriteLine(RunsTest.Test(TextsCorrelation_Result));

            Console.WriteLine("\n[ProbabilisticProperties]");
            Console.WriteLine(RunsTest.Test(ProbabilisticProperties_Result));

            Console.WriteLine($"\n[Total time: {(int)sw.Elapsed.TotalSeconds} (sec)]");
            Console.Read();
        }

        static void TestСipher()
        {
            string source = "fedcba9876543210";
            string key_str = "ffeeddccbbaa99887766554433221100f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
            string encoded = "4ee901e5c2d8ca3d";

            ulong[] source_arr = Utils.HexStringToUlongArray(source);
            uint[] key_arr = Utils.HexStringToUintArray(key_str);
            ulong[] encoded_by_me = MagmaСipher.Encode(source_arr, key_arr);

            Console.WriteLine($"[Source]        {source}");
            Console.WriteLine($"[Encoded]       {encoded}");

            Console.WriteLine($"[Encoded by me] {Utils.UlongArrayToHexString(encoded_by_me)}");
            Console.WriteLine($"[Decoded by me] {Utils.UlongArrayToHexString(MagmaСipher.Decode(encoded_by_me, key_arr))}");
        }

        static void StoreData(ulong[] arr, string filename)
        {
            var ints = GetIntBits(arr);

            //using (var writer = new StreamWriter(Path.Combine(@"D:\Stud\Study\KM\Task_3\Scenarios", filename)))
            using (var writer = new StreamWriter(Path.Combine(Environment.CurrentDirectory, filename)))
            {
                StringBuilder builder = new StringBuilder(ints.Length);

                for (int i = 0; i < ints.Length; i++)
                {
                    builder.Append($"{ints[i]} ");
                }

                builder.Remove(builder.Length - 1, 1);

                writer.Write(builder.ToString());
            }
        }
    }

    static class Utils
    {
        public static string ByteArrayToHexString(byte[] arr)
        {
            return string.Concat(arr.Select(x => Convert.ToString(x, 16).PadLeft(2, '0'))).ToLower();
        }
        public static string UintArrayToHexString(uint[] arr)
        {
            var bytes = arr.SelectMany(x => BitConverter.GetBytes(x)).ToArray();

            return ByteArrayToHexString(bytes);
        }
        public static string UlongArrayToHexString(ulong[] arr)
        {
            var bytes = arr.SelectMany(x => BitConverter.GetBytes(x)).ToArray();

            return ByteArrayToHexString(bytes);
        }

        public static byte[] HexStringToByteArray(string str)
        {
            if (str.Length % 2 != 0)
                str = "0" + str;

            byte[] arr = new byte[str.Length / 2];

            for (int i = 0; i < arr.Length; i++)
            {
                string substr = str.Substring(2 * i, 2);

                arr[i] = (byte)int.Parse(substr, System.Globalization.NumberStyles.HexNumber);
            }

            return arr;
        }
        public static uint[] HexStringToUintArray(string str)
        {
            var bytes = HexStringToByteArray(str);

            int bytes_needed = 4 - (bytes.Length % 4 > 0 ? bytes.Length % 4 : 4);

            var new_bytes = new byte[bytes.Length + bytes_needed];

            Array.Copy(bytes, 0, new_bytes, bytes_needed, bytes.Length);

            if (new_bytes.Length % 4 != 0)
                throw new ArgumentException();

            uint[] res = new uint[new_bytes.Length / 4];

            for (int i = 0; i < res.Length; i++)
            {
                res[i] = BitConverter.ToUInt32(new_bytes, 4 * i);
            }

            return res;
        }
        public static ulong[] HexStringToUlongArray(string str)
        {
            var bytes = HexStringToByteArray(str);

            int bytes_needed = 8 - (bytes.Length % 8 > 0 ? bytes.Length % 8 : 8);

            var new_bytes = new byte[bytes.Length + bytes_needed];

            Array.Copy(bytes, 0, new_bytes, bytes_needed, bytes.Length);

            if (new_bytes.Length % 8 != 0)
                throw new ArgumentException();

            ulong[] res = new ulong[new_bytes.Length / 8];

            for (int i = 0; i < res.Length; i++)
            {
                res[i] = BitConverter.ToUInt64(new_bytes, 8 * i);
            }

            return res;
        }

        public static string ToBitString(this BitArray arr)
        {
            StringBuilder builder = new StringBuilder(arr.Length);

            foreach (var b in arr)
            {
                builder.Append(Convert.ToInt32((bool)b));
            }

            return builder.ToString();
        }
    }
}