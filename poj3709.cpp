#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

const int maxn = 5e5 + 10;

LL a[maxn], sum[maxn], dp[maxn];
int q[maxn];

LL A(LL x) {
	return dp[x] - sum[x] + a[x+1] * x;
}

LL B(LL x) {
	return a[x+1];
}

int main() {
//	freopen("in", "r", stdin);
	int t;
	scanf("%d", &t);
	while(t--) {
		int n, k;
		scanf("%d%d", &n, &k);
		for( int i=1; i<=n; i++ ) {
			scanf("%lld", &a[i]);
			sum[i] = sum[i-1] + a[i];
		}
		int head = 0, tail = 0;
		q[tail++] = 0;
		for( int i=1; i<=n; i++ ) {
			while(head + 1 < tail) {
				int x = q[head], y = q[head+1];
				if(A(x)-A(y)>=i*(B(x)-B(y))) head++;
				else break;
			}
			dp[i] = dp[q[head]] + sum[i] - sum[q[head]] - a[q[head]+1] * (i - q[head]);
			if(i-(k-1) >= k) {
				while(head + 1 < tail) {
					int x = q[tail-2], y = q[tail-1], z = i - (k-1);
					if((A(x) - A(y)) * (B(y) - B(z)) >= (A(y) - A(z)) * (B(x) - B(y))) {
						tail--;
					}
					else break;
				}
				q[tail++] = i - (k-1);
			}
		}
		printf("%lld\n", dp[n]);
	}
	return 0;
}
