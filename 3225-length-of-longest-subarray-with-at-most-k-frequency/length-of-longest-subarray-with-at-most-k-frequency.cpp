class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> frequency;
        int left = 0;
        int answer = 0;

        for (int right = 0; right < nums.size(); right++) {
            frequency[nums[right]]++;

            while (frequency[nums[right]] > k) {
                frequency[nums[left]]--;
                left++;
            }

            answer = max(answer, right - left + 1);
        }

        return answer;
    }
};