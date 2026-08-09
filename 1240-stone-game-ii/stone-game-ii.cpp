class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffix(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        // dp[i][m], m can go up to n (since x <= 2m and max index is n)
        // We can bound m by n because 2m >= n is enough to take all.
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = n - 1; i >= 0; --i) {
            for (int m = 1; m <= n; ++m) {
                int best = 0;
                int limit = 2 * m;
                for (int x = 1; x <= limit && i + x <= n; ++x) {
                    int nextM = max(m, x);
                    // opponent gets dp[i+x][nextM], we get rest
                    int cur = suffix[i] - dp[i + x][nextM];
                    best = max(best, cur);
                }
                dp[i][m] = best;
            }
        }

        return dp[0][1];
    }
};