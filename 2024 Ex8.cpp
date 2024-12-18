/*
1. 根据推论13.10可知，满足条件
{W, X}, {X, Y}, {W, Y, Z} ∈ Γ 和  {W, Y}, {X}, {W, Z}  not ∈ Γ
的访问结构Γ不能由理想方案实现（信息率ρ至多为2/3），我们将有序四元组(W, X, Y, Z)称为Γ的证据。
请实现功能：给定一个存在证据的访问结构，输出其所有证据。
输入为参与者数量n、访问结构的基Γ0，以有序四元组的形式(W, X, Y, Z)输出所有证据，证据按照变量序号升序排列，输出以#结尾。

示例：
Input.in
4（注：这是n）
3（注：这是x，下面分别是x个最小授权子集，每个子集中包含了参与者的序号）
1 2 （注：表示{P1, P2}）
2 3
3 4

Output.out
1 2 3 4（注：表示(P1, P2, P3, P4)分别对应(W, X, Y, Z)）
4 3 2 1（注：表示(P4, P3, P2, P1)分别对应(W, X, Y, Z)）
#

邮件题目：学号-姓名-现代密码学第8次实验
源代码压缩打包作为附件
源代码压缩吧文件名：学号-8
邮件内容：说明语言和编译环境
邮箱：moderncrypt@163.com
*/
/*
4
3
1 2
2 3
3 4
*/

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

bool inclue(set<int>a, vector<set<int>>clue) {
    for (int i = 0; i < clue.size(); i++) {
        if (includes(a.begin(), a.end(), clue[i].begin(), clue[i].end())) {
            return true;
        }
    }
    return false;
}

void find_WYZ(int w, int x, int y, vector<int>& W, vector<int>& X, vector<int>& Y, vector<int>& Z, vector<set<int>>clue2, vector<set<int>>clue3, set<int>number) {
    set<int>WYZ = { w,y };
    for (auto it = number.begin(); it != number.end(); ++it) {
        if (*it == w || *it == y) {
            continue;
        }
        else {
            int z = *it;
            WYZ.insert(z);
            if (inclue(WYZ, clue2) || inclue(WYZ, clue3)) {
                set<int>WY = { w,y };
                set<int>WZ = { w,z };
                if (!inclue(WY, clue2) && !inclue(WZ, clue2)) {
                    W.push_back(w);
                    X.push_back(x);
                    Y.push_back(y);
                    Z.push_back(z);
                }
            }
            else {
                WYZ.erase(z);
            }
        }
    }
}

int main() {
    int n, m;

    cin >> n >> m;

    set<int>number;
    set<int>* Authorized_subsets = new set<int>[m];
    vector<set<int>>clue2;
    vector<set<int>>clue3;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        Authorized_subsets[i].insert(a);
        Authorized_subsets[i].insert(b);

        if (Authorized_subsets[i].size() == 2) {
            clue2.push_back(Authorized_subsets[i]);
            number.insert(Authorized_subsets[i].begin(), Authorized_subsets[i].end());
        }
        if (Authorized_subsets[i].size() == 3) {
            clue3.push_back(Authorized_subsets[i]);
            number.insert(Authorized_subsets[i].begin(), Authorized_subsets[i].end());
        }
    }

    vector<int>W;
    vector<int>X;
    vector<int>Y;
    vector<int>Z;

    for (int i = 0; i < clue2.size(); i++) {
        set<int> commonElement;
        set<int> disjointElements;
        for (int j = i + 1; j < clue2.size(); j++) {
            set_intersection(clue2[i].begin(), clue2[i].end(), clue2[j].begin(), clue2[j].end(),
                inserter(commonElement, commonElement.begin()));
            if (commonElement.size() == 1) {
                int x = *commonElement.begin();
                set_symmetric_difference(clue2[i].begin(), clue2[i].end(), clue2[j].begin(), clue2[j].end(),
                    inserter(disjointElements, disjointElements.begin()));
                int w = *disjointElements.begin();
                int y = *next(disjointElements.begin());
                find_WYZ(w, x, y, W, X, Y, Z, clue2, clue3, number);
                find_WYZ(y, x, w, W, X, Y, Z, clue2, clue3, number);
            }
        }
    }

    vector<int> indices(W.size());
    for (int i = 0; i < indices.size(); ++i) {
        indices[i] = i;
    }

    sort(indices.begin(), indices.end(), [&W](int a, int b) {
        return W[a] < W[b];
        });

    cout << endl;

    for (int i = 0; i < indices.size(); i++)
        cout << W[indices[i]] << " " << X[indices[i]] << " " << Y[indices[i]] << " " << Z[indices[i]] << endl;

    cout << "#";

    return 0;
}