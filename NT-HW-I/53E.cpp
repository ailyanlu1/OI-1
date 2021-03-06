#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 10, kMaxS = 1 << kMaxN;
int n, m, k, dp[kMaxS][kMaxS], e[kMaxN];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int u, v; m --; ) {
		scanf("%d%d", &u, &v);
		-- u, -- v;
		e[u] |= 1 << v, e[v] |= 1 << u;
		dp[1 << u | 1 << v][1 << u | 1 << v] = 1;
	}
	for (int mask = 0; mask < 1 << n; ++ mask)
		for (int s = mask; s; s = (s - 1) & mask) if (dp[mask][s])
			for (int u = 0; u < n; ++ u) if (mask & 1 << u)
				for (int v = 0; v < n; ++ v) if ((~mask & 1 << v) && (e[u] & 1 << v)) {
					int nmask = mask | 1 << v;
					int ns = (s | 1 << v) & ~(1 << u);
					if ((1 << (v + 1)) > ns) dp[nmask][ns] += dp[mask][s];
				}
	int ans = 0;
	for (int mask = 0; mask < 1 << n; ++ mask)
		if (__builtin_popcount(mask) == k) ans += dp[(1 << n) - 1][mask];
	printf("%d\n", ans);
	return 0;
}
