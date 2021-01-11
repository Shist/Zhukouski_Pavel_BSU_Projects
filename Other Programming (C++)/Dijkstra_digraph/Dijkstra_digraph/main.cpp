#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	ifstream fin;
	ofstream fout;
	fin.open("minpath.in", fstream::in);
	fout.open("minpatho.out", fstream::out);
	int N, M, A, B;

	fin >> N;
	fin >> M;
	fin >> A;
	fin >> B;

	vector<vector<int>> graph;
	graph.resize(N);
	for (int i = 0; i < N; ++i) {
		graph[i].resize(N);
	}
	vector<int> distance;
	distance.resize(N);
	for (int i = 0; i < distance.size(); i++) {
		distance[i] = INT_MAX;
	}
	vector<bool> visit;
	visit.resize(N);

	int tmp1, tmp2, D;
	for (int i = 0; i < M; i++) {
		fin >> tmp1;
		fin >> tmp2;
		fin >> D;
		if (graph[tmp1 - 1][tmp2 - 1] == 0) {
			graph[tmp1 - 1][tmp2 - 1] = D;
		}
		else if (graph[tmp1 - 1][tmp2 - 1] > D) {
			graph[tmp1 - 1][tmp2 - 1] = D;
		}
	}

	int minInd = 0;
	int rez = 0;
	int j = A - 1;
	bool minBool = false;
	while (j < B) {
		for (int i = 0; i < graph.size(); i++) {
			if (graph[j][i] == 0) {
				continue;
			}
			if (graph[j][i] != 0 && distance[j] == INT_MAX) {
				distance[j] = graph[j][i];
				minInd = i;
				minBool = true;
			}
			if (graph[j][i] != 0 && graph[j][i] < distance[j]) {
				distance[j] = graph[j][i];
				minInd = i;
				minBool = true;
			}
		}
		if (!minBool) {
			visit[j] = true;
			j = distance[j - 1] - 1;
		}
		else {
			if (!visit[j]) {
				if (j == B - 1) {
					distance[j] = j + 1;
					break;
				}
				rez += graph[j][minInd];
				distance[j] = j + 1;
				visit[j] = true;
				j = minInd;
				minBool = false;
			}
			else {
				fout << 0;
				return 0;
			}
		}
	}

	fout << rez << endl;
	if (rez != 0) {
		for (int i = 0; i < N; i++) {
			fout << distance[i] << " ";
		}
	}
	fin.close();
	fout.close();
	return 0;
}