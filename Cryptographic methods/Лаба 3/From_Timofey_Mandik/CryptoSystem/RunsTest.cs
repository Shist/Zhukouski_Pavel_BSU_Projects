using System;
using System.Collections;
using System.Linq;
using System.Text;

namespace CryptoSystem
{
    public static class RunsTest
    {
        const double DecisionRulePercent = 0.01;
        static double Erfc(double x)
        {
            double a1 = 0.254829592;
            double a2 = -0.284496736;
            double a3 = 1.421413741;
            double a4 = -1.453152027;
            double a5 = 1.061405429;
            double p = 0.3275911;

            int sign = x < 0 ? -1 : 1;

            x = Math.Abs(x);

            double t = 1.0 / (1.0 + p * x);
            double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * Math.Exp(-x * x);

            return 1 - sign * y;
        }

        public static bool TestBinaryString(string str)
        {
            return Test(new BitArray(str.Select(x =>
            {
                if (x == '0' || x == '1')
                {
                    return x == '1';
                }
                else
                {
                    throw new ArgumentException();
                }
            }).ToArray()));
        }
        public static bool Test(string str)
        {
            return Test(str, Encoding.Unicode);

        }
        public static bool Test(string str, Encoding encoding)
        {
            return Test(new BitArray(encoding.GetBytes(str)));
        }
        public static bool Test(ulong[] arr)
        {
            return Test(arr.SelectMany(x => BitConverter.GetBytes(x)).ToArray());
        }
        public static bool Test(uint[] arr)
        {
            return Test(arr.SelectMany(x => BitConverter.GetBytes(x)).ToArray());
        }
        public static bool Test(byte[] arr)
        {
            return Test(new BitArray(arr));
        }
        public static bool Test(BitArray arr)
        {
            return Test(arr.Cast<bool>().ToArray());
        }
        public static bool Test(bool[] arr)
        {
            int n = arr.Length;
            double pi = (double)arr.Count(x => x) / n;
            double tau = 2.0 / Math.Sqrt(n);

            if (Math.Abs(pi - 0.5) >= tau)
            {
                return false;
            }

            double v = 1;

            for (int k = 0; k <= n - 2; k++)
            {
                v += arr[k] == arr[k + 1] ? 0 : 1;
            }

            double p_value = Erfc(Math.Abs(v - 2 * n * pi * (1 - pi)) / (2.0 * Math.Sqrt(2 * n) * pi * (1 - pi)));

            return p_value >= DecisionRulePercent;
        }
    }
}