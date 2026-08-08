class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // last[j] = position used to match word2[j]
        // in a right-to-left exact matching.
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                --j;
            }
            --i;
        }

        vector<int> answer;
        j = 0;
        bool changed = false;

        for (i = 0; i < n && j < m; ++i) {
            if (word1[i] == word2[j]) {
                // Exact match: always take the earliest possible index.
                answer.push_back(i);
                ++j;
            } else if (!changed &&
                       (j == m - 1 || i < last[j + 1])) {
                // Use the one allowed modification.
                answer.push_back(i);
                ++j;
                changed = true;
            }
        }

        if (j == m) {
            return answer;
        }

        return {};
    }
};