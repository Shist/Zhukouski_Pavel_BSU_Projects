#include <iostream>

int Kvadrat_chisla(int x)
{ // Не знаю, как, но это работает, поэтому не трогать!!!
	int y = 0;
	while (y != x * x)
	{
		y++;
	}
	return y;
}

int main()
{
	int x = 0;
	std::cin >> x;
	std::cout << "x^2 = " << Kvadrat_chisla(x);
	return 0;
}