#include "pch.h"
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
vector<vector<double> > Matrix;
double Z;
set<int> P;
int cn, bn;

bool Pivot(pair<int, int> &p) {
	int x = 0, y = 0;
	double cmax = -INT_MAX;
	vector<double> C = Matrix[0];
	vector<double> B;

	for (int i = 0; i < bn; i++) {
		B.push_back(Matrix[i][cn - 1]);
	}

	for (int i = 0; i < C.size(); i++) {
		if (cmax < C[i] && P.find(i) == P.end()) {
			cmax = C[i];
			y = i;
		}
	}
	if (cmax < 0) {
		return 0;
	}
	double bmin = INT_MAX;
	for (int i = 1; i < bn; i++) {
		double tmp = B[i] / Matrix[i][y];
		if (Matrix[i][y] != 0 && bmin > tmp) {
			bmin = tmp;
			x = i;
		}
	}

	p = make_pair(x, y);
	for (set<int>::iterator it = P.begin(); it != P.end(); it++) {
		if (Matrix[x][*it] != 0) {
			//cout<<"erase "<<*it<<endl;
			P.erase(*it);
			break;
		}
	}
	P.insert(y);
	//cout<<"add "<<y<<endl;
	return true;
}
void print() {
	for (int i = 0; i < Matrix.size(); i++) {
		for (int j = 0; j < Matrix[0].size(); j++) {
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "result z:" << -Matrix[0][cn - 1] << endl;
}
void Gaussian(pair<int, int> p) {
	int  x = p.first;
	int y = p.second;
	double norm = Matrix[x][y];
	for (int i = 0; i < cn; i++) {
		Matrix[x][i] /= norm;
	}
	for (int i = 0; i < bn && i != x; i++)
	{
		if (Matrix[i][y] != 0) {
			double tmpnorm = Matrix[i][y];
			for (int j = 0; j < cn; j++) {
				Matrix[i][j] = Matrix[i][j] - tmpnorm * Matrix[x][j];
			}
		}
	}
}
void solve() {
	pair<int, int> t;
	while(true) {
		print();
		if (Pivot(t) == 0) {
			return;
		}
		cout << t.first << " " << t.second << endl;
		for (set<int>::iterator it = P.begin(); it != P.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
		Gaussian(t);
	}
}
int main(int argc, char *argv[]) {
	cin >> cn >> bn;
	for (int i = 0; i < bn; i++) {
		vector<double> vectmp;
		for (int j = 0; j < cn; j++) {
			double tmp = 0;
			cin >> tmp;
			vectmp.push_back(tmp);
		}
		Matrix.push_back(vectmp);
	}

	for (int i = 0; i < bn-1; i++) {
		P.insert(cn-i-2);
	}
	solve();
}