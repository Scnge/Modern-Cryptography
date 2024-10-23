/*
1. 请实现Schnorr身份识别方案（协议9.8），令模数是素数p，有p=2q+1，给定循环群（p的二次剩余群）的生成元g和素数阶q，私钥a，随机数k，随机响应r，输出
（1）公钥v
（2）用于验证的信息γ
（3）Alice的响应y

示例：  
Input.in  
4 5 （注：这是g q）
3 3 2  （注：这是a k r）

Output.out
5 （注：这是公钥v）
9 （注：这是γ）
4 （注：这是响应y）
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
    long long g, q, a, k, r;
    cin >> g >> q;
    cin >> a >> k >> r;

    long long p = 2 * q + 1;

    long long v = mod_exp(g, q - a, p);

    long long gamma = mod_exp(g, k, p);

    long long y = (k + r * a) % q;

    cout << v << endl;
    cout << gamma << endl;
    cout << y << endl;

    return 0;
}
