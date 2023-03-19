#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//#include <iostream>
//using namespace std;
//
//
//struct TreeNode {
//    int val;
//    TreeNode* left;
//    TreeNode* right;
//    TreeNode() : val(0), left(nullptr), right(nullptr) {}
//    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
//};
//
//
//void flatten(TreeNode* root) {
//    if (root == nullptr)
//        return;
//    flatten(root->left);
//    flatten(root->right);
//    // 后序
//    TreeNode* rightNode = root->right; //保存一下要移动的右节点
//    TreeNode* leftTail = root->left; //找左节点串的尾
//    while (leftTail)
//        leftTail = leftTail->right;
//    // 改连接关系
//    leftTail = rightNode; // 去改leftTail没用，上层的指针朝向没改
//    root->right = root->left;
//    root->left = nullptr;
//}
//
//int main()
//{
//    struct TreeNode n1(1);
//    struct TreeNode n2(2);
//    struct TreeNode n3(3);
//    struct TreeNode n4(4);
//    struct TreeNode n5(5);
//    struct TreeNode n6(6);
//
//    n1.left = &n2;
//    n1.right = &n5;
//    n2.left = &n3;
//    n2.right = &n4;
//    n5.right = &n6;
//
//    flatten(&n1);
//
//    return 0;
//}
//
//
////class solution {
////public:
////    void flatten(treenode* root) {
////        if (!root)   return;//递归出口
////        flatten(root->left);
////        flatten(root->right);
////        //现在可以认为左右子树都已经处理好了
////        auto tmp = root->right;//临时保存右子树
////        root->right = root->left;//左子树接到右边
////        root->left = null;//左子树置空
////        //寻找左子树的最右节点
////        while (root->right)  root = root->right;
////        root->right = tmp; .//右子树接到左子树的最右节点
////    }
////};
//




//class Solution {
//public:
//    vector<vector<string>> res;
//
//    vector<vector<string>> solveNQueens(int n) {
//        vector<string> board(n, string(n, '.'));
//        backtrack(board, 0);
//        return res;
//    }
//
//    void backtrack(vector<string>& board, int row) {
//        if (row == board.size()) { //到达目的地
//            res.push_back(board);
//            return;
//        }
//
//        for (int coli = 0; coli < board[0].size(); coli++) {
//            //前序做出决策
//            if (!isValid(board, row, coli)) continue;
//
//            board[row][coli] = 'Q';
//
//            backtrack(board, row + 1);
//
//            //后序撤销决策
//            board[row][coli] = '.';
//        }
//
//    }
//
//    bool isValid(vector<string>& board, int row, int col) { //设定下棋规则，这和全排列中的visited是一个效果
//        //检查上方是否有皇后
//        for (int i = 0; i < row; i++) {
//            if (board[i][col] == 'Q')
//                return false;
//        }
//        //检查左上方是否有皇后
//        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
//            if (board[i][j] == 'Q')
//                return false;
//        }
//        //检查右上方是否有皇后
//        for (int i = row - 1, j = col + 1; i >= 0 && j < board[0].size(); i--, j++) {
//            if (board[i][j] == 'Q')
//                return false;
//        }
//
//        return true;
//    }
//};
//
//
//void traverse(const vector<int>& v, int index) {
//    if (index == v.size())
//        return;
//    cout << v[index] << " ";
//    traverse(v, index + 1);
//}
//
//int test() {
//    for (int i = 0; i < 5; i++) {
//        for (int j = 0; j < 6; j++) {
//            if (j == 3)
//                return i+j;
//        }
//    }
//}


//int main() {
//    //Solution s;
//    //s.solveNQueens(10);
//
//    //vector<int> v = { 1,2,3,4,5,6 };
//    //traverse(v, 0);
//    vector<vector<int>> board = {
//        {1, 2, 3},
//        {4, 0, 5}
//    };
//
//    string target = "123450"; //终点
//    string start; //起点
//    int m = 2, n = 3; //本题的棋盘尺寸
//
//    for (int i = 0; i < m; i++) {
//        for (int j = 0; j < n; j++)
//            start.push_back((char)(board[i][j] + '0'));
//    }
//    cout << start << endl;
//    cout << typeid(start).name() << endl;
//
//
//
//    return 0;
//}

//class Solution {
//public:
//    int slidingPuzzle(vector<vector<int>>& board) {
//        //将二维数组拉成一维数组后，转换成了BFS问题，每个结点的相邻结点就是0的不同移动情况
//        string target = "123450"; //终点
//        string start; //起点
//        int m = 2, n = 3; //本题的棋盘尺寸
//
//        for (int i = 0; i < m; i++) {
//            for (int j = 0; j < n; j++)
//                start.push_back((char)(board[i][j] + '0'));
//        }
//
//        queue<string> q;
//        q.push(start); //队列初始化
//        unordered_set<string> visited; //已经遍历过的可能性，防止走回头路
//        int step = 0;
//
//        vector<vector<int>> neighbor = {
//            {1, 3},
//            {0, 2, 4},
//            {1, 5},
//            {0, 4},
//            {1, 3, 5},
//            {2, 4}
//        }; //遍历拉成的一维数组中的元素的二维映射关系，因为本题board尺寸较小，可以直接遍历
//
//        while (!q.empty()) {
//            int levelSize = q.size();
//            for (int i = 0; i < levelSize; i++) {
//                string front = q.front();
//                q.pop();
//
//                //到达目标
//                if (front == target)
//                    return step;
//
//                //找到0在front里的位置，以此来确定fornt有几个邻接点
//                int index = 0;
//                string::iterator it = front.begin();
//                while (*it != '0')
//                    index++;
//                //遍历front的所有邻结点
//                for (int i = 0; i < neighbor[index].size(); i++) {
//                    string exchange = front; //交换0的位置
//                    exchange[index] = front[neighbor[index][i]];
//                    exchange[neighbor[index][i]] = '0';
//
//                    if (!visited.count(exchange)) {//若不在visited里就加入队列
//                        q.push(exchange);
//                        visited.insert(exchange);
//                    }
//                }
//            }
//            step++;
//        }
//        return -1;
//    }
//};
//
//int main() {
//
//    vector<vector<int>> board = {
//        {1, 2, 3},
//        {4, 0, 5}
//    };
//    Solution s;
//    cout << s.slidingPuzzle(board) << endl;
//
//    return 0;
//}


//class Solution {
//public:
//    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
//        //满足有向权图，无负权边提前，用dijkstra算法
//        //构造图的邻接表
//        unordered_map<int, vector<pair<int, int>>> graph;
//        for (int i = 0; i < times.size(); i++) {
//            graph[times[i][0]].push_back(make_pair(times[i][1], times[i][2]));
//        }
//
//        //distTo是从起点k(start)到各个其他结点的最短路径和
//        vector<int> distTo = dijkstra(k, graph, n);
//        int res = 0;
//        return res;
//    }
//
//    vector<int> dijkstra(int start, unordered_map<int, vector<pair<int, int>>>& graph, int n) {
//        vector<int> distTo(n + 1, INT_MAX); //因为有n个结点，且第一个结点是从1开始的，所以给n+1个
//        distTo[start] = 0; //设起点到起点的距离为0
//
//        struct Greater {
//            bool operator()(const pair<int, int>& parent, const pair<int, int>& child) const {
//                return parent.second > child.second;
//            }
//        };
//
//        //优先级队列的底层是二叉堆，默认容器用可以随机访问的vector，排小堆
//        priority_queue<pair<int, int>, vector<pair<int, int>>, Greater> pq;
//
//        return distTo;
//    }
//
//};
//
//int main() {
//    return 0;
//}

//class Solution {
//public:
//    bool noCycle = true;
//    vector<vector<int>> buildGraph(int numCourses, vector<vector<int>>& prerequisites) {
//        vector<vector<int>> graph(numCourses);
//        for (int i = 0; i < numCourses; i++) {
//            graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
//        }
//        return graph;
//    }
//    void traverse(vector<vector<int>>& graph, int s, vector<bool>& visited, vector<bool>& onPath) {
//        if (onPath[s])
//            noCycle = false;
//        if (!noCycle || visited[s])
//            return;
//        //前序
//        visited[s] = true;
//        onPath[s] = true;
//        for (int i = 0; i < graph[s].size(); i++) {
//            traverse(graph, i, visited, onPath);
//        }
//        //后序
//        onPath[s] = false;
//    }
//
//    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
//        vector<vector<int>> graph = buildGraph(numCourses, prerequisites);
//        vector<bool> visited(numCourses, false);
//        vector<bool> onPath(numCourses, false);
//
//        for (int i = 0; i < graph.size(); i++) {
//            traverse(graph, i, visited, onPath);
//        }
//        return noCycle;
//    }
//};
//
//int main() {
//    int numCourses = 2;
//    vector<vector<int>> prerequisites = { {1,0}, {0,1} };
//    Solution s;
//    cout << s.canFinish(numCourses, prerequisites) << endl;
//	return 0;
//}


//class W
//{
//public:
//	W(int x = 0)
//	{
//		cout << "W()" << endl;
//	}
//
//	W(const W& w)
//	{
//		cout << "W(const W& w)" << endl;
//	}
//
//	W& operator=(const W& w)
//	{
//		cout << "W& operator=(const W& w)" << endl;
//		return *this;
//	}
//
//	~W()
//	{
//		cout << "~W()" << endl;
//	}
//};
//
//int main() {
//	W w1;
//	return 0;
//}

//int main() {
//	char char2[] = "abcd";
//	char2[2] = '3';
//	cout << char2 << endl;
//	const char* pchar3 = "abcd";
//	int* p5 = new int[5]{ 1,2,3,4,5 };
//	cout << *p5 + 2 << endl;
//	return 0;
//}

//class HeapOnly {
//public:
//	static HeapOnly* CreateObj() {
//		return new HeapOnly;
//	}
//private:
//	HeapOnly(){}
//};
//
//int main() {
//	HeapOnly* obj1 = HeapOnly::CreateObj();
//	static HeapOnly obj2;
//	return 0;
//}

//class A {
//public:
//    void Print(); //类成员声明
//private:
//    int _a;
//};
//
//void A::Print() { 
//    cout << _a << endl; 
//} //类成员定义
//
//
//int main() {
//    return 0;
//}

//class Singleton {
//public:
//	static Singleton* GetInstance() {
//		return _spInst;
//	}
//	void Print() {
//		cout << _spInst << endl;
//	}
//private:
//	Singleton() {}
//	Singleton(const Singleton&) = delete; //防拷贝
//
//	int _a;
//	//static Singleton _sInst; //声明，否则构造私有取不到，声明的为类成员就能令定义时取到
//	static Singleton* _spInst; //声明
//};
//
////Singleton Singleton::_sInst; // 定义成全局的，而不是私有的，满足饿汉模式的要求（main函数之前就被初始化）
//Singleton* Singleton::_spInst = new Singleton; //定义
//
//int main() {
//	Singleton::GetInstance()->Print(); //只能这么取，因为不能实例化
//	return 0;
//}

////InfoMgr 信息管理
//class InfoMgr {
//public:
//	static InfoMgr* GetInstance() {
//		return _spInst;
//	}
//
//	void SetAddress(const string& s) {
//		_address = s;
//	}
//
//	string GetAddress() {
//		return _address;
//	}
//
//private:
//	InfoMgr() {}
//	InfoMgr(const InfoMgr&) = delete;
//	
//	string _address;
//	int _key;
//
//	static InfoMgr* _spInst;
//};
//
//InfoMgr* InfoMgr::_spInst = new InfoMgr; //定义
//
//int main() {
//	return 0;
//}

//class Singleton {
//public:
//	static Singleton* GetInstance() {
//		return _spInst;
//	}
//	void Print() {
//		cout << _spInst << endl;
//	}
//private:
//	Singleton() {}
//	Singleton(const Singleton&) = delete; //防拷贝
//
//	int _a;
//	//static Singleton _sInst; //声明，否则构造私有取不到，声明的为类成员就能令定义时取到
//	static Singleton* _spInst; //声明
//};
//
////Singleton Singleton::_sInst; // 定义成全局的，而不是私有的，满足饿汉模式的要求（main函数之前就被初始化）
//Singleton* Singleton::_spInst = new Singleton; //定义
//
//int main() {
//	Singleton::GetInstance()->Print(); //只能这么取，因为不能实例化
//	return 0;
//}

int main() {
	char buff[128];
	while (scanf("%s", buff) != EOF) {
	}
}
