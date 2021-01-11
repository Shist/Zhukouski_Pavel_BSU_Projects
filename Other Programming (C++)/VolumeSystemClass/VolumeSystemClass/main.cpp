#include "VolumeSystem.h"
#include <iostream>
#include <set> // Для вариантов 2-14 и 2-14
using namespace std;

int main()
{
	try
	{
		// Проверка работы всех методов класса
		VolumeSystem A(0, 0, 0.0);
		cout << "Object A: " << A << endl;
		cout << "Volume of object A is " << A.GetVolume() << endl;
		A.Set_Shtof(7);
		cout << "The amount of damns in object A after Set-method is " << A.Get_Shtof() << endl;
		A.Set_Bottl(1);
		cout << "The amount of bottles in object A after Set-method is " << A.Get_Bottl() << endl;
		A.Set_Chrk(3.75);
		cout << "The amount of charms in object A after Set-method is " << A.Get_Chrk() << endl;
		VolumeSystem B(1, 1, 1.0);
		cout << "Object B: " << A << endl;
		cout << "Volume of object B is " << A.GetVolume() << endl;
		B.Set_Shtof(4);
		cout << "The amount of damns in object B after Set-method is " << A.Get_Shtof() << endl;
		B.Set_Bottl(0);
		cout << "The amount of bottles in object B after Set-method is " << A.Get_Bottl() << endl;
		B.Set_Chrk(1.5);
		cout << "The amount of charms in object B after Set-method is " << A.Get_Chrk() << endl;
		cout << "The result of A == B (1 - true, 0 - false): " << (A == B) << endl;
		cout << "The result of A != B (1 - true, 0 - false): " << (A != B) << endl;
		cout << "The result of A < B (1 - true, 0 - false): " << (A < B) << endl;
		cout << "The result of A <= B (1 - true, 0 - false): " << (A <= B) << endl;
		cout << "The result of A > B (1 - true, 0 - false): " << (A > B) << endl;
		cout << "The result of A >= B (1 - true, 0 - false): " << (A >= B) << endl;
		VolumeSystem A_with_B(A + B);
		cout << "A + B = " << A_with_B << endl;
		VolumeSystem A_without_B(A - B);
		cout << "A - B = " << A_without_B << endl;
		VolumeSystem Temp(1, 1, 1.0);
		A += Temp;
		cout << "A += Temp: " << A << endl;
		B -= Temp;
		cout << "B -= Temp: " << B << endl;
		// Проверка работы всех методов класса

		// Варианты 2-1 и 2-15
		// Cоздать массив из 10 объектов разработанного класса, найти их суммарный объём.
		/*VolumeSystem C(1, 1, 1.0);
		VolumeSystem D(1, 1, 1.0);
		VolumeSystem E(1, 1, 1.0);
		VolumeSystem F(1, 1, 1.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(1, 1, 1.0);
		VolumeSystem I(1, 1, 1.0);
		VolumeSystem J(1, 1, 1.0);
		VolumeSystem K(1, 1, 1.0);
		VolumeSystem L(1, 1, 1.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double sum = 0.0;
		for (int i = 0; i < 10; i++)
			sum += arr[i].GetVolume();
		cout << "The total volume is " << sum << endl;*/

		// Варианты 2-2 и 2-16
		// Создать массив из 10 объектов разработанного класса, найти номер первого объекта с минимальным объёмом.
		/*VolumeSystem C(1, 1, 1.0);
		VolumeSystem D(1, 1, 1.0);
		VolumeSystem E(1, 1, 1.0);
		VolumeSystem F(1, 1, 1.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(1, 1, 1.0);
		VolumeSystem I(1, 1, 1.0);
		VolumeSystem J(0, 0, 0.0);
		VolumeSystem K(1, 1, 1.0);
		VolumeSystem L(1, 1, 1.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_volume = DBL_MAX;
		int ind = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetVolume() < min_volume)
			{
				min_volume = arr[i].GetVolume();
				ind = i;
			}
		cout << "The index (from 0 to 9) of the first object with minimal volume is " << ind << endl;*/

		// Варианты 2-3 и 2-17
		// Создать массив из 10 объектов разработанного класса, найти номер первого объекта с максимальным объёмом.
		/*VolumeSystem C(0, 0, 0.0);
		VolumeSystem D(0, 0, 0.0);
		VolumeSystem E(0, 0, 0.0);
		VolumeSystem F(0, 0, 0.0);
		VolumeSystem G(0, 0, 0.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(0, 0, 0.0);
		VolumeSystem J(1, 1, 1.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(0, 0, 0.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double max_volume = 0.0;
		int ind = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetVolume() > max_volume)
			{
				max_volume = arr[i].GetVolume();
				ind = i;
			}
		cout << "The index (from 0 to 9) of the first object with maximal volume is " << ind << endl;*/

		// Варианты 2-4 и 2-18
		// Создать массив из 10 объектов разработанного класса, определить, сколько объектов совпадает по объёму с последним элементом массива.
		/*VolumeSystem C(0, 0, 0.0);
		VolumeSystem D(0, 0, 0.0);
		VolumeSystem E(0, 0, 0.0);
		VolumeSystem F(1, 1, 1.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(0, 0, 0.0);
		VolumeSystem J(1, 1, 1.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(1, 1, 1.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double need_volume = arr[9].GetVolume();
		int count = 0;
		for (int i = 0; i < 9; i++)
			if (arr[i].GetVolume() == need_volume)
				count++;
		cout << "The amount of objects which volume is the same with the last object is " << count << endl;*/

		// Варианты 2-5 и 2-19
		// Создать массив из 10 объектов разработанного класса, найти номер последнего объекта с максимальным объёмом.
		/*VolumeSystem C(0, 0, 0.0);
		VolumeSystem D(0, 0, 0.0);
		VolumeSystem E(0, 0, 0.0);
		VolumeSystem F(1, 1, 1.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(0, 0, 0.0);
		VolumeSystem J(1, 1, 1.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(0, 0, 0.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double max_volume = 0.0;
		int ind = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetVolume() >= max_volume)
			{
				max_volume = arr[i].GetVolume();
				ind = i;
			}
		cout << "The index (from 0 to 9) of the last object with maximal volume is " << ind << endl;*/

		// Варианты 2-6 и 2-20
		// Создать массив из 10 объектов разработанного класса, определить, сколько объектов совпадает по объёму с первым элементом массива.
		/*VolumeSystem C(1, 1, 1.0);
		VolumeSystem D(0, 0, 0.0);
		VolumeSystem E(0, 0, 0.0);
		VolumeSystem F(1, 1, 1.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(0, 0, 0.0);
		VolumeSystem J(1, 1, 1.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(0, 0, 0.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double need_volume = arr[0].GetVolume();
		int count = 0;
		for (int i = 1; i < 10; i++)
			if (arr[i].GetVolume() == need_volume)
				count++;
		cout << "The amount of objects which volume is the same with the first object is " << count << endl;*/

		// Варианты 2-7 и 2-21
		// Создать массив из 10 объектов разработанного класса, найти номер последнего объекта с минимальным объёмом.
		/*VolumeSystem C(0, 0, 0.0);
		VolumeSystem D(0, 0, 0.0);
		VolumeSystem E(0, 0, 0.0);
		VolumeSystem F(1, 1, 1.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(0, 0, 0.0);
		VolumeSystem J(1, 1, 1.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(1, 1, 1.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_volume = DBL_MAX;
		int ind = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetVolume() <= min_volume)
			{
				min_volume = arr[i].GetVolume();
				ind = i;
			}
		cout << "The index (from 0 to 9) of the last object with minimal volume is " << ind << endl;*/

		// Варианты 2-8 и 2-22
		// Создать массив из 10 объектов разработанного класса, определить, сколько объектов совпадает по объёму с пятым элементом массива.
		/*VolumeSystem C(1, 1, 1.0);
		VolumeSystem D(0, 0, 0.0);
		VolumeSystem E(0, 0, 0.0);
		VolumeSystem F(1, 1, 1.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(0, 0, 0.0);
		VolumeSystem J(1, 1, 1.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(0, 0, 0.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double need_volume = arr[4].GetVolume();
		int count = 0;
		for (int i = 0; i < 10; i++)
			if (i != 4 && arr[i].GetVolume() == need_volume)
				count++;
		cout << "The amount of objects which volume is the same with the fifth object is " << count << endl;*/

		// Варианты 2-9 и 2-23
		// Создать массив из 10 объектов разработанного класса, найти количество элементов с минимальным объёмом.
		/*VolumeSystem C(1, 1, 1.0);
		VolumeSystem D(1, 1, 1.0);
		VolumeSystem E(1, 1, 1.0);
		VolumeSystem F(1, 1, 1.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(0, 0, 0.0);
		VolumeSystem J(1, 1, 1.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(0, 0, 0.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_volume = DBL_MAX;
		int count = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetVolume() < min_volume)
			{
				min_volume = arr[i].GetVolume();
				count = 1;
			}
			else if (arr[i].GetVolume() == min_volume)
				count++;
		cout << "The amount of objects with minimal volume is " << count << endl;*/

		// Варианты 2-10 и 2-24
		// Создать массив из 10 объектов разработанного класса, найти количество элементов с максимальным объёмом.
		/*VolumeSystem C(0, 0, 0.0);
		VolumeSystem D(0, 0, 0.0);
		VolumeSystem E(0, 0, 0.0);
		VolumeSystem F(1, 1, 1.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(0, 0, 0.0);
		VolumeSystem J(1, 1, 1.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(0, 0, 0.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double max_volume = 0.0;
		int count = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetVolume() > max_volume)
			{
				max_volume = arr[i].GetVolume();
				count = 1;
			}
			else if (arr[i].GetVolume() == max_volume)
				count++;
		cout << "The amount of objects with maximal volume is " << count << endl;*/

		// Варианты 2-11 и 2-25
		// Создать массив из 10 объектов разработанного класса, вывести максимальный объём элементов этого массива.
		/*VolumeSystem C(0, 0, 0.0);
		VolumeSystem D(0, 0, 0.0);
		VolumeSystem E(0, 0, 0.0);
		VolumeSystem F(1, 0, 0.0);
		VolumeSystem G(2, 0, 0.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(0, 0, 0.0);
		VolumeSystem J(1, 0, 0.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(0, 0, 0.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double max_volume = 0.0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetVolume() > max_volume)
				max_volume = arr[i].GetVolume();
		cout << "The maximal volume from objects of this array is " << max_volume << " liters" << endl;*/

		// Варианты 2-12 и 2-26
		// Создать массив из 10 объектов разработанного класса, вывести минимальный объём элементов этого массива.
		/*VolumeSystem C(4, 0, 0.0);
		VolumeSystem D(2, 0, 0.0);
		VolumeSystem E(3, 0, 0.0);
		VolumeSystem F(1, 0, 0.0);
		VolumeSystem G(2, 0, 0.0);
		VolumeSystem H(5, 0, 0.0);
		VolumeSystem I(4, 0, 0.0);
		VolumeSystem J(1, 0, 0.0);
		VolumeSystem K(7, 0, 0.0);
		VolumeSystem L(4, 0, 0.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_volume = DBL_MAX;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetVolume() < min_volume)
				min_volume = arr[i].GetVolume();
		cout << "The minimal volume from objects of this array is " << min_volume << " liters" << endl;*/

		// Варианты 2-13 и 2-27
		// Создать массив из 10 объектов разработанного класса, вывести разницу между объёмами максимального и минимального элементов массива.
		/*VolumeSystem C(4, 0, 0.0);
		VolumeSystem D(2, 0, 0.0);
		VolumeSystem E(3, 0, 0.0);
		VolumeSystem F(1, 0, 0.0);
		VolumeSystem G(2, 0, 0.0);
		VolumeSystem H(5, 0, 0.0);
		VolumeSystem I(4, 0, 0.0);
		VolumeSystem J(1, 0, 0.0);
		VolumeSystem K(6, 0, 0.0);
		VolumeSystem L(4, 0, 0.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_volume = DBL_MAX;
		double max_volume = 0.0;
		for (int i = 0; i < 10; i++)
		{
			if (arr[i].GetVolume() < min_volume)
				min_volume = arr[i].GetVolume();
			if (arr[i].GetVolume() > max_volume)
				max_volume = arr[i].GetVolume();
		}
		cout << "The difference between maximal and minimal volumes from objects of this array is " << (max_volume - min_volume) << " liters" << endl;*/

		// Вариант 2-14
		// Создать массив из 10 объектов разработанного класса, вывести количество различных элементов этого массива
        /*VolumeSystem C(2, 1, 2.0);
		VolumeSystem D(0, 0, 0.0);
		VolumeSystem E(1, 1, 1.0);
		VolumeSystem F(0, 0, 0.0);
		VolumeSystem G(1, 1, 1.0);
		VolumeSystem H(0, 0, 0.0);
		VolumeSystem I(1, 1, 1.0);
		VolumeSystem J(2, 1, 2.0);
		VolumeSystem K(0, 0, 0.0);
		VolumeSystem L(3, 1, 3.0);
		VolumeSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		set<VolumeSystem> unic_objects; // Контейнер set представляет собой множество уникальных элементов
		for (int i = 0; i < 10; i++)
			unic_objects.emplace(arr[i]);
		cout << "The number of different objects in the array is " << unic_objects.size() << endl;*/
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}