#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    vector<long long> prefix;
    vector<vector<int>> memo;

    long long rangeSum(int l, int r) {
        return prefix[r + 1] - prefix[l];
    }

    int solve(int l, int r) {
        // Only one stone remains, so no score can be gained.
        if (l == r) {
            return 0;
        }

        int &answer = memo[l][r];
        if (answer != -1) {
            return answer;
        }

        answer = 0;

        for (int k = l; k < r; ++k) {
            long long leftSum = rangeSum(l, k);
            long long rightSum = rangeSum(k + 1, r);

            if (leftSum < rightSum) {
                answer = max(
                    answer,
                    (int)(leftSum + solve(l, k))
                );
            } 
            else if (leftSum > rightSum) {
                answer = max(
                    answer,
                    (int)(rightSum + solve(k + 1, r))
                );
            } 
            else {
                answer = max(
                    answer,
                    (int)(leftSum + max(solve(l, k), solve(k + 1, r)))
                );
            }
        }

        return answer;
    }

    int stoneGameV(vector<int>& stoneValue) {
        n = stoneValue.size();

        prefix.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        memo.assign(n, vector<int>(n, -1));

        return solve(0, n - 1);
    }
};