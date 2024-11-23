#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <cassert>
#include <string>

using namespace std;

class Pkpec {
public:
    struct PublicKey {
        long long n; // n = p * q
        long long n_squared; // n^2
        long long g; // g = n + 1
    };

    struct PrivateKey {
        long long lambda; // lambda = lcm(p-1, q-1)
        long long mu; // mu = (L(g^lambda mod n^2))^-1 mod n
    };

    PublicKey pub_key;
    PrivateKey priv_key;

    Pkpec() {};

    void KeyGen(int bit_length) {
        long long p = GeneratePrime(bit_length / 2);
        long long q = GeneratePrime(bit_length / 2);

        pub_key.n = p * q;
        pub_key.n_squared = pub_key.n * pub_key.n;
        pub_key.g = pub_key.n + 1;

        long long p_minus_1 = p - 1;
        long long q_minus_1 = q - 1;
        priv_key.lambda = LCM(p_minus_1, q_minus_1);

        long long g_lambda = ModExp(pub_key.g, priv_key.lambda, pub_key.n_squared);
        priv_key.mu = ModInverse(L_function(g_lambda, pub_key.n), pub_key.n);
    }

    void Encrypt(vector<long long>& ciphertext, const string& plaintext) {
        for (size_t i = 0; i < plaintext.size(); ++i) {
            long long r;
            do {
                r = GenerateRandom(pub_key.n);
            } while (GCD(r, pub_key.n) != 1);

            long long m = static_cast<long long>(plaintext[i]);
            long long g_pow_m = ModExp(pub_key.g, m, pub_key.n_squared);
            long long r_pow_n = ModExp(r, pub_key.n, pub_key.n_squared);

            long long encrypted_char = (g_pow_m * r_pow_n) % pub_key.n_squared;
            ciphertext.push_back(encrypted_char);
        }
    }

    void Decrypt(string& plaintext, const vector<long long>& ciphertext) {
        plaintext.clear();

        for (size_t i = 0; i < ciphertext.size(); ++i) {
            long long c_lambda = ModExp(ciphertext[i], priv_key.lambda, pub_key.n_squared);
            long long l_value = L_function(c_lambda, pub_key.n);
            long long decrypted_char = (l_value * priv_key.mu) % pub_key.n;
            plaintext.push_back(static_cast<char>(decrypted_char));
        }
    }

    long long GeneratePrime(int bit_length) {
        long long prime = 1;
        while (!IsPrime(prime))
            prime = (1LL << (bit_length - 1)) + rand() % (1LL << (bit_length - 1));

        return prime;
    }

    long long GenerateRandom(long long upper_bound) {
        static random_device rd;
        static mt19937_64 gen(rd());
        uniform_int_distribution<long long> dis(1, upper_bound - 1);
        return dis(gen);
    }

    bool IsPrime(long long num) {
        if (num <= 1) 
            return false;
        if (num <= 3) 
            return true;
        if (num % 2 == 0 || num % 3 == 0) 
            return false;
        for (long long i = 5; i * i <= num; i += 6)
            if (num % i == 0 || num % (i + 2) == 0) 
                return false;

        return true;
    }

    long long LCM(long long a, long long b) {
        return (a / GCD(a, b)) * b;
    }

    long long GCD(long long a, long long b) {
        while (b != 0) {
            long long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    long long L_function(long long x, long long n) {
        return (x - 1) / n;
    }

    long long ModExp(long long base, long long exp, long long mod) {
        long long result = 1;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }

    long long ModInverse(long long a, long long n) {
        long long t = 0, new_t = 1;
        long long r = n, new_r = a;
        while (new_r != 0) {
            long long quotient = r / new_r;
            t = t - quotient * new_t;
            swap(t, new_t);
            r = r - quotient * new_r;
            swap(r, new_r);
        }

        if (r > 1)
            throw runtime_error("a is not invertible");
        if (t < 0)
            t += n;

        return t;
    }
};

int main() {
    Pkpec npe;
    npe.KeyGen(16);

    string plaintext;
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    vector<long long> ciphertext;
    npe.Encrypt(ciphertext, plaintext);

    cout << "Ciphertext: ";
    for (size_t i = 0; i < ciphertext.size(); ++i)
        cout << ciphertext[i] << " ";
    cout << endl;

    string decrypted;
    npe.Decrypt(decrypted, ciphertext);

    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
