class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1e9 + 7;
        
        // We need C(n+k-1, 2k)
        int N = n + k - 1;
        int R = 2 * k;
        
        // Compute C(N, R) mod MOD
        // C(N, R) = N! / (R! * (N-R)!)
        // Use modular inverse for division
        
        long long numerator = 1;
        long long denominator = 1;
        
        // Optimize: C(N, R) = C(N, N-R), use smaller R
        R = min(R, N - R);
        
        for (int i = 0; i < R; i++) {
            numerator = (numerator * (N - i)) % MOD;
            denominator = (denominator * (i + 1)) % MOD;
        }
        
        // Modular inverse using Fermat's little theorem: a^(-1) ≡ a^(MOD-2) mod MOD
        long long invDenom = modPow(denominator, MOD - 2, MOD);
        
        return (numerator * invDenom) % MOD;
    }
    
private:
    long long modPow(long long base, long long exp, int mod) {
        long long result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) result = (result * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }
};