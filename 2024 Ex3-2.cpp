/*
2. 请实现Schnorr身份识别方案，令模数是素数p，有p=2q+1，给定循环群（p的二次剩余群）的生成元g和素数阶q，公钥v，两组不同的挑战和响应(r1, y1)和(r2, y2)，输出私钥a

示例：  
Input.in  
4 5 5（注：这是g q v）
2 4 1 1（注：这是r1 y1 r2 y2）

Output.out
3 （注：这是私钥a）
*/

#include <iostream>
#include <cmath>

using namespace std;

// b^p % m
long long mod_exp(long long b, long long p, long long m) {
    long long result = 1;
    b = b % m;
    while (p > 0) {
        if (p % 2 == 1) {
            result = (result * b) % m;
        }
        p = p >> 1;
        b = (b * b) % m;
    }
    return result;
}

int main() {
    long long g, q, v;
    long long r1, y1, r2, y2;
    cin >> g >> q >> v;
    cin >> r1 >> y1 >> r2 >> y2;

    long long p = 2 * q + 1;

    // y1 - y2 = (r1 - r2) * a (mod q)
    long long x1 = (y1 - y2 + q) % q; 
    long long x2 = (r1 - r2 + q) % q; 

    long long x3 = mod_exp(x2, q - 2, q);
    long long a = (x1 * x3) % q;

    cout << a << endl;

    return 0;
}
