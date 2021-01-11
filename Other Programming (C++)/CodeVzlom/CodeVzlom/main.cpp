#include <fstream>
#include <string>
using namespace std;

int main()
{
	ofstream fout("codes.txt");
	int num = 0;
	while (num != 10000)
	{
		string temp = "";
		if (num / 1000 == 0)
			temp += '0';
		if (num / 100 == 0)
			temp += '0';
		if (num / 10 == 0)
			temp += '0';
		temp += to_string(num);
		fout << temp << endl;
		num++;
	}
	fout.close();
	return 0;
}