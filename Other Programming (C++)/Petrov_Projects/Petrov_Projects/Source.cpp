#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class MyPair
{
public:
	long long first;
	char second;
	MyPair(long long f, char s)
	{
		first = f;
		second = s;
	}
	MyPair()
	{
		first = 0;
		second = '[';
	}
};

void Merge(MyPair* arr, long long N, long long first, long long last)
{
	long long middle, start, final, j;
	MyPair* temp_arr = new MyPair[N];
	middle = (first + last) / 2;
	start = first;
	final = middle + 1;
	for (j = first; j <= last; j++)
	{
		if ((start <= middle) && ((final > last) || (arr[start].first < arr[final].first)))
		{
			temp_arr[j].first = arr[start].first;
			temp_arr[j].second = arr[start].second;
			start++;
		}
		else
		{
			temp_arr[j].first = arr[final].first;
			temp_arr[j].second = arr[final].second;
			final++;
		}
	}
	for (j = first; j <= last; j++)
	{
		arr[j] = temp_arr[j];
	}
	delete[] temp_arr;
}

void MergeSort(MyPair* arr, long long N, long long first, long long last)
{
	if (first < last)
	{
		MergeSort(arr, N, first, (first + last) / 2);
		MergeSort(arr, N, (first + last) / 2 + 1, last);
		Merge(arr, N, first, last);
	}
}

int main(int argc, char* argv[])
{
	ifstream input("rect.in");
	ofstream output("rect.out");
	long long Xmax = 0;
	long long Ymax = 0;
	long long N = 0;
	input >> Xmax;
	input >> Ymax;
	input >> N;
	long long left_top_X = 0;
	long long right_bottom_Y = 0;
	long long right_bottom_X = 0;
	long long left_top_y = 0;
	long long end_X = 0;
	long long end_Y = 0;
	long long end_Num = 0;
	long long counts = 0;
	long long additional_coord = 0;
	vector<pair<long long, char>> rect_arr;
	rect_arr.reserve(2 * N);
	long long i = 0;
	for (long long t = 0; t < N; t++)
	{
		input >> left_top_X;
		input >> right_bottom_Y;
		input >> right_bottom_X;
		input >> left_top_y;
		long long cur_crds = 0;
		long long FirstDestination = 0;
		long long SecondDestination = 0;
		if (left_top_y == 0)
			cur_crds = INT32_MAX;
		else
		{
			FirstDestination = left_top_X * Ymax;
			SecondDestination = left_top_y * Xmax;
			if (SecondDestination > FirstDestination)
				cur_crds = (left_top_y - 1 + FirstDestination) / left_top_y;
			else
				cur_crds = Xmax - SecondDestination / left_top_X + Ymax;
		}
		rect_arr.push_back({ cur_crds, '[' });
		if (right_bottom_Y == 0)
			cur_crds = INT32_MAX;
		else
		{
			FirstDestination = right_bottom_X * Ymax;
			SecondDestination = right_bottom_Y * Xmax;
			if (SecondDestination > FirstDestination)
				cur_crds = FirstDestination / right_bottom_Y;
			else
				cur_crds = Xmax - (right_bottom_X - 1 + SecondDestination) / right_bottom_X + Ymax;
		}
		rect_arr.push_back({ cur_crds, ']' });
	}
	sort(rect_arr.begin(), rect_arr.end());
	for(i = 0; i < 2 * N; i++)
	{
		if (rect_arr[i].second == '[')
			counts++;
		else
			counts--;
		if (counts > end_Num)
		{
			end_Num = counts;
			additional_coord = rect_arr[i].first;
		}
	}
	if (additional_coord > Xmax)
	{
		end_X = Xmax;
		end_Y = Xmax + Ymax - additional_coord;
	}
	else
	{
		end_X = additional_coord;
		end_Y = Ymax;
	}
	output << end_Num << " " << end_X << " " << end_Y;
	input.close();
	output.close();
	return 0;
}