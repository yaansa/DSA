class Solution {
 public:
  string smallestNumber(string num, long long t) {
    auto [primeCount, ok] = getPrimeCount(t);
    if (!ok)
      return "-1";

    unordered_map<int, int> factorCount = getFactorCount(primeCount);

    if (sumValues(factorCount) > num.length())
      return construct(factorCount);

    unordered_map<int, int> prefixPrimeCount = getPrimeCount(num);

    int firstZero = num.find('0');
    if (firstZero == string::npos) {
      firstZero = num.length();
      if (isSubset(primeCount, prefixPrimeCount))
        return num;
    }

    for (int i = num.length() - 1; i >= 0; --i) {
      int d = num[i] - '0';

      prefixPrimeCount = subtract(prefixPrimeCount, kFactorCounts.at(d));

      int remaining = num.length() - i - 1;

      if (i > firstZero)
        continue;

      for (int nd = d + 1; nd <= 9; ++nd) {
        auto need =
            getFactorCount(subtract(subtract(primeCount, prefixPrimeCount),
                                    kFactorCounts.at(nd)));

        if (sumValues(need) > remaining)
          continue;

        int ones = remaining - sumValues(need);

        return num.substr(0, i) + char('0' + nd) +
               string(ones, '1') + construct(need);
      }
    }

    auto need = getFactorCount(primeCount);

    return string(num.length() + 1 - sumValues(need), '1') +
           construct(need);
  }

 private:
  static const unordered_map<int, unordered_map<int, int>> kFactorCounts;

  pair<unordered_map<int, int>, bool> getPrimeCount(long long t) {
    unordered_map<int, int> cnt{{2, 0}, {3, 0}, {5, 0}, {7, 0}};

    for (int p : {2, 3, 5, 7}) {
      while (t % p == 0) {
        ++cnt[p];
        t /= p;
      }
    }

    return {cnt, t == 1};
  }

  unordered_map<int, int> getPrimeCount(const string& s) {
    unordered_map<int, int> cnt{{2, 0}, {3, 0}, {5, 0}, {7, 0}};

    for (char c : s)
      for (auto [p, f] : kFactorCounts.at(c - '0'))
        cnt[p] += f;

    return cnt;
  }

  unordered_map<int, int> getFactorCount(
      const unordered_map<int, int>& cnt) {
    int c8 = cnt.at(2) / 3;
    int rem2 = cnt.at(2) % 3;

    int c9 = cnt.at(3) / 2;
    int c3 = cnt.at(3) % 2;

    int c4 = rem2 / 2;
    int c2 = rem2 % 2;

    int c6 = 0;

    if (c2 && c3) {
      c2 = 0;
      c3 = 0;
      c6 = 1;
    }

    if (c3 && c4) {
      c2 = 1;
      c3 = 0;
      c4 = 0;
      c6 = 1;
    }

    return {
        {2, c2},
        {3, c3},
        {4, c4},
        {5, cnt.at(5)},
        {6, c6},
        {7, cnt.at(7)},
        {8, c8},
        {9, c9},
    };
  }

  string construct(const unordered_map<int, int>& cnt) {
    string ans;

    for (int d = 2; d <= 9; ++d)
      ans += string(cnt.at(d), char('0' + d));

    return ans;
  }

  bool isSubset(const unordered_map<int, int>& need,
                const unordered_map<int, int>& have) {
    for (auto [p, c] : need)
      if (have.at(p) < c)
        return false;

    return true;
  }

  unordered_map<int, int> subtract(
      unordered_map<int, int> a,
      const unordered_map<int, int>& b) {
    for (auto [p, c] : b)
      a[p] = max(0, a[p] - c);

    return a;
  }

  int sumValues(const unordered_map<int, int>& mp) {
    int sum = 0;

    for (auto [_, v] : mp)
      sum += v;

    return sum;
  }
};

const unordered_map<int, unordered_map<int, int>>
    Solution::kFactorCounts = {
        {0, {}},
        {1, {}},
        {2, {{2, 1}}},
        {3, {{3, 1}}},
        {4, {{2, 2}}},
        {5, {{5, 1}}},
        {6, {{2, 1}, {3, 1}}},
        {7, {{7, 1}}},
        {8, {{2, 3}}},
        {9, {{3, 2}}},
    };