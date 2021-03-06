#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 100;
int n, s, c[kMaxN], q[kMaxN][kMaxN + 1], t[kMaxN][kMaxN + 1], d[kMaxN][kMaxN + 1];

int Check(int u, int v) {
	int res = 0, i = 0, j = 0;
	int who = -1;
	while (i < c[u] && j < c[v]) {
		if (t[u][i + 1] < t[v][j + 1]) ++ i; else ++ j;
		int su = d[u][i], sv = d[v][j];
		if (t[u][i] > t[v][j])
			sv += (t[u][i] - t[v][j]) * q[v][j + 1];
		else
			su += (t[v][j] - t[u][i]) * q[u][i + 1];
		if (su < sv) {
			if (who == 0) ++ res;
			who = 1;
		}
		if (su > sv) {
			if (who == 1) ++ res;
			who = 0;
		}
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &s);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &c[i]);
		for (int a, b, j = 0; j < c[i]; ++ j) {
			scanf("%d%d", &a, &b);
			q[i][j + 1] = a;
			t[i][j + 1] = t[i][j] + b;
			d[i][j + 1] = d[i][j] + a * b;
		}
	}
	int res = 0;
	for (int i = 0; i < n - 1; ++ i)
		for (int j = i + 1; j < n; ++ j)
			res += Check(i, j);
	printf("%d\n", res);
	return 0;
}
