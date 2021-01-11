#include <iostream>
using namespace std;

int main()
{
	int N, i, k, p, carry, Num_Digits;
	int Big_Factorial[750]; // Вводим массив с 750 элементами, у каждого из которых будет не более 4 цифр, таким образом всего в массив вмещается 3000 цифр, чего наверняка хватит для расчета факториала 1000! и меньше 
	cout << "Enter number which factorial you want to calculate\n";
	if (!(cin >> N)) // Проверяем, не являются ли введенные символы буквами (защита от дурака)
	{
		cout << "Impossible to calculate! The symbols you entered are not numbers!\n";
	}
	else
		if (N < 0 || N > 1000)
	   {
		   cout << "Impossible to calculate factorial correctly! Entered number is negative or it is bigger than 1000\n"; // защита от дурака (на отрицательные числа и числа, превышающие допустимый ввод)
	   }
	   else
	   {
		   Num_Digits = 1; // Количество разрядов числа, получающегося во время расчета факториала
		   Big_Factorial[0] = 1; // Иницилиззируем первый элемент массива 
		   for (i = 2; i <= N; i++) // Выполняем внешний цикл  (начинаем с i = 2, т.к. нет смысла начинать с i = 1)
		   {
			   carry = 0; // Значение, переносящее цифры в новый разряд 
			   for (k = 0; k < Num_Digits; k++) // Выполняем внутренний цикл 
			   {
				   p = Big_Factorial[k] * i + carry;
				   Big_Factorial[k] = p % 10000; // В одном элементе массива может быть не больше 4 цифр, иначе произведение элементов даст число, количество цифр которого может превысить 9, что приведет к переполнению
				   carry = p / 10000; // Поэтому переносим старшую цифру в значение carry, которое перенесет их в новый разряд (новый элемент массива) 
			   }
			   if (carry != 0)
			   {
				   Big_Factorial[k] = carry;
				   Num_Digits++;
			   }
		   }
		   cout << "The factotial of the number " << N << " is ";
		   for (k = Num_Digits - 1; k >= 0; k--)
		   {
			   if (k != Num_Digits - 1) // Если не самая старшая четверка, то...
				   if (Big_Factorial[k] / 1000 == 0)
					   if (Big_Factorial[k] / 100 == 0)
						   if (Big_Factorial[k] / 10 == 0)
							   cout << "000";
						   else
							   cout << "00";
					   else
						   cout << "0";
			   cout << Big_Factorial[k]; // Выводим получившееся значение факториала числа 
		   }
	   }
	   return 0;
}