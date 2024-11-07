/*
请实现二元拉格朗日插值法（定理10.4），输入素数模数p，多项式次数m，Z_p中的m个不同元素y_1,...y_m，以及对应的多项式a_1(x), ..., a_{m+1}(x)，输出A(x, y)的所有系数（m+1阶方阵）

示例：
Input.in  
13 2（注：这是p m）
1 2 3（注：这是y_1 y_2 y_3）
1 1 1（注：这是a_1(x) = 1 + x + x^2的系数）
7 0 4（注：这是a_2(x) = 7 + 4x^2的系数）
2 9 0（注：这是a_3(x) = 2 + 9x的系数）

Output.out
10  3    1  
12  10  5
4    7   3
（注：第i行第j列表示x^{i-1}y^{j-1}的系数）
*/

/*
13 2
1 2 3
1 1 1
7 0 4
2 9 0
*/

#include <iostream>
#include <vector>

using namespace std;

int modx(int x, int y, int mod) {
    while (x < 0 || y < 0) {
        x += mod;
        y += mod;
    }
    x %= mod;
    y %= mod;
    int sum = 0;
    while (x != 0) {
        if (x & 1) {
            sum += y;
            sum %= mod;
        }
        y = y << 1;
        x = x >> 1;
    }
    return sum;
}

int modj(int x, int y, int mod) {
    int z = x - y;
    while (z < 0) {
        z += mod;
    }
    return z % mod;
}

int pow(int x, int e, int n) {
    int m = 1;
    while (e > 0) {
        if (e & 1)
            m = (m * x) % n;
        x = (x * x) % n;
        e = e >> 1;
    }
    return m;
}

int main() {
    int p, m;
    cin >> p >> m;

    vector<int> y(m + 1);
    for (int i = 1; i <= m + 1; ++i) {
        cin >> y[i];
    }

    vector< vector<int> > a(m + 2, vector<int>(m + 1));
    for (int i = 1; i <= m + 1; ++i) {
        for (int j = 0; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    vector< vector<int> > z(m + 2, vector<int>(m + 1, 0));
    for (int i = 1; i <= m + 1; ++i) {
        z[i][0] = 1;
        int c = 0;

        for (int h = 1; h <= m + 1; ++h) {
            if (h != i) {
                int k = modj(y[i], y[h], p);
                k = pow(k, p - 2, p);
                int t = modx(-y[h], k, p);
                
                for (int j = c; j >= 0; --j) {
                    z[i][j + 1] = (modx(z[i][j], k, p) + modx(z[i][j + 1], t, p)) % p;
                }
                z[i][0] = modx(z[i][0], t, p);
                ++c;
            }
        }
    }

    vector< vector<int> > A(m + 1, vector<int>(m + 1, 0));
    for (int j = 1; j <= m + 1; ++j) {
        for (int i = 0; i <= m; ++i) {
            for (int h = 0; h <= m; ++h) {
                A[i][h] = (A[i][h] + modx(a[j][i], z[j][h], p)) % p;
            }
        }
    }

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}