/* ------------------------------------------------------------------|
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

注意:
不能使用代码库中的排序函数来解决这道题。

示例:

输入: [2,0,2,1,1,0]
输出: [0,0,1,1,2,2]
进阶：

一个直观的解决方案是使用计数排序的两趟扫描算法。
首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
你能想出一个仅使用常数空间的一趟扫描算法吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-colors
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	dp法
*
*	执行用时：68 ms, 在所有 C++ 提交中击败了88.56%的用户
*	内存消耗：16.4 MB, 在所有 C++ 提交中击败了90.18%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

bool canCross(vector<int>& stones) {
    int n = stones.size();
    //k的距离必须小于等于i
    //因为初始青蛙第0步只能跳距离1，类推第1步最远跳距离2
    //第n次最远只能跳距离n+1
    //所以到石头j时最远只能跳j+1步
    //因此两个石头相聚超过i的时候就无法跳过去了
    for (int i = 1; i < n; ++i) {
        if (stones[i] - stones[i - 1] > i) {
            return false;
        }
    }

    //在第i个石头能走j步
    vector<vector<bool>> dp(n, vector<bool>(n + 1, 0));
    dp[0][1] = 1;

    for (int i = 1; i < n; ++i) {
        bool flag = 0;
        for (int j = i - 1; j >= 0; --j) {
            //计算石i与石j的距离k
            int k = stones[i] - stones[j];
            if (k > j + 1) {
                break;
            }
            if (dp[j][k]) {
                flag = 1;
                dp[i][k - 1] = 1;
                dp[i][k] = 1;
                dp[i][k + 1] = 1;
            }
        }
        if (i == n - 1 && !flag) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<int> s = { 0,1,2,3,4,8,9,11 };
    canCross(s);
}