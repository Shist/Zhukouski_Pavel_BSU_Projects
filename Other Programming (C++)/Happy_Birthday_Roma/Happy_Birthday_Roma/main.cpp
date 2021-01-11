// Made for Roman Koltunchik (best programming teacher) by Shist (22.02.2020)
// JUST RUN IT AWAY!!!
#include <iostream>
#include <ctime>

void Output_1()
{
	std::cout << "  **   **     ***     *****  ***** **     **  " << std::endl;
	std::cout << "  **   **    ** **    **  ** **  ** **   **   " << std::endl;
	std::cout << "  *******   *******   *****  *****   ** **    " << std::endl;
	std::cout << "  **   **  **     **  **     **       ***     " << std::endl;
	std::cout << "  **   ** **       ** **     **       ***     " << std::endl << std::endl;
}

void Output_2()
{
	std::cout << "  *****  **** *****  ****** **   ** *****     ***  **     **  " << std::endl;
	std::cout << "  **  **  **  **  **   **   **   ** **  **   ** **  **   **   " << std::endl;
	std::cout << "  *****   **  *****    **   ******* **  **  *******  ** **    " << std::endl;
	std::cout << "  **  **  **  **  **   **   **   ** **  ** **     **  ***     " << std::endl;
	std::cout << "  *****  **** **   **  **   **   ** ***** **       ** ***     " << std::endl << std::endl;
}

void Output_3()
{
	std::cout << "  ******  ****       **     **  ****  **    **      " << std::endl;
	std::cout << "    **   **  **       **   **  **  ** **    **      " << std::endl;
	std::cout << "    **   **  **        ** **   **  ** **   ***      " << std::endl;
	std::cout << "    **   **  **         ***    **  ** **  ****      " << std::endl;
	std::cout << "    **    ****          ***     ****   **** **  **  " << std::endl;
	std::cout << "                                                 *  " << std::endl;
}

void Output_4()
{
	std::cout << "                                      *** *** ***  " << std::endl;
	std::cout << "  *****    ****  ***  ***     ***     *** *** ***  " << std::endl;
	std::cout << "  **  **  **  ** ********    ** **    *** *** ***  " << std::endl;
	std::cout << "  *****   **  ** ** ** **   *******    *   *   *   " << std::endl;
	std::cout << "  **  **  **  ** **    **  **     **               " << std::endl;
	std::cout << "  **   **  ****  **    ** **       **  O   O   O   " << std::endl << std::endl;
}

int main()
{
	system("color 0e");
	system("title HAPPY BIRTHDAY TO YOU, ROMA!");
	while (clock() != 1000) {};
	Output_1();
	while (clock() != 2000) {};
	Output_2();
	while (clock() != 3000) {};
	Output_3();
	while (clock() != 4000) {};
	Output_4();
	system("pause");
	return 0;
}