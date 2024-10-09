/*
请实现RSA生成器，在给定模数N、其分解p和q、指数e（即习题8.4中的b）和种子s0的情况下，计算该生成器的周期t，并输出前i个比特.

示例：
Input.in
33 3 11 （注：这是N p q）
7 5 8  （注：这是e s0 i）
Output.out
4 （注：这是t）
00010001 （注：这是前i个比特）
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
