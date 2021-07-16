#include <bits/stdc++.h>

#define MAX 400

int dp[MAX][MAX][2];
int data[MAX];
int n;

int solve(int a, int b, bool sides) {
	int &ret = dp[a][b][sides];
	if (ret != -1) return ret;
	int diff = (b - a) + 1;
	assert(diff > 1);
	ret = diff;
	#define setmin(expr) ret = std::min(ret, (expr))
	if (sides) {
		assert(data[a] == data[b]);
		if (diff > 2) {
			setmin(solve(a+1, b-1, false));
		}
		if (diff == 2) setmin(0);
		for (int i = a+1; i < b; i++) {
			if (data[i] == data[a]) {
				setmin(solve(a, i, true) + solve(i, b, true));
			}
		}
	}
	else {

		if (data[a] == data[b]) {
			setmin(solve(a, b, true) + 1);
		}
		setmin(solve(a, b-1, false) + 1);
		setmin(solve(a+1, b, false) + 1);
		for (int i = a; i < b; i++) {
			if (data[a] == data[i]) {
				setmin(solve(a, i, true) + 1 + solve(i+1, b, false));
			}
		}
		for (int i = a+1; i <= b; i++) {
			if (data[i] == data[b]) {
				setmin(solve(a, i-1, false) + 1 + solve(i, b, true));
			}
		}
	}
	return ret;
}

int main() {
	std::cin >> n;
	for (int x = 0; x < n; x++) {
		std::cin >> data[x];
		for (int y = 0; y < n; y++) {
			dp[x][y][0] = dp[x][y][1] = -1;
		}
		dp[x][x][0] = 1;
		dp[x][x][1] = 0;
	}
	std::cout << solve(0, n-1, false) << "\n";
}
