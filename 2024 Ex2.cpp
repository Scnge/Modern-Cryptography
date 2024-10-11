/*
请实现Elgamal签名方案，给定公钥(p, g, q)（分别是习题7.2上的p, α, β），消息m（即习题中的x）及其签名(γ, δ)，输出
（1）签名是否合法
（2）确定私钥a
（3）确定签名时的随机值r（即习题中的k）

示例：
Input.in
11 2 9 （注：这是p g q）
8 7 8  （注：这是m γ δ）

Output.out
YES （注：合法输出YES，否则输出NO）
6 （注：这是私钥a）
7 （注：这是随机值r）

邮件题目：学号-姓名-现代密码学第2次实验
源代码压缩打包作为附件
源代码压缩吧文件名：学号-2
邮件内容：说明语言和编译环境
邮箱：moderncrypt@163.com2
*/

#include <iostream>
#include <cmath>

using namespace std;

// 模幂运算
long long mod(long long x, long long y, long long p) {
    long long result = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1) {
            result = (result * x) % p;
        }
        y = y >> 1;
        x = (x * x) % p;
    }
    return result;
}

// 验证合法
bool verify_signature(long long p, long long g, long long q, long long m, long long gamma, long long delta) {
    if (gamma <= 0 || gamma >= p) return false;

    long long left = mod(q, gamma, p) * mod(gamma, delta, p) % p;
    long long right = mod(g, m, p);

    return left == right;
}

// 私钥a
long long private_key(long long p, long long g, long long q) {
    for (long long a = 1; a < p; a++) {
        if (mod(g, a, p) == q) {
            return a;
        }
    }
    return -1;
}

// 随机值k
long long random_k(long long p, long long g, long long gamma) {
    for (long long k = 1; k < p; k++) {
        if (mod(g, k, p) == gamma) {
            return k;
        }
    }
    return -1;
}

int main() {
    long long p, g, q;
    long long m, gamma, delta;

    cin >> p >> g >> q;
    cin >> m >> gamma >> delta;

    if (verify_signature(p, g, q, m, gamma, delta)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
        return 0;
    }

    long long a = private_key(p, g, q);
    if (a != -1) {
        cout << a << endl;
    }

    long long r = random_k(p, g, gamma);
    if (r != -1) {
        cout << r << endl;
    }

    return 0;
}
