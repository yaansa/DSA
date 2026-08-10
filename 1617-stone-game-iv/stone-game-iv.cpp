class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);

        for (int stones = 1; stones <= n; stones++) {
            for (int k = 1; k * k <= stones; k++) {
                int square = k * k;

                // If the opponent reaches a losing state,
                // the current player wins.
                if (!dp[stones - square]) {
                    dp[stones] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};