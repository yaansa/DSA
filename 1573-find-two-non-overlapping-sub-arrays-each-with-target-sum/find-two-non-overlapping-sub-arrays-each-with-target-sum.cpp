class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        vector<int> best(n + 1, INF);

        int left = 0;
        long long sum = 0;
        int answer = INF;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > target && left <= right) {
                sum -= arr[left];
                left++;
            }

            best[right + 1] = best[right];

            if (sum == target) {
                int length = right - left + 1;

                // best[left] contains a subarray before current [left...right]
                if (best[left] != INF) {
                    answer = min(answer, best[left] + length);
                }

                // Store the shortest valid subarray ending at or before right
                best[right + 1] = min(best[right + 1], length);
            }
        }

        return answer == INF ? -1 : answer;
    }
};