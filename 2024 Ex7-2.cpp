/*
请根据给定参与者集合P（共有n个参与者）以及一个已知的包含访问结构基的授权子集集合α（共有x个元素），输出对应的访问结构γ的基γ0（以#结尾），然后构造基于CNF的单调布尔电路并输出CNF的所有析取式（以#结尾）和给定秘密k时对应的分发规则（以#结尾）。
要求：
集合和变量内部全部按照变量序号升序排列；
基γ0中的最小授权子集按照变量序号升序排列（例如，{P1, P2, P4}排在{P2, P3}之前，{P2, P3}排在{P2, P4, P5}之前）；
CNF中的析取式（或门）按照变量序号升序排列（例如，P1vP2排在P2vP3之前，P2vP3排在P2vP4之前）；
分发规则中的变量命名为a，需要按照线的出现顺序升序排列（例如，a_1、a_2、a_3等），如果与门输入线数量为m，则令a_m = k - a_1 - a_2 - ... - a_{m-1}，输出分发规则时输出变量下标即可。

示例：
Input.in
4（注：这是n）
4（注：这是x，下面分别是x个授权子集，每个子集中包含了参与者的序号）
1 2 4
1 3 4
2 3
1 2 3

Output.out
1 2 4
1 3 4
2 3
#（注：这是γ0）
1 2（注：表示P1vP2，以此类推）
1 3
2 3
2 4
3 4
#
1 2（注：表示f(P1) = (a_1, a_2)，以此类推）
1 3 4
2 3 5（注：表示f(P3) = (a_2, a_3, k - a_1 - a_2 - a_3 - a_4)，以此类推）
4 5
#

*/
/*
4
4
1 2 4
1 3 4
2 3
1 2 3
*/

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<set>

using namespace std;

vector<set<int>> find_basis(const vector<set<int>>& sets) {
    vector<set<int>> basis;
    int x = sets.size();

    for (int i = 0; i < x; ++i) {
        bool isSubset = false;
        for (int j = 0; j < x; ++j) {
            if (i == j) continue;
            if (includes(sets[i].begin(), sets[i].end(), sets[j].begin(), sets[j].end())) {
                isSubset = true;
                break;
            }
        }
        if (!isSubset) {
            basis.push_back(sets[i]);
        }
    }
    return basis;
}

void removeDuplicateSets(vector<set<int>>& v) {
    for (int i = v.size() - 1; i >= 0; --i) {
        for (int j = 0; j < v.size(); ++j) {
            if (i != j && includes(v[i].begin(), v[i].end(), v[j].begin(), v[j].end())) {
                v.erase(v.begin() + i);
                break;
            }
        }
    }
}

vector<set<int>> AND(const vector<set<int>>& CNF1, const vector<set<int>>& CNF2) {
    vector<set<int>> result;

    for (const auto& set1 : CNF1) {
        for (const auto& set2 : CNF2) {
            set<int> mergedSet;
            set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(mergedSet, mergedSet.begin()));
            result.push_back(mergedSet);
        }
    }
    removeDuplicateSets(result);
    return result;
}

vector<set<int>> DNF_TO_CNF(vector<set<int>> DNF) {
    if (DNF.size() == 1) return DNF;

    vector<set<int>> CNF;
    for (const auto& elem : DNF[0]) {
        set<int> singleElementSet;
        singleElementSet.insert(elem);
        CNF.push_back(singleElementSet);
    }
    DNF.erase(DNF.begin());

    while (!DNF.empty()) {
        vector<set<int>> temp_CNF;
        for (const auto& elem : DNF[0]) {
            set<int> singleElementSet;
            singleElementSet.insert(elem);
            temp_CNF.push_back(singleElementSet);
        }
        CNF = AND(CNF, temp_CNF);
        DNF.erase(DNF.begin());
    }
    return CNF;
}

int main() {
    int n;
    cin >> n;
    int x;
    cin >> x;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<set<int>> Authorized_subsets(x);

    for (int i = 0; i < x; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string token;
        while (ss >> token) {
            Authorized_subsets[i].insert(stoi(token));
        }
    }

    vector<set<int>> basis = find_basis(Authorized_subsets);
    sort(basis.begin(), basis.end());

    cout << endl;
    for (const auto& set : basis) {
        for (const auto& number : set) {
            cout << number << " ";
        }
        cout << endl;
    }
    cout << "#" << endl;

    vector<set<int>> CNF = DNF_TO_CNF(basis);
    sort(CNF.begin(), CNF.end());

    for (const auto& set : CNF) {
        for (const auto& number : set) {
            cout << number << " ";
        }
        cout << endl;
    }
    cout << "#" << endl;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < CNF.size(); ++j) {
            if (CNF[j].find(i) != CNF[j].end()) {
                cout << j + 1 << " ";
            }
        }
        cout << endl;
    }
    cout << "#" << endl;

    return 0;
}
