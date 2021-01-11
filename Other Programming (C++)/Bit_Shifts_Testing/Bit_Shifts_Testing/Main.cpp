#include <iostream>

int main()
{
	setlocale(LC_ALL, "Rus");
	int a = 4;
	std::cout << "Исходное число: " << a << std::endl;
	a = a << 1;
	std::cout << "Число после побитового сдвига влево на один: " << a;
	return 0;
}