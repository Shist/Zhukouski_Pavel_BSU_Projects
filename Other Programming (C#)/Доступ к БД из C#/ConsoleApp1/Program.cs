using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.OleDb;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Введите желаемую дату: ");
            string temp;
            bool check = false;
            DateTime data_zakaza = DateTime.Now;
            try
            {
                temp = Console.ReadLine();
                data_zakaza = Convert.ToDateTime(temp);
            }
            catch (FormatException ex)
            {
                Console.WriteLine(ex.Message);
                return;
            }
            OleDbConnectionStringBuilder builder = new OleDbConnectionStringBuilder();
            builder.Add("provider", "Microsoft.Jet.OLEDB.4.0");
            builder.Add("Data Source","online_shop.mdb");
            OleDbConnection connection = new OleDbConnection(builder.ConnectionString);
            #region sql
            try
            {
                connection.Open();
                Console.ForegroundColor = ConsoleColor.Magenta;
                Console.WriteLine("Внимание!!! Подключение прошло успешно!!!");
                Console.ResetColor();

                string Query = @"SELECT Заказ.ДатаПоставки, Товар.НАИМЕНОВАНИЕ, Товар.МАРКА, [Состав заказа].Цена, [Состав заказа].Количество,
                Клиент.НАИМЕНОВАНИЕ, [Состояния заказа].КодСостояния
                FROM Товар INNER JOIN (([Состояния заказа] INNER JOIN (Клиент INNER JOIN Заказ ON Клиент.КОДКЛИЕНТА = Заказ.КодКлиента)
                ON [Состояния заказа].КодСостояния = Заказ.КодСостояния) INNER JOIN [Состав заказа] ON Заказ.НомерЗаказа = [Состав заказа].НомерЗаказа)
                ON Товар.КодТовара = [Состав заказа].КодТовара;";
                OleDbCommand command = new OleDbCommand(Query, connection);
                using (OleDbDataReader db_reader = command.ExecuteReader()) {
                    while(db_reader.Read())
                    {
                        if(db_reader[6].ToString() == "4" && data_zakaza < Convert.ToDateTime(db_reader[0].ToString()))
                        {
                            Console.WriteLine("Дата поставки: {0};\t Наименование товара: {1};\t Марка: {2};\t" +
                                "Цена: {3};\t Количество: {4};\t Наименование клиента: {5};",
            db_reader[0].ToString(), db_reader[1].ToString(), db_reader[2].ToString(), db_reader[3].ToString(), db_reader[4].ToString(), db_reader[5].ToString());
                            check = true;
                        }
                    }
                    if (!check)
                        Console.WriteLine("Начиная с введённой даты не было поставлено ни одного заказа...");
                }

            }
            finally{
                connection.Close();
                Console.ForegroundColor = ConsoleColor.Magenta;
                Console.WriteLine("Внимание!!! Отключение подключения прошло успешно!!!");
                Console.ResetColor();
            }
            #endregion
           
            Console.ReadKey();
        }
    }
}
//ORDER BY Курьер.ФИО;