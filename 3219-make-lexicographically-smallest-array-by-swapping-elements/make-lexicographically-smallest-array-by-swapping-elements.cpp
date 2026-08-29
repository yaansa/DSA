class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        
        // Step 1: Pair (value, original_index)
        vector<pair<int, int>> pairs(n);
        for (int i = 0; i < n; i++) {
            pairs[i] = {nums[i], i};
        }
        
        // Step 2: Sort by value
        sort(pairs.begin(), pairs.end());
        
        // Step 3 & 4: Form groups and place values
        vector<int> result(n);
        int i = 0;
        
        while (i < n) {
            // Collect all indices in current group
            vector<int> groupIndices;
            vector<int> groupValues;
            
            int j = i;
            while (j < n) {
                groupIndices.push_back(pairs[j].second);
                groupValues.push_back(pairs[j].first);
                
                // Check if next value belongs to same group
                if (j + 1 < n && pairs[j + 1].first - pairs[j].first <= limit) {
                    j++;
                } else {
                    break;
                }
            }
            
            // Sort indices to place smallest values at smallest positions
            sort(groupIndices.begin(), groupIndices.end());
            
            // Assign values to positions
            for (int k = 0; k < groupIndices.size(); k++) {
                result[groupIndices[k]] = groupValues[k];
            }
            
            // Move to next group
            i = j + 1;
        }
        
        return result;
    }
};