#include <iostream>
#include <cmath>
                                                                                                                                                                                                                                                                                                                                                           double ln(double x)
{
	double X = sqrt(x);
	return X;
}                                                                                                                                                                                                            
using namespace std;



double fpuLog(double x)
{
	__asm
	{
		fld x
		fld1
		fadd
		fsqrt
		fst x
	}
	return x;
}

double taylorLog(double x, int accuracy)
{
	const double oneTenth = 0.1;
	const int two = 2;
	__asm
	{
		fld oneTenth
		fld1
		mov ecx, accuracy
		inc ecx
		L1 : fmul st(0), st(1)
			 loop L1
			 fstp st(1)

			 fild two
			 fiadd two
			 fld x
			 fmul x
			 fdiv st(0), st(1)
			 fidiv two
			 fchs
			 fld1
			 fld x
			 fidiv two
			 fadd

			 L2 : fadd st(0), st(1)
				  fld st(1)
				  fabs
				  fcomip st(0), st(4)
				  jb L3

				  fld st(2)
				  fiadd two
				  fst st(3)
				  fld1
				  fiadd two
				  fsubp st(1), st(0)

				  fld st(2)
				  fmul
				  fmul x
				  fdiv st(0), st(3)
				  fchs
				  fstp st(2)

				  jmp L2

				  L3 : fstp x
	}
	return x;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "Incorrect number of parameters!";
		return -1;
	}

	double x = atof(argv[1]);
	int k = atoi(argv[2]);

	cout.precision(k);
	cout << "log(x+1) as computed by library Math: " << ln(x + 1) << '\n';
	cout << "log(x+1) as computed by FPU: " << fpuLog(x) << '\n';
	return 0;
}