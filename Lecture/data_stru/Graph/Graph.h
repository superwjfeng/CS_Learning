#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <functional>
#include <limits>
#include <cassert>

#include "UnionFindSet.h"

using namespace std;

namespace matrix
{
	// Weight 可以是整数，也可以是浮点数
	template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph
	{
		typedef Graph<V, W, MAX_W, Direction> Self;
	public:
		//图的创建
		Graph() = default;

		Graph(const V* a, size_t n) //创建图要提供节点内容数组a*和节点数n
		{
			_vertices.reserve(n); //先开好n大小的内存
			for (size_t i = 0; i < n; i++)
			{
				_vertices.push_back(a[i]); //往_vertices里填充节点内容
				_indexMap[a[i]] = i; //填充_indexMap的映射关系
			}

			_matrix.resize(n);
			for (size_t i = 0; i < _matrix.size(); i++)
			{
				_matrix[i].resize(n, MAX_W); //nontype模板初始化
				for (size_t j = 0; j < _matrix[i].size(); j++)
				{
					//对角线上的权重初始化为0
					if (i == j) _matrix[i][j] = 0;
				}
			}
		}

		size_t GetVertexIndex(const V& v)
		{
			auto it = _indexMap.find(v);
			if (it != _indexMap.end())
			{
				return it->second;
			}
			else
			{
				assert(false);
				//throw invalid_argument("顶点不存在");
				return -1;
			}
		}

		//给的是vertex的下标，最小生成树用
		void _AddEdge(size_t srci, size_t dsti, const W& w)
		{
			_matrix[srci][dsti] = w;
			// 无向图要添加两个方向的权重
			if (Direction == false)
			{
				_matrix[dsti][srci] = w;
			}
		}

		//给的是vertex
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexIndex(src);
			size_t dsti = GetVertexIndex(dst);
			_matrix[srci][dsti] = w;
			// 无向图要添加两个方向的权重
			_AddEdge(srci, dsti, w); //复用
		}

		void Print()
		{
			cout << "<邻接矩阵结构>" << endl << endl;

			cout << "vertices: " << endl;
			for (size_t i = 0; i < _vertices.size(); i++)
			{
				cout << "[" << i << "]" << "->" << _vertices[i] << endl;
			}
			cout << endl;

			// matrix
			// 列号
			cout << "matrix: " << endl;
			cout << "  ";
			for (size_t i = 0; i < _vertices.size(); i++)
			{
				//cout << i << " ";
				printf("%4d", i);
			}
			cout << endl << endl;;
			for (size_t i = 0; i < _matrix.size(); i++)
			{
				// 行号
				cout << i << " ";
				for (size_t j = 0; j < _matrix[i].size(); j++)
				{
					//cout << _matrix[i][j] << " ";
					if (_matrix[i][j] == MAX_W)
					{
						//cout << "* ";
						printf("%4c", '*');
					}
					else
					{
						//cout << _matrix[i][j] << " ";
						printf("%4d", _matrix[i][j]);
					}
				}
				cout << endl;
			}
			cout << endl;

			cout << "Edge:" << endl;
			for (size_t i = 0; i < _matrix.size(); i++)
			{
				for (size_t j = 0; j < _matrix[i].size(); j++)
				{
					if (i < j && _matrix[i][j] != MAX_W)
					{
						cout << _vertices[i] << "->" << _vertices[j] << ": " << _matrix[i][j] << endl;
					}
				}
			}

			cout << endl;
		}

		void BFS(const V& src)
		{
			size_t srci = GetVertexIndex(src);
			queue<int> q;
			vector<bool> visited(_vertices.size(), false);

			q.push(srci);
			visited[srci] = true;
			int levelSize = 1; //控制一层一层出，层序遍历

			size_t n = _vertices.size();
			cout << "BFS process: " << endl;
			while (!q.empty())
			{
				//一层一层出
				for (int i = 0; i < levelSize; i++)
				{
					int front = q.front();
					q.pop();
					cout << front << ":" << _vertices[front] << " ";
					// 把front顶点的邻接顶点入队列
					for (size_t i = 0; i < n; i++)
					{
						if (_matrix[front][i] != MAX_W)
						{
							if (visited[i] == false)
							{
								q.push(i);
								visited[i] = true;
							}
						}
					}
				}
				cout << endl;
				levelSize = q.size();
			}
			cout << endl;
		}

		void _DFS(size_t srci, vector<bool>& visited)
		{
			cout << srci << ":" << _vertices[srci] << endl;
			visited[srci] = true;
			//找一个与scri相邻的且没有访问过的点，往深度遍历
			for (size_t i = 0; i < _vertices.size(); i++)
			{
				if (_matrix[srci][i] != MAX_W && visited[i] == false)
				{
					_DFS(i, visited);
				}
			}
		}

		void DFS(const V& src)
		{
			size_t srci = GetVertexIndex(src);
			vector<bool> visited(_vertices.size(), false);
			cout << "DFS process: " << endl;
			_DFS(srci, visited);
		}

		struct Edge
		{
			size_t _srci;
			size_t _dsti;
			W _w;
			
			Edge(size_t srci, size_t dsti, const W& w)
				:_srci(srci), _dsti(dsti), _w(w)
			{}

			//Edge是priority_queue的存储元素，要实现比较
			bool operator>(const Edge& e) const
			{
				return _w > e._w;
			}
		};

		W Kruskal(Self& minTree)
		{
			size_t n = _vertices.size();
			minTree._vertices = _vertices;
			minTree._indexMap = _indexMap;
			minTree._matrix.resize(n);
			//初始化
			for (size_t i = 0; i < n; i++)
			{
				minTree._matrix[i].resize(n, MAX_W);
			}

			priority_queue<Edge, vector<Edge>, greater<Edge>> minque;
			//建堆
			for (size_t i = 0; i < n; i++)
			{
				for (size_t j = 0; j < n; j++)
				{
					if (i < j && _matrix[i][j] != MAX_W) //避免无向图的重复：i < j
					{
						minque.push(Edge(i, j, _matrix[i][j]));
					}
				}
			}

			// 选出n-1条边
			int size = 0;
			W totalW = W();
			UnionFindSet ufs(n);
			while (!minque.empty())
			{
				Edge min = minque.top();
				minque.pop();

				if (!ufs.InSet(min._srci, min._dsti)) //不在一个集合内，可以添加这条边到MST里
				{
					cout << _vertices[min._srci] << "->" << _vertices[min._dsti]
						<< ":" << min._w << endl;
					minTree._AddEdge(min._srci, min._dsti, min._w);
					ufs.Union(min._srci, min._dsti);
					++size;
					totalW += min._w;
				}
				else
				{
					cout << "构成环：";
					cout << _vertices[min._srci] << "->" << _vertices[min._dsti]
						<< ":" << min._w << endl;
				}
			}
			cout << endl;

			if (size == n - 1) //给的是连通图
				return totalW;
			else
				return W(); //给的不是连通图，没有MST

		}

		W Prim(Self& minTree, const W& src)
		{
			size_t srci = GetVertexIndex(src);
			size_t n = _vertices.size();

			minTree._vertices = _vertices;
			minTree._indexMap = _indexMap;
			minTree._matrix.resize(n);
			//初始化
			for (size_t i = 0; i < n; i++)
			{
				minTree._matrix[i].resize(n, MAX_W);
			}

			//set<int> X; //visited
			//set<int> Y; //frontier
			//X.insert(srci);
			//for (size_t i = 0; i < n; i++)
			//{
			//	if (i != srci)
			//	{
			//		Y.insert(i);
			//	}
			//}

			vector<bool> X(n,false);
			vector<bool> Y(n,true);
			X[srci] = true;
			Y[srci] = false;

			X.resize(n);
			//从X->Y集合中选出最短的边
			//仍然采用优先级队列+探环的实现，否则效率很低
			priority_queue<Edge, vector<Edge>, greater<Edge>> minq; //greater 小数优先
			//先把srci连接的边添加到队列中
			for (size_t i = 0; i < n; ++i)
			{
				if (_matrix[srci][i] != MAX_W)
				{
					minq.push(Edge(srci, i, _matrix[srci][i]));
				}
			}

			cout << "Prim 开始选边" << endl;
			size_t size = 0;
			W totalW = W();
			while (!minq.empty())
			{
				Edge min = minq.top();
				minq.pop();

				if (X[min._dsti]) //最小边的目标点也在X集合，则构成环
				{
					cout << "构成环：";
					cout << _vertices[min._srci] << "->" << _vertices[min._dsti]
						<< ":" << min._w << endl;
				}
				else
				{
					minTree._AddEdge(min._srci, min._dsti, min._w);

					cout << _vertices[min._srci] << "->" << _vertices[min._dsti]
						<< ":" << min._w << endl;

					X[min._dsti] = true;
					Y[min._dsti] = false;
					++size;
					totalW += min._w;

					if (size == n - 1) break;

					for (size_t i = 0; i < n; ++i)
					{
						if (_matrix[min._dsti][i] != MAX_W && X[i] == 0) //i要不在X集合里，避免成环
						{
							minq.push(Edge(min._dsti, i, _matrix[min._dsti][i]));
						}
					}
				}
			}

			if (size == n - 1)
				return totalW;
			else
				return W();

		}

		void PrintShortPath(const V& src, const vector<W>& dist, const vector<int>& pPath)
		{
			size_t srci = GetVertexIndex(src);
			size_t n = _vertices.size();
			for (size_t i = 0; i < n; i++)
			{
				if (i != srci)
				{
					// 找出i顶点的路径
					vector<int> path;
					size_t parenti = i;
					while (parenti != srci)
					{
						path.push_back(parenti);
						parenti = pPath[parenti];
					}
					path.push_back(srci);

					reverse(path.begin(), path.end());

					for (auto i : path)
						cout << _vertices[i] << "->";
					cout << dist[i] << endl;
				}
			}
		}

		//顶点个数是N -> O(N^2)，空间复杂度 O(N`)
		void Dijkstra(const V& src, vector<W>& dist, vector<int>& pPath)
		{
			size_t srci = GetVertexIndex(src);
			size_t n = _vertices.size();
			dist.resize(n, MAX_W); //将dist里的所有值先初始化为MAX_W
			pPath.resize(n, -1); //将pPath里的所有值先初始化为MAX_W
			
			//srci节点初始化
			dist[srci] = W(); //记录srci到其余节点的最短距离
			pPath[srci] = srci; //记录当前节点的父节点下标

			//不能直接修改优先级队列中的某一个元素，所以不能直接采用优先级队列

			//S用来标记已经确定最短路径的顶点集合
			vector<bool> visited(n, false); //S改成visited
			for (size_t i = 0; i < n; i++)
			{
				//选出本轮最短路径顶点curr更新其他路径
				int curr = 0; //本次循环选出的有最小距离的结点，相当于priority_queue每次的队头
				W min = MAX_W; //保存最小权值
				for (size_t j = 0; j < n; j++) //最多把所有n个结点都遍历一遍
				{
					if (visited[j] == false && dist[j] < min)
					{
						curr = j;
						min = dist[j];
					}
				}
				visited[curr] = true;

				//松弛更新curr连接的顶点j _matrix[curr][j] + dist[curr] < dist[j]
				for (size_t j = 0; j < n; j++)
				{
					if (visited[j] == false && //第一个条件防止成环
						_matrix[curr][j] != MAX_W && 
						dist[curr] + _matrix[curr][j] < dist[j])
					{
						dist[j] = dist[curr] + _matrix[curr][j];
						pPath[j] = curr; //谁更新存谁
					}
				}
			}
		}
		
		bool BellmanFord(const V& src, vector<W>& dist, vector<int>& pPath)
		{
			size_t n = _vertices.size();
			size_t srci = GetVertexIndex(src);
			dist.resize(n, MAX_W); //将dist里的所有值先初始化为MAX_W
			pPath.resize(n, -1); //将pPath里的所有值先初始化为MAX_W
			dist[srci] = W();

			cout << "更新边：" << endl;

			for (size_t i = 0; i < n; i++)
			{
				bool update = false;
				printf("更新第%d轮：\n", i);
				for (size_t j = 0; j < n; j++)
				{
					for (size_t k = 0; k < n; k++)
					{
						if (_matrix[j][k] != MAX_W && dist[j] + _matrix[j][k] < dist[k])
						{
							update = true;
							cout << _vertices[j] << "->" << _vertices[k]
								<< ":" << _matrix[j][k] << endl;
							dist[k] = dist[j] + _matrix[j][k];
							pPath[k] = j;
						}
					}
				}

				//如果这个轮次中没有更新出最短路径，那么后续轮次就不需要再走了
				if (update == false) break;

				//如果还能更新就是带负权回路
				for (size_t j = 0; j < n; j++)
				{
					for (size_t k = 0; k < n; k++)
					{
						if (_matrix[i][j] != MAX_W && dist[i] + _matrix[i][j] < dist[j])
							return false;
					}
				}
			}

			return true;
		}

	private:
		vector<V> _vertices;           //顶点集合
		map<V, int> _indexMap;         //顶点映射下标，因为顶点可能是V=char这种类型的
		vector<vector<W>> _matrix;     //邻接矩阵
	};

	void TestGraph1()
	{
		Graph<char, int, INT_MAX, true> g("0123", 4);
		g.AddEdge('0', '1', 1);
		g.AddEdge('0', '3', 4);
		g.AddEdge('1', '3', 2);
		g.AddEdge('1', '2', 9);
		g.AddEdge('2', '3', 8);
		g.AddEdge('2', '1', 5);
		g.AddEdge('2', '0', 3);
		g.AddEdge('3', '2', 6);
		g.Print();
	}

	void TestBDFS()
	{
		string a[] = { "张三", "李四", "王五", "赵六", "周七" };
		Graph<string, int> g1(a, sizeof(a) / sizeof(string));
		g1.AddEdge("张三", "李四", 100);
		g1.AddEdge("张三", "王五", 200);
		g1.AddEdge("王五", "赵六", 30);
		g1.AddEdge("王五", "周七", 30);
		g1.Print();
		g1.BFS("张三");
		g1.DFS("张三");
	}

	void TestKruskal()
	{
		const char* str = "abcdefghi";
		Graph<char, int> g(str, strlen(str));
		g.AddEdge('a', 'b', 4);
		g.AddEdge('a', 'h', 8);
		//g.AddEdge('a', 'h', 9);
		g.AddEdge('b', 'c', 8);
		g.AddEdge('b', 'h', 11);
		g.AddEdge('c', 'i', 2);
		g.AddEdge('c', 'f', 4);
		g.AddEdge('c', 'd', 7);
		g.AddEdge('d', 'f', 14);
		g.AddEdge('d', 'e', 9);
		g.AddEdge('e', 'f', 10);
		g.AddEdge('f', 'g', 2);
		g.AddEdge('g', 'h', 1);
		g.AddEdge('g', 'i', 6);
		g.AddEdge('h', 'i', 7);
		
		//Kruskal
		Graph<char, int> kminTree; //初始化最小生成树
		cout << "Kruskal total W: " << g.Kruskal(kminTree) << endl << endl;
		cout << "MST: ";
		kminTree.Print();

		cout << "------------------------------------------------" << endl;



		//for (size_t i = 0; i < strlen(str); ++i)
		//{
		//	cout << "Prim:" << g.Prim(pminTree, str[i]) << endl;
		//}
	}

	void TestPrim()
	{
		const char* str = "abcdefghi";
		Graph<char, int> g(str, strlen(str));
		g.AddEdge('a', 'b', 4);
		g.AddEdge('a', 'h', 8);
		//g.AddEdge('a', 'h', 9);
		g.AddEdge('b', 'c', 8);
		g.AddEdge('b', 'h', 11);
		g.AddEdge('c', 'i', 2);
		g.AddEdge('c', 'f', 4);
		g.AddEdge('c', 'd', 7);
		g.AddEdge('d', 'f', 14);
		g.AddEdge('d', 'e', 9);
		g.AddEdge('e', 'f', 10);
		g.AddEdge('f', 'g', 2);
		g.AddEdge('g', 'h', 1);
		g.AddEdge('g', 'i', 6);
		g.AddEdge('h', 'i', 7);

		// Prim
		Graph<char, int> pminTree;
		cout << "Prim total W: " << g.Prim(pminTree, 'a') << endl << endl;
		cout << "MST: ";
		pminTree.Print();
	}

	void TestGraphDijkstra()
	{
		const char* str = "syztx";
		Graph<char, int, INT_MAX, true> g(str, strlen(str));
		g.AddEdge('s', 't', 10);
		g.AddEdge('s', 'y', 5);
		g.AddEdge('y', 't', 3);
		g.AddEdge('y', 'x', 9);
		g.AddEdge('y', 'z', 2);
		g.AddEdge('z', 's', 7);
		g.AddEdge('z', 'x', 6);
		g.AddEdge('t', 'y', 2);
		g.AddEdge('t', 'x', 1);
		g.AddEdge('x', 'z', 4);

		vector<int> dist;
		vector<int> parentPath;
		g.Dijkstra('s', dist, parentPath);
		g.PrintShortPath('s', dist, parentPath);
		// 图中带有负权路径时，贪心策略则失效了。
		// 测试结果可以看到s->t->y之间的最短路径没更新出来
		/*g.AddEdge('s', 't', 10);
		g.AddEdge('s', 'y', 5);
		g.AddEdge('t', 'y', -7);
		g.AddEdge('y', 'x', 3);
		vector<int> dist;
		vector<int> parentPath;
		g.Dijkstra('s', dist, parentPath);
		g.PrinrtShotPath('s', dist, parentPath);*/
	}

	void TestGraphBellmannFord()
	{
		const char* str = "syztx";
		Graph<char, int, INT_MAX, true> g(str, strlen(str));
		g.AddEdge('s', 't', 6);
		g.AddEdge('s', 'y', 7);
		g.AddEdge('y', 'z', 9);
		g.AddEdge('y', 'x', -3);
		g.AddEdge('z', 's', 2);
		g.AddEdge('z', 'x', 7);
		g.AddEdge('t', 'x', 5);
		g.AddEdge('t', 'y', 8);
		g.AddEdge('t', 'z', -4);
		g.AddEdge('x', 't', -2);

		vector<int> dist;
		vector<int> parentPath;
		g.BellmanFord('s', dist, parentPath);
		cout << endl;
		g.PrintShortPath('s', dist, parentPath);
	}
}



namespace link_table
{
	template<class W>
	struct Edge
	{
		//int _srci;
		//一般来说只考虑出度就可以了，入度不太用得着，因为自己的入度就是别人的出度
		int _dsti; //目标点的下标
		W _w; //权值
		Edge<W>* _next;

		Edge(int dsti, const W& w)
			:_dsti(dsti), _w(w), _next(nullptr)
		{}
	};

	// Weight 可以是整数，也可以是浮点数
	template<class V, class W, bool Direction = false>
	class Graph
	{
		typedef Edge<W> Edge;
	public:
		//图的创建
		Graph(const V* a, size_t n)
		{
			_vertices.reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				_vertices.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			_tables.resize(n, nullptr);

		}

		size_t GetVertexIndex(const V& v)
		{
			auto it = _indexMap.find(v);
			if (it != _indexMap.end())
			{
				return it->second;
			}
			else
			{
				assert(false);
				//throw invalid_argument("顶点不存在");
				return -1;
			}
		}

		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexIndex(src);
			size_t dsti = GetVertexIndex(dst);

			Edge* eg = new Edge(dsti, w);
			//头插
			eg->_next = _tables[srci];
			_tables[srci] = eg; //eg变成链上的第一个元素 
			//有向图结束

			//无向图
			if (Direction == false)
			{
				Edge* eg = new Edge(srci, w);
				eg->_next = _tables[dsti];
				_tables[dsti] = eg;
			}

		}

		void Print()
		{
			cout << "<邻接表结构>" << endl << endl;

			//vertices
			cout << "vertices: " << endl;
			for (size_t i = 0; i < _vertices.size(); i++)
			{
				cout << "[" << i << "]" << "->" << _vertices[i] << endl;
			}
			cout << endl;

			cout << "table: " << endl;
			for (size_t i = 0; i < _tables.size(); i++)
			{
				cout << _vertices[i] << "[" << i << "]->";
				Edge* curr = _tables[i];
				while (curr)
				{
					cout << "[" << _vertices[curr->_dsti] << "[" << curr->_dsti << "]->"
						<< curr->_w << "]->";
					curr = curr->_next;
				}
				cout << "nullptr" << endl;
			}
		}
	private:
		vector<V> _vertices;           //顶点集合
		map<V, int> _indexMap;         //顶点映射下标，因为顶点可能是V=char这种类型的
		vector<Edge*> _tables;         //邻接表
	};


	void TestGraph1()
	{
		string a[] = { "张三", "李四", "王五", "赵六", "周七" };
		Graph<string, int> g1(a, sizeof(a) / sizeof(string));
		g1.AddEdge("张三", "李四", 100);
		g1.AddEdge("张三", "王五", 200);
		g1.AddEdge("王五", "赵六", 30);
		g1.AddEdge("王五", "周七", 30);
		g1.Print();
	}
}
