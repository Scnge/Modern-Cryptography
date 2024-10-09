/*
��ʵ��RSA���������ڸ���ģ��N����ֽ�p��q��ָ��e����ϰ��8.4�е�b��������s0������£������������������t�������ǰi������.

ʾ����
Input.in
33 3 11 ��ע������N p q��
7 5 8  ��ע������e s0 i��
Output.out
4 ��ע������t��
00010001 ��ע������ǰi�����أ�
*/

#include <iostream>
#include <vector>

using namespace std;

int mod_pow(int base, int exponent, int modulus) {
    int result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    int n, p, q, e, initial_value, num_bits;
    cin >> n >> p >> q >> e >> initial_value >> num_bits;

    vector<int> sequence;
    vector<int> bits;

    sequence.push_back(initial_value);
    int period = 0;
    int index = 0;

    while (true) {
        int next_value = mod_pow(sequence[index], e, n);
        sequence.push_back(next_value);

        if (index < num_bits)
            bits.push_back(next_value % 2);

        if (period == 0) {
            for (int k = 0; k <= index; k++) {
                if (sequence[k] == next_value) {
                    period = index + 1 - k;
                    break;
                }
            }
        }

        if (period != 0 && index >= num_bits - 1)
            break;

        index++;
    }

    cout << period << endl;
    for (int bit : bits) {
        cout << bit;
    }
    return 0;
}
