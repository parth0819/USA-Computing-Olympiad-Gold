#include <bits/stdc++.h>

using ull = unsigned long long;

ull diff(ull a, ull b) {
	return a > b ? a - b : b - a;
}


bool same(ull a, ull b) {
	for (ull k = 0; k <= 39; k++) {
		ull p = std::pow(3ll, k);
		if ((((a / p) % 3) % 2) != (((b / p) % 3) % 2)) return false;
	}
	return true;
}

//constexpr ull MAX = 2e18 + 100;
constexpr ull MAX = 20;
using Pair = std::pair<ull, ull>;

template<class T1, class T2>
std::ostream &operator<<(std::ostream &out, const std::pair<T1, T2> &p) {
	out << p.first << " " << p.second;
}

std::pair<ull, ull> range_match(const std::pair<ull, ull> &r1, const std::pair<ull, ull> &r2) {
	return Pair(std::max(r1.first, r2.first), std::min(r1.second, r2.second));
}


std::map<std::pair<Pair, ull>, ull> weird_dp;
ull solve(ull x, ull y, ull d, ull val) {
	auto dp_state = std::make_pair(Pair(x, y), d);
	if (auto it = weird_dp.find(dp_state); it != weird_dp.end()) {
		return it->second;
	}
	//std::cerr << x << " " << y << " " << d << " " << val << "= " << d << "\n";
	assert(std::max(x, y) + d <= val);
	if (x == y) {
		//std::cerr << x << " " << y << " " << d << " " << val << "= " << d << "\n";
		return d;
	}
	assert(val % 3 == 0);
	ull ret = 0;
	ull v1 = val / 3;
	Pair p0[2] = { Pair(0, v1), Pair(v1*2, v1*3)};
	Pair p1(v1, v1*2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			Pair l = range_match(Pair(x, x+d), p0[i]);
			Pair r = range_match(Pair(y, y+d), p0[j]);
			// l and r are "matching this bit" x/y ranges
			if (l.first >= l.second) continue;
			if (r.first >= r.second) continue;
			// if theyre both valid d_range is the range on which theyre both correct something something
			// x + d_range.first, y+d_range.first, d_range.second - d_range.first
			Pair d_range = range_match(Pair(l.first-x, l.second-x), Pair(r.first-y, r.second-y));
			ull l_dec = v1 * (i*2);
			ull r_dec = v1 * (j*2);
			//std::cerr << "d_range = " << d_range << "\n";
			if (d_range.first >= d_range.second) continue;
			//assert(std::max(l.second, r.second) <= v1);
			//std::cerr << "call ij " << i << " " << j << "\n";
			ret += solve(x + d_range.first - l_dec, y + d_range.first - r_dec,
				d_range.second - d_range.first, v1);
		}
	}
	do {
		Pair l = range_match(Pair(x, x+d), p1);
		Pair r = range_match(Pair(y, y+d), p1);
		if (l.first >= l.second) continue;
		if (r.first >= r.second) continue;
		Pair d_range = range_match(Pair(l.first-x, l.second-x), Pair(r.first-y, r.second-y));
		ull l_dec = v1;
		ull r_dec = v1;
		//std::cerr << "d_range = " << d_range << "\n";
		if (d_range.first >= d_range.second) continue;
		//assert(std::max(l.second, r.second) <= v1);
		//std::cerr << "call 1\n";
		ret += solve(x + d_range.first - l_dec, y + d_range.first - r_dec,
			d_range.second - d_range.first, v1);
	} while (false);
	weird_dp[dp_state] = ret;
	//std::cerr << x << " " << y << " " << d << " " << val << "= " << ret << "\n";
	return ret;
		// range(x, x+d) and range(y, y+d)
		//
	/*
		if (d % 3 != 0) {
			ull good_d = d - d % 3;
			return solve(x, y, good_d) + solve(x + good_d, y + good_d, d % 3);
		}
		ull ret = solve(x / 3, y / 3, d / 3);
		return ret * (x % 3 == y % 3 ? 3 : 1);*/
}

int main() {
	int n;
	std::cin >> n;
	//ull mx = std::pow(3ll, 5);
	constexpr ull BIG_MX = 5e18;
	ull mx = 1;
	while (mx < BIG_MX) mx *= 3;
	assert(mx % 3 == 0);
	std::cerr << mx << "\n\n";
	while (n--) {
		ull d, x, y;
		std::cin >> d >> x >> y;
		d += 1;
		std::cout << solve(x, y, d, mx) << "\n";
		/*
		ull ans = 1; // how many times x y range happens

		while (x != y) {
			//std::cerr << x << " " << y << "\n";
			ull v1 = (x) % 3;
			ull v2 = (x) % 3;
			if (v1 != v2) {
				while (diff(v1, v2) != 2) {
					v1 = (v1 + 1) % 3;
					v2 = (v2 + 1) % 3;
					ans -= mult;
				}
				ans = (ans / (mult * 3)) + mult;
			}
			mult *= 3;
			x /= 3;
			y /= 3;
		}
		std::cout << ans << "\n";
		*/
	}
}
