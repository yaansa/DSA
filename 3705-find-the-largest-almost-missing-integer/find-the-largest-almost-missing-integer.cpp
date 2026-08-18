#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();

        // There is only one window: the complete array.
        if (k == n) {
            return *max_element(nums.begin(), nums.end());
        }

        unordered_map<int, int> freq;
        for (int x : nums) {
            freq[x]++;
        }

        // Each one-element subarray contains one value.
        if (k == 1) {
            int ans = -1;

            for (int x : nums) {
                if (freq[x] == 1) {
                    ans = max(ans, x);
                }
            }

            return ans;
        }

        // For 1 < k < n, only endpoints are possible.
        int ans = -1;

        if (freq[nums[0]] == 1) {
            ans = max(ans, nums[0]);
        }

        if (freq[nums[n - 1]] == 1) {
            ans = max(ans, nums[n - 1]);
        }

        return ans;
    }
};