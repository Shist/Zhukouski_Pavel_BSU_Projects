using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Classes_C_sharp
{
    public class Temperature : IComparable, IFormattable
    {
        /// <summary>
        /// Реализация интерфейса IFormattable
        /// </summary>
        public string ToString(string format, IFormatProvider fp)
        {
            if (format == null)
                return ToString();
            string valueFormat = format.Substring(1);
            if ((format[0] == 'F') || (format[0] == 'f'))
                return Fahrenheit.ToString(valueFormat, fp) + "'F";
            if ((format[0] == 'C') || (format[0] == 'c'))
                return Celcium.ToString(valueFormat, fp) + "'C";
            throw new FormatException(String.Format("Invalid format string: '{0}'.", format));
        }
        /// <summary>
        /// Реализация интерфейса IComparable
        /// </summary>
        public int CompareTo(object obj)
        {
            if (!(obj is Temperature))
                throw new ArgumentException(
                "object is not a Temperature");
            Temperature otherTemperature = (Temperature)obj;
            if (this < otherTemperature)
                return -1;
            if (this > otherTemperature)
                return 1;
            return 0;
        }
        /// <summary>
        /// Единственное поле для хранения данных - температура
        /// в шкале Цельсия
        /// </summary>
        private double _celcium;
        /// <summary>
        /// Конструктор без параметров
        /// (Параметры по умолчанию недоступны)
        /// </summary>
        public Temperature()
        {
            _celcium = 0;
        }
        /// <summary>
        /// Конструктор, задающий температуру в шкале Цельсия
        /// </summary>
        public Temperature(double t)
        {
            _celcium = t;
        }
        /// <summary>
        /// Перегрузка операции сложения
        /// </summary>
        /// <param name="t1">Первое слагаемое</param>
        /// <param name="t2">Второе слагаемое</param>
        /// <returns>Сумма</returns>
        public static Temperature operator +(Temperature t1, Temperature t2) // плюс
        {
            Temperature t = new Temperature();
            t._celcium = t1._celcium + t2._celcium;
            return t;
        }
        public static Temperature operator -(Temperature t1, Temperature t2) // минус
        {
            Temperature t = new Temperature();
            t._celcium = t1._celcium - t2._celcium;
            return t;
        }
        /// <summary>
        /// Перегрузка унарного минуса
        /// </summary>
        /// <param name="t1">Исходные данные</param>
        /// <returns>Температура со знаком «минус»</returns>
        public static Temperature operator -(Temperature t1) // унарный минус
        {
            Temperature t = new Temperature();
            t._celcium = -t1._celcium;
            return t;
        }
        /// <summary>
        /// метод для получения температуры в шкале Цельсия
        /// </summary>
        /// <returns>значение температуры</returns>
        public double getCelcium() // геттер
        {
            return _celcium;
        }
        public static bool operator <(Temperature t1, Temperature t2) // меньше
        {
            return (t1._celcium < t2._celcium);
        }
        public static bool operator >(Temperature t1, Temperature t2) // больше
        {
            return (t1._celcium > t2._celcium);
        }
        public static bool operator ==(Temperature t1, Temperature t2) // равно
        {
            return (t1._celcium == t2._celcium);
        }
        public static bool operator !=(Temperature t1, Temperature t2) // неравно
        {
            return (t1._celcium != t2._celcium);
        }
        public override bool Equals(object obj) // ovverride - говорит о том, что мы ПЕРЕОПРЕДЕЛЯЕМ метод
        {
            if (obj == null) // попытка сравнить с нулевым объектом
                throw new NullReferenceException(); // одно из системных исключений
            if (!(obj is Temperature)) // проверка на то, является ли объект температурой
                throw new ArgumentException // операция is - проверяет, какому классу принадлежит наш объект
                ("Argument should be Temperature type");
            return (_celcium == (obj as Temperature)._celcium); // операция as преобразовывает объект к указаному типу (возможна только тогда, когда is вернула истину)
        }
        public override int GetHashCode()
        {
            return _celcium.GetHashCode();
        }
        /// <summary>
        /// Метод для перевода данных из строки
        /// </summary>
        /// <param name="s">Строка с представлением температуры
        /// (должна завершаться ' и признаком шкалы)</param>
        /// <returns>значение температуры</returns>
        public static Temperature Parse(string s) // метод Parse преобразует строку в объект
        {
            if (s == null) throw new ArgumentNullException(); // проверка на пустоту
            if (s.Length < 3) // проверка на кол-во символов (два последние должны означать градусы Цельсия)
                throw new FormatException
                ("Parameter length is too small");
            if ( !( (s.Substring(s.Length - 2, 2) == "'C") || (s.Substring(s.Length - 2, 2) == "'c") ) )
                throw new FormatException
                ("Parameter doesn't terminate by temperature mode");
            double d = Double.Parse(s.Substring(0, s.Length - 2));
            Temperature t = new Temperature();
            t._celcium = d;
            return t;
        }
        /// <summary>
        /// Перевод температуры в строку
        /// В этой версии - только в шкале Цельсия
        /// Переопределяется метод класса Object,
        /// что даёт возможность выводить данные в выходной поток
        /// </summary>
        /// <returns>представление температуры в виде строки</returns>
        public override string ToString()
        {
            double rezt;
            char rezt1;
            if (System.Globalization.CultureInfo.CurrentCulture.Name == "en-US")
            {
                rezt = fahrenheit;
                rezt1 = 'F';
            }
            else
            {
                rezt = celcium;
                rezt1 = 'C';
            }
            return String.Format("{0:##0.##}", rezt) + "'" + rezt1;
        }
        public double Celcium
        {
            get
            {
                return _celcium;
            }
            set
            {
                _celcium = value;
            }
        }
        public double Fahrenheit
        {
            get
            {
                return 32 + 1.8 * _celcium;
            }
            set
            {
                _celcium = (value - 32) / 1.8;
            }
        }
        ///<summary>
        /// Автоматически генерируемое свойство для шкалы Цельсия
        /// </summary>
        public double celcium
        {
            get;
            set;
        }
        /// <summary>
        /// Свойство для шкалы Фаренгейта
        /// </summary>
        public double fahrenheit
        {
            get
            {
                return 32 + 1.8 * celcium;
            }
            set
            {
                celcium = (value - 32) / 1.8;
            }
        }
    }
}
// this[] - это индексатор