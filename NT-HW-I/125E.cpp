#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 5000, kMaxM = 100000;
int n, m, k, ds[kMaxN];
bool cho[kMaxM];

int Find(int x) {
	return (x == ds[x] ? x : ds[x] = Find(ds[x]));
}

struct Edge {
	int u, v, x, y;
	double c;
	bool operator < (const Edge &t) const {
		return (c < t.c);
	}
} e[kMaxM];

int Calc(double add) {
	for (int i = 0; i < m; ++ i) {
		cho[i] = false;
		if (e[i].x == 1) e[i].c += add;
	}
	for (int i = 0; i < n; ++ i) ds[i] = i;
	random_shuffle(e, e + m);
	sort(e, e + m);
	int res = 0;
	for (int i = 0; i < m; ++ i) {
		int u = Find(e[i].u), v = Find(e[i].v);
		if (u != v) {
			res += e[i].x;
			ds[u] = v;
			cho[e[i].y] = true;
		}
	}
	for (int i = 0; i < m; ++ i)
		if (e[i].x == 1) e[i].c -= add;
	return res;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; ++ i) {
		scanf("%d%d%lf", &e[i].u, &e[i].v, &e[i].c);
		-- e[i].u, -- e[i].v;
		e[i].x = (e[i].u == 0 || e[i].v == 0);
		e[i].y = i;
	}
	double lb = -100000, rb = 100000;
	if (Calc(lb) < k || Calc(rb) > k) {
		puts("-1");
		return 0;
	}
	for ( ; ; ) {
		double mid = (lb + rb) * 0.5;
		int t = Calc(mid);
		if (t == k) break;
		t > k ? lb = mid : rb = mid;
	}
	printf("%d\n", n - 1);
	for (int i = 0, fir = 1; i < m; ++ i)
		if (cho[i]) {
			if (fir) fir = 0;
			else printf(" ");
			printf("%d", i + 1);
		}
	puts("");
	return 0;
}
