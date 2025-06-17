const int MOD = 1e9 + 7;
const int MX = 1e5;

long long fact[MX];
long long inv_fact[MX];

class Solution {
    long long qpow(long long x, int n) {
        long long res = 1;
        while (n) {
            if (n & 1) {
                res = res * x % MOD;
            }
            x = x * x % MOD;
            n >>= 1;
        }
        return res;
    }

    long long comb(int n, int m) {
        return fact[n] * inv_fact[m] % MOD * inv_fact[n - m] % MOD;
    }
    void init() {
        if (fact[0]) {
            return;
        }
        fact[0] = 1;
        for (int i = 1; i < MX; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }

        inv_fact[MX - 1] = qpow(fact[MX - 1], MOD - 2);
        for (int i = MX - 1; i; i--) {
            inv_fact[i - 1] = inv_fact[i] * i % MOD;
        }
    }

public:
    int countGoodArrays(int n, int m, int k) {
        init();
        return comb(n - 1, k) * m % MOD * qpow(m - 1, n - k - 1) % MOD;
    }
};



************************************************************************************************************************************************************************************
#include <vector>

class Solution {
private:
    const int MOD = 1e9 + 7;

    // Calculates (x^n) % MOD in O(log n) time.
    long long power(long long x, int n) {
        long long res = 1;
        x %= MOD;
        while (n > 0) {
            if (n & 1) { // If n is odd
                res = (res * x) % MOD;
            }
            x = (x * x) % MOD;
            n >>= 1; // n = n / 2
        }
        return res;
    }

    // Calculates the modular inverse of n using Fermat's Little Theorem.
    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

    // Calculates C(n, k) % MOD in O(k + log MOD) time.
    long long combinations(int n, int k) {
        if (k < 0 || k > n) {
            return 0;
        }
        if (k == 0 || k == n) {
            return 1;
        }
        // Use the identity C(n, k) = C(n, n-k) to optimize.
        if (k > n / 2) {
            k = n - k;
        }

        // Calculate [n * (n-1) * ... * (n-k+1)] / k!
        long long numerator = 1;
        for (int i = 0; i < k; ++i) {
            numerator = (numerator * (n - i)) % MOD;
        }

        long long denominator_fact = 1;
        for (int i = 1; i <= k; ++i) {
            denominator_fact = (denominator_fact * i) % MOD;
        }

        return (numerator * modInverse(denominator_fact)) % MOD;
    }

public:
    int countGoodArrays(int n, int m, int k) {
        if (n - 1 < k) {
            return 0;
        }
        
        long long combinations_val = combinations(n - 1, k);
        long long m_power_val = power(m - 1, n - k - 1);

        long long result = (combinations_val * m) % MOD;
        result = (result * m_power_val) % MOD;
        
        return static_cast<int>(result);
    }
};