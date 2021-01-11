#include <iostream>
using namespace std;
int answ, n, k, R[30], C[30], S[60];
int* D = S + 45;
void count(int r)
{
	if (r > n) { answ += (n == k); return; }
	if (R[r]) { count(r + 1); return; }
	for (int c = 1; c <= n; c++)
	{
		if (!C[c] && !S[r + c] && !D[r - c])
		{
			R[r] = C[c] = S[r + c] = D[r - c] = 1; k++;
			count(r + 1);
			R[r] = C[c] = S[r + c] = D[r - c] = 0; k--;
		}
	}
}
int main()
{
	cin >> n >> k;
	for (int i = 0, r, c; i < k; i++)
	{
		cin >> r >> c;
		R[r] = C[c] = S[r + c] = D[r - c] = 1;
	}
	count(1);
	cout << answ << std::endl;
	return 0;
}