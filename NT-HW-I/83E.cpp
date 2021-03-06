#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 200000, kMaxM = 20;
int n, m, seq[kMaxN], len[kMaxN];
int dp[kMaxM + 1][1 << kMaxM];

int Get(int i, int j) {
	for (int t = m; t >= 0; -- t)
		if ((seq[i] & ((1 << t) - 1)) == (seq[j] >> (m - t))) return t;
}

void Min(int &des, int src) {
	des = min(des, src);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		static char buf[32];
		scanf("%s", buf);
		m = strlen(buf);
		for (int j = 0; j < m; ++ j) seq[i] = seq[i] << 1 | (buf[j] - '0');
	}
	int ans = m;
	for (int i = 1; i < n; ++ i) {
		len[i] = Get(i - 1, i);
		ans += m - len[i];
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1; i < n; ++ i)
		for (int j = 0; j <= m; ++ j) { 
			int t = dp[j][seq[i] >> (m - j)] + (m - j) - (m - len[i]);
			for (int k = 0; k <= m; ++ k) Min(dp[k][seq[i - 1] & ((1 << k) - 1)], t); 
		}
	int delta = 0;
	for (int i = 0; i <= m; ++ i)
		for (int j = 0; j < 1 << i; ++ j) Min(delta, dp[i][j]);
	ans += delta;
	printf("%d\n", ans);
	return 0;
}
