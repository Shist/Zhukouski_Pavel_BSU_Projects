using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Fraction_C_sharp
{
    public class Fraction : IEquatable<Fraction>
    {
        private int ch { get; set; } // Числитель
        private int zn { get; set; } // Знаменатель

        public Fraction() // Конструктор по умолчанию
        {
            checked
            {
                ch = 0;
                zn = 1;
            }
        }
        public Fraction(int numerator, int denominator) // Конструктор
        {
            checked
            {
                if (denominator == 0)
                    throw new Exception("Знаменатель не может быть равен нулю!!!");
                ch = numerator;
                zn = denominator;
                Reduction();
            }
        }

        private void Reduction() // Функция для сокращения дробей
        {
            checked
            {
                if (zn < 0) // Если знаменатель меньше нуля, то переносим знак "миунс" в числитель
                {
                    zn = -zn;
                    ch = -ch;
                }
                int temp = (Math.Abs(ch) > Math.Abs(zn)) ? zn : ch;
                temp = Math.Abs(temp);
                for (int i = temp; i > 1; i--)
                {
                    if (ch % i == 0 && zn % i == 0)
                    {
                        ch /= i;
                        zn /= i;
                    }
                }
                if (ch == 0) zn = 1;
            }
        }

        public static Fraction operator -(Fraction a) // Унарный минус
        {
            checked
            {
                a.ch *= -1;
                return a;
            }
        }

        public static Fraction operator +(Fraction f1, Fraction f2) // Сложение
        {
            checked
            {
                Fraction X = new Fraction(f1.ch * f2.zn + f2.ch * f1.zn, f1.zn * f2.zn);
                X.Reduction();
                return X;
            }
        }

        public static Fraction operator -(Fraction f1, Fraction f2) // Разность
        {
            checked
            {
                Fraction X = new Fraction(f1.ch * f2.zn - f2.ch * f1.zn, f1.zn * f2.zn);
                X.Reduction();
                return X;
            }
        }

        public static Fraction operator *(Fraction f1, Fraction f2) // Умножение
        {
            checked
            {
                Fraction X = new Fraction(f1.ch * f2.ch, f1.zn * f2.zn);
                X.Reduction();
                return X;
            }
        }

        public static Fraction operator /(Fraction f1, Fraction f2) // Деление
        {
            checked
            {
                Fraction X = new Fraction(f1.ch * f2.zn, f1.zn * f2.ch);
                X.Reduction();
                return X;
            }
        }

        public static bool operator ==(Fraction f1, Fraction f2) // Равенство
        {
            checked
            {
                return f1.ch * f2.zn == f1.zn * f2.ch;
            }
        }

        public static bool operator !=(Fraction f1, Fraction f2) // Неравенство
        {
            checked
            {
                return !(f1 == f2);
            }
        }

        public static bool operator >(Fraction f1, Fraction f2) // Больше
        {
            checked
            {
                return f1.ch * f2.zn > f1.zn * f2.ch;
            }
        }

        public static bool operator <(Fraction f1, Fraction f2) // Меньше
        {
            checked
            {
                return f1.ch * f2.zn < f1.zn * f2.ch;
            }
        }

        public static bool operator >=(Fraction f1, Fraction f2) // Больше/равно
        {
            checked
            {
                return f1.ch * f2.zn >= f1.zn * f2.ch;
            }
        }

        public static bool operator <=(Fraction f1, Fraction f2) // Меньше/равно
        {
            checked
            {
                return f1.ch * f2.zn <= f1.zn * f2.ch;
            }
        }

        public override string ToString() // Представить в виде строки
        {
            try
            {
                return ((double)ch / zn >= 0 ? "" : "-") + Math.Abs(ch) + "/" + Math.Abs(zn);
            }
            catch (OverflowException)
            {
                return "";
            }
        }

        public double SeeDouble() // Представить в рациональном виде
        {
            checked
            {
                return (double)ch / zn;
            }
        }

        public bool Equals(Fraction other)
        {
            checked
            {
                if (ReferenceEquals(null, other)) return false;
                if (ReferenceEquals(this, other)) return true;
                return (ch * other.zn == other.ch * zn);
            }
        }

        public override bool Equals(object obj)
        {
            checked
            {
                if (ReferenceEquals(null, obj)) return false;
                if (ReferenceEquals(this, obj)) return true;
                return obj.GetType() == typeof(Fraction) && Equals((Fraction)obj);
            }
        }

        public Fraction Parse(string text)
        {
            checked
            {

                if (text == null)
                    throw new ArgumentNullException();
                if (text.Length < 3)
                    throw new FormatException("Ошибка в методе Parse! Параметр длины слишком мал!!!");
                if (!(text.Substring(text.Length - 1, 1) == "/"))
                    throw new FormatException("Ошибка в методе Parse! Параметр не прекращается в режиме дроби!!!");
                int ch = int.Parse(text.Substring(0, text.Length - 2));
                int zn = int.Parse(text.Substring(0, text.Length - 2));
                Fraction X = new Fraction();
                X.ch = ch;
                X.zn = zn;
                return X;
            }
        }

        public override int GetHashCode()
        {
            unchecked
            {
                return (ch * 397) ^ zn;
            }
        }
    }
}