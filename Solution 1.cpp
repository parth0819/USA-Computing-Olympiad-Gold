//C++17

#include <bits/stdc++.h>

using ll = long long;
using ull = long long;


bool solve2(ll a, ll b) {
	if (a == b) return false;
	if (a != b) return true;
}

static std::map<ull, bool> dp;

bool solve_short(const std::vector<ll> &v) { // nt sorted
	//if (v.size() == 1 && v[0] == 0) return 0;
	ull hash = 0;
	ull add = 1;
	for (auto it : v) {
		hash += add * it;
		add *= 101;
	}
	if (auto it = dp.find(hash); it != dp.end()) return it->second;

	ll ans = 0;
	ll mx = 0;
	for (auto it : v) { mx = std::max(it, mx); }
	if (mx == 0) return dp[hash] = false;
	ll mx_cnt = 0;
	for (auto it : v) { if (it == mx) mx_cnt++; }
	if (mx_cnt % 2) return dp[hash] = true;
	for (ll i = mx; i > 0; i--) {
		std::vector<ll> v2;
		for (auto it : v) {
			if (i <= it) v2.push_back(it / i);
		}
		if (v2.empty()) break;
		std::sort(v2.begin(), v2.end());
		ll prev_it = -1;
		for (ll &it : v2) {
			if (it == prev_it) continue;
			prev_it = it;
			--it;
			if (!solve_short(v2)) return dp[hash] = true;
			++it;
		}
	}
	return dp[hash] = false;
}

ll solve(const std::vector<ll> &v) { // nt sorted
	//if (v.size() == 1 && v[0] == 0) return 0;
	//std::cerr << v.size() << "\n";
	ll ans = 0;
	for (int i = 1;; i++) {
		std::vector<ll> v2;
		for (auto it : v) {
			if (i <= it) v2.push_back(it / i);
		}
		if (v2.empty()) break;
		ll prev_it = -1;
		bool prev_solve = false;
		for (auto &it : v2) {
			if (it == prev_it) {
				if (!prev_solve) ans++;
				continue;
			}
			prev_it = it;
			--it;
			prev_solve = solve_short(v2);
			if (!prev_solve) ans++;
			++it;
		}
	}
	return ans;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<ll> stones(n);
	for (auto &it : stones) {
		std::cin >> it;
	}
	if (n == 2) {
		ll ans = 0;
		for (int i = 1; i <= std::max(stones[0], stones[1]); i++) {
			ll s1 = stones[0] / i;
			ll s2 = stones[1] / i;
			if (s1 && !solve2(s1-1, s2)) ans++;
			if (s2 && !solve2(s1, s2-1)) ans++;
		}
		std::cout << ans << "\n";
		return 0;
	}
	std::cout << solve(stones) << "\n";
}
