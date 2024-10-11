/*
��ʵ��Elgamalǩ��������������Կ(p, g, q)���ֱ���ϰ��7.2�ϵ�p, ��, �£�����Ϣm����ϰ���е�x������ǩ��(��, ��)�����
��1��ǩ���Ƿ�Ϸ�
��2��ȷ��˽Կa
��3��ȷ��ǩ��ʱ�����ֵr����ϰ���е�k��

ʾ����
Input.in
11 2 9 ��ע������p g q��
8 7 8  ��ע������m �� �ģ�

Output.out
YES ��ע���Ϸ����YES���������NO��
6 ��ע������˽Կa��
7 ��ע���������ֵr��

�ʼ���Ŀ��ѧ��-����-�ִ�����ѧ��2��ʵ��
Դ����ѹ�������Ϊ����
Դ����ѹ�����ļ�����ѧ��-2
�ʼ����ݣ�˵�����Ժͱ��뻷��
���䣺moderncrypt@163.com2
*/

#include <iostream>
#include <cmath>

using namespace std;

// ģ������
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

// ��֤�Ϸ�
bool verify_signature(long long p, long long g, long long q, long long m, long long gamma, long long delta) {
    if (gamma <= 0 || gamma >= p) return false;

    long long left = mod(q, gamma, p) * mod(gamma, delta, p) % p;
    long long right = mod(g, m, p);

    return left == right;
}

// ˽Կa
long long private_key(long long p, long long g, long long q) {
    for (long long a = 1; a < p; a++) {
        if (mod(g, a, p) == q) {
            return a;
        }
    }
    return -1;
}

// ���ֵk
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
