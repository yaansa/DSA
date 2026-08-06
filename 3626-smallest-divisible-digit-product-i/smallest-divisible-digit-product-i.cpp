class Solution {
public:
    int smallestNumber(int n, int t) {
        int x = n;
        while (true) {
            int prod = 1;
            int temp = x;
            while (temp > 0) {
                prod *= temp % 10;
                temp /= 10;
            }
            if (prod % t == 0) {
                return x;
            }
            ++x;
        }
    }
};