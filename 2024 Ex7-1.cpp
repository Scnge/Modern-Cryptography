/*
1. 请实现(t, w)-Shamir门限方案（密码体制13.1），给定公共参数t、w和p，可以实现功能：
给定t个份额(x, y)之后，还原出秘密k，同时给坐标为x'的参与者分享新的份额y'

示例：
Input.in
3 5 19（注：这是t w p）
1 1（注：这是x1 y1）
3 4（注：这是x2 y2）
5 6（注：这是x3 y3）
10（注：这是x'）

Output.out
11 （注：这是k）
9 （注：这是y'）

*/
/*
3 5 19
1 1
3 4
5 6
10
*/

#include <iostream>
#include <vector>

using namespace std;

int mod(int a, int p) {
    int m0 = p, t, q;
    int x0 = 0, x1 = 1;
    if (p == 1)
        return 0;
    while (a > 1) {
        q = a / p;
        t = p;
        p = a % p, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}

// 拉格朗日插值多项式
int lagrange(const vector<pair<int, int>>& shares, int x, int p) {
    int secret = 0;
    int t = shares.size();
    for (int i = 0; i < t; ++i) {
        int xi = shares[i].first;
        int yi = shares[i].second;
        int li = 1;
        for (int j = 0; j < t; ++j) {
            if (i != j) {
                int xj = shares[j].first;
                li = (li * (x - xj + p) % p * mod(xi - xj + p, p)) % p;
            }
        }
        secret = (secret + yi * li % p) % p;
    }
    return secret;
}

int main() {
    int t, w, p;
    cin >> t >> w >> p;

    vector<pair<int, int>> shares(t);
    for (int i = 0; i < t; ++i)
        cin >> shares[i].first >> shares[i].second;

    int x_prime;
    cin >> x_prime;

    int secret = lagrange(shares, 0, p);
    cout << endl << secret << endl;

    int y_prime = lagrange(shares, x_prime, p);
    cout << y_prime << endl;

    return 0;
}