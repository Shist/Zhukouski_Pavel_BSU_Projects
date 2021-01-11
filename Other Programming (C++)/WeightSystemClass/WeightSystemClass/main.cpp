#include "WeightSystem.h"
#include <iostream>
#include <set> // Для вариантов 1-14 и 2-14
using namespace std;

int main()
{
	try
	{
		// Проверка работы всех методов класса
		WeightSystem A(0, 0, 0);
		cout << "Object A: " << A << endl;
		cout << "Weigth of object A is " << A.GetWeight() << endl;
		A.Set_Pud(42);
		cout << "The amount of poods in object A after Set-method is " << A.Get_Pud() << endl;
		A.Set_Fut(27);
		cout << "The amount of pounds in object A after Set-method is " << A.Get_Fut() << endl;
		A.Set_Zol(56);
		cout << "The amount of spools in object A after Set-method is " << A.Get_Zol() << endl;
		WeightSystem B(1, 1, 1);
		cout << "Object B: " << A << endl;
		cout << "Weigth of object B is " << A.GetWeight() << endl;
		B.Set_Pud(9);
		cout << "The amount of poods in object B after Set-method is " << A.Get_Pud() << endl;
		B.Set_Fut(31);
		cout << "The amount of pounds in object B after Set-method is " << A.Get_Fut() << endl;
		B.Set_Zol(77);
		cout << "The amount of spools in object B after Set-method is " << A.Get_Zol() << endl;
		cout << "The result of A == B (1 - true, 0 - false): " << (A == B) << endl;
		cout << "The result of A != B (1 - true, 0 - false): " << (A != B) << endl;
		cout << "The result of A < B (1 - true, 0 - false): " << (A < B) << endl;
		cout << "The result of A <= B (1 - true, 0 - false): " << (A <= B) << endl;
		cout << "The result of A > B (1 - true, 0 - false): " << (A > B) << endl;
		cout << "The result of A >= B (1 - true, 0 - false): " << (A >= B) << endl;
		WeightSystem A_with_B(A + B);
		cout << "A + B = " << A_with_B << endl;
		WeightSystem A_without_B(A - B);
		cout << "A - B = " << A_without_B << endl;
		WeightSystem Temp(1, 1, 1);
		A += Temp;
		cout << "A += Temp: " << A << endl;
		B -= Temp;
		cout << "B -= Temp: " << B << endl << endl;
		// Проверка работы всех методов класса

		// Варианты 1-1 и 1-15
		// Cоздать массив из 10 объектов разработанного класса, найти их суммарный вес.
		/*WeightSystem C(1, 1, 1);
		WeightSystem D(1, 1, 1);
		WeightSystem E(1, 1, 1);
		WeightSystem F(1, 1, 1);
		WeightSystem G(1, 1, 1);
		WeightSystem H(1, 1, 1);
		WeightSystem I(1, 1, 1);
		WeightSystem J(1, 1, 1);
		WeightSystem K(1, 1, 1);
		WeightSystem L(1, 1, 1);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double sum = 0.0;
		for (int i = 0; i < 10; i++)
			sum += arr[i].GetWeight();
		cout << "The total weight is " << sum << endl;*/

		// Варианты 1-2 и 1-16
		// Создать массив из 10 объектов разработанного класса, найти номер первого объекта с минимальным весом.
		/*WeightSystem C(1, 1, 1);
		WeightSystem D(1, 1, 1);
		WeightSystem E(1, 1, 1);
		WeightSystem F(1, 1, 1);
		WeightSystem G(1, 1, 1);
		WeightSystem H(1, 1, 1);
		WeightSystem I(1, 1, 1);
		WeightSystem J(0, 0, 0);
		WeightSystem K(1, 1, 1);
		WeightSystem L(1, 1, 1);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_weight = DBL_MAX;
		int ind = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetWeight() < min_weight)
			{
				min_weight = arr[i].GetWeight();
				ind = i;
			}
		cout << "The index (from 0 to 9) of the first object with minimal weight is " << ind << endl;*/

		// Варианты 1-3 и 1-17
		// Создать массив из 10 объектов разработанного класса, найти номер первого объекта с максимальным весом.
		/*WeightSystem C(0, 0, 0);
		WeightSystem D(0, 0, 0);
		WeightSystem E(0, 0, 0);
		WeightSystem F(0, 0, 0);
		WeightSystem G(0, 0, 0);
		WeightSystem H(0, 0, 0);
		WeightSystem I(0, 0, 0);
		WeightSystem J(1, 1, 1);
		WeightSystem K(0, 0, 0);
		WeightSystem L(0, 0, 0);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double max_weight = 0.0;
		int ind = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetWeight() > max_weight)
			{
				max_weight = arr[i].GetWeight();
				ind = i;
			}
		cout << "The index (from 0 to 9) of the first object with maximal weight is " << ind << endl;*/

		// Варианты 1-4 и 1-18
		// Создать массив из 10 объектов разработанного класса, определить, сколько объектов совпадает по весу с последним элементом массива.
		/*WeightSystem C(0, 0, 0);
		WeightSystem D(0, 0, 0);
		WeightSystem E(0, 0, 0);
		WeightSystem F(1, 1, 1);
		WeightSystem G(1, 1, 1);
		WeightSystem H(0, 0, 0);
		WeightSystem I(0, 0, 0);
		WeightSystem J(1, 1, 1);
		WeightSystem K(0, 0, 0);
		WeightSystem L(1, 1, 1);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double need_weight = arr[9].GetWeight();
		int count = 0;
		for (int i = 0; i < 9; i++)
			if (arr[i].GetWeight() == need_weight)
				count++;
		cout << "The amount of objects which weight is the same with the last object is " << count << endl;*/

		// Варианты 1-5 и 1-19
		// Создать массив из 10 объектов разработанного класса, найти номер последнего объекта с максимальным весом.
		/*WeightSystem C(0, 0, 0);
		WeightSystem D(0, 0, 0);
		WeightSystem E(0, 0, 0);
		WeightSystem F(1, 1, 1);
		WeightSystem G(1, 1, 1);
		WeightSystem H(0, 0, 0);
		WeightSystem I(0, 0, 0);
		WeightSystem J(1, 1, 1);
		WeightSystem K(0, 0, 0);
		WeightSystem L(0, 0, 0);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double max_weight = 0.0;
		int ind = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetWeight() >= max_weight)
			{
				max_weight = arr[i].GetWeight();
				ind = i;
			}
		cout << "The index (from 0 to 9) of the last object with maximal weight is " << ind << endl;*/

		// Варианты 1-6 и 1-20
		// Создать массив из 10 объектов разработанного класса, определить, сколько объектов совпадает по весу с первым элементом массива.
        /*WeightSystem C(1, 1, 1);
		WeightSystem D(0, 0, 0);
		WeightSystem E(0, 0, 0);
		WeightSystem F(1, 1, 1);
		WeightSystem G(1, 1, 1);
		WeightSystem H(0, 0, 0);
		WeightSystem I(0, 0, 0);
		WeightSystem J(1, 1, 1);
		WeightSystem K(0, 0, 0);
		WeightSystem L(0, 0, 0);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double need_weight = arr[0].GetWeight();
		int count = 0;
		for (int i = 1; i < 10; i++)
			if (arr[i].GetWeight() == need_weight)
				count++;
		cout << "The amount of objects which weight is the same with the first object is " << count << endl;*/

		// Варианты 1-7 и 1-21
		// Создать массив из 10 объектов разработанного класса, найти номер последнего объекта с минимальным весом.
        /*WeightSystem C(0, 0, 0);
		WeightSystem D(0, 0, 0);
		WeightSystem E(0, 0, 0);
		WeightSystem F(1, 1, 1);
		WeightSystem G(1, 1, 1);
		WeightSystem H(0, 0, 0);
		WeightSystem I(0, 0, 0);
		WeightSystem J(1, 1, 1);
		WeightSystem K(0, 0, 0);
		WeightSystem L(1, 1, 1);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_weight = DBL_MAX;
		int ind = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetWeight() <= min_weight)
			{
				min_weight = arr[i].GetWeight();
				ind = i;
			}
		cout << "The index (from 0 to 9) of the last object with minimal weight is " << ind << endl;*/

		// Варианты 1-8 и 1-22
		// Создать массив из 10 объектов разработанного класса, определить, сколько объектов совпадает по весу с пятым элементом массива.
        /*WeightSystem C(1, 1, 1);
		WeightSystem D(0, 0, 0);
		WeightSystem E(0, 0, 0);
		WeightSystem F(1, 1, 1);
		WeightSystem G(1, 1, 1);
		WeightSystem H(0, 0, 0);
		WeightSystem I(0, 0, 0);
		WeightSystem J(1, 1, 1);
		WeightSystem K(0, 0, 0);
		WeightSystem L(0, 0, 0);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double need_weight = arr[4].GetWeight();
		int count = 0;
		for (int i = 0; i < 10; i++)
			if (i != 4 && arr[i].GetWeight() == need_weight)
				count++;
		cout << "The amount of objects which weight is the same with the fifth object is " << count << endl;*/

		// Варианты 1-9 и 1-23
		// Создать массив из 10 объектов разработанного класса, найти количество элементов с минимальным весом.
        /*WeightSystem C(1, 1, 1);
		WeightSystem D(1, 1, 1);
		WeightSystem E(1, 1, 1);
		WeightSystem F(1, 1, 1);
		WeightSystem G(1, 1, 1);
		WeightSystem H(0, 0, 0);
		WeightSystem I(0, 0, 0);
		WeightSystem J(1, 1, 1);
		WeightSystem K(0, 0, 0);
		WeightSystem L(0, 0, 0);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_weight = DBL_MAX;
		int count = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetWeight() < min_weight)
			{
				min_weight = arr[i].GetWeight();
				count = 1;
			}
			else if (arr[i].GetWeight() == min_weight)
				count++;
		cout << "The amount of objects with minimal weight is " << count << endl;*/

		// Варианты 1-10 и 1-24
		// Создать массив из 10 объектов разработанного класса, найти количество элементов с максимальным весом.
        /*WeightSystem C(0, 0, 0);
		WeightSystem D(0, 0, 0);
		WeightSystem E(0, 0, 0);
		WeightSystem F(1, 1, 1);
		WeightSystem G(1, 1, 1);
		WeightSystem H(0, 0, 0);
		WeightSystem I(0, 0, 0);
		WeightSystem J(1, 1, 1);
		WeightSystem K(0, 0, 0);
		WeightSystem L(0, 0, 0);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double max_weight = 0.0;
		int count = 0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetWeight() > max_weight)
			{
				max_weight = arr[i].GetWeight();
				count = 1;
			}
			else if (arr[i].GetWeight() == max_weight)
				count++;
		cout << "The amount of objects with maximal weight is " << count << endl;*/

		// Варианты 1-11 и 1-25
		// Создать массив из 10 объектов разработанного класса, вывести максимальный вес элементов этого массива.
        /*WeightSystem C(0, 0, 0);
		WeightSystem D(0, 0, 0);
		WeightSystem E(0, 0, 0);
		WeightSystem F(1, 0, 0);
		WeightSystem G(2, 0, 0);
		WeightSystem H(0, 0, 0);
		WeightSystem I(0, 0, 0);
		WeightSystem J(1, 0, 0);
		WeightSystem K(0, 0, 0);
		WeightSystem L(0, 0, 0);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double max_weight = 0.0;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetWeight() > max_weight)
				max_weight = arr[i].GetWeight();
		cout << "The maximal weight from objects of this array is " << max_weight << " kg" << endl;*/

		// Варианты 1-12 и 1-26
		// Создать массив из 10 объектов разработанного класса, вывести минимальный вес элементов этого массива.
        /*WeightSystem C(4, 0, 0);
		WeightSystem D(2, 0, 0);
		WeightSystem E(3, 0, 0);
		WeightSystem F(1, 0, 0);
		WeightSystem G(2, 0, 0);
		WeightSystem H(5, 0, 0);
		WeightSystem I(4, 0, 0);
		WeightSystem J(1, 0, 0);
		WeightSystem K(7, 0, 0);
		WeightSystem L(4, 0, 0);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_weight = DBL_MAX;
		for (int i = 0; i < 10; i++)
			if (arr[i].GetWeight() < min_weight)
				min_weight = arr[i].GetWeight();
		cout << "The minimal weight from objects of this array is " << min_weight << " kg" << endl;*/

		// Варианты 1-13 и 1-27
		// Создать массив из 10 объектов разработанного класса, вывести разницу между весами максимального и минимального элементов массива.
        /*WeightSystem C(4, 0, 0);
		WeightSystem D(2, 0, 0);
		WeightSystem E(3, 0, 0);
		WeightSystem F(1, 0, 0);
		WeightSystem G(2, 0, 0);
		WeightSystem H(5, 0, 0);
		WeightSystem I(4, 0, 0);
		WeightSystem J(1, 0, 0);
		WeightSystem K(6, 0, 0);
		WeightSystem L(4, 0, 0);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		double min_weight = DBL_MAX;
		double max_weight = 0.0;
		for (int i = 0; i < 10; i++)
		{
			if (arr[i].GetWeight() < min_weight)
				min_weight = arr[i].GetWeight();
			if (arr[i].GetWeight() > max_weight)
				max_weight = arr[i].GetWeight();
		}
		cout << "The difference between maximal and minimal weights from objects of this array is " << (max_weight - min_weight) << " kg" << endl;*/

		// Вариант 1-14
		// Создать массив из 10 объектов разработанного класса, вывести количество различных элементов этого массива
        /*WeightSystem C(2, 2, 2);
		WeightSystem D(0, 0, 0);
		WeightSystem E(1, 1, 1);
		WeightSystem F(0, 0, 0);
		WeightSystem G(1, 1, 1);
		WeightSystem H(0, 0, 0);
		WeightSystem I(1, 1, 1);
		WeightSystem J(2, 2, 2);
		WeightSystem K(0, 0, 0);
		WeightSystem L(3, 3, 3);
		WeightSystem arr[10] = { C, D, E, F, G, H, I, J, K, L };
		set<WeightSystem> unic_objects; // Контейнер set представляет собой множество уникальных элементов
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