#pragma once

#pragma once
#include <vector>
#include <map>

//template<class T>
//class UnionFindSet
//{
//public:
//	UnionFindSet(const T* a, size_t n)
//	{
//		for (size_t i = 0; i < n; i++)
//		{
//			_a.push_back(a[i]);
//			_indexMap[a[i]] = i;
//		}
//
//	}
//private:
//	vector<T> _a;          //编号找人
//	map<T, int> _indexMap; //人找编号
//	
//};

class UnionFindSet
{
public:
	UnionFindSet(size_t n)
		:_ufs(n, -1)
	{}

	void Union(int x1, int x2) //归并
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if (root1 == root2) //已经在一个集合里了，没必要归并
			return;
		
		//数据量小的往数量大的集合合并，默认root1大
		if (abs(_ufs[root1]) < abs(_ufs[root2]))
			std::swap(root1, root2);

		_ufs[root1] += _ufs[root2];
		_ufs[root2] = root1; //root2变成了root1的子集
	}

	int FindRoot(int x)
	{
		int root = x;
		while (_ufs[root] >= 0)
		{
			root = _ufs[root];
		}

		//路径压缩
		while (_ufs[x] >= 0)
		{
			int parent = _ufs[x];
			_ufs[x] = root;

			x = parent; //沿着路径往上
		}

		return root;
	}

	bool InSet(int x1, int x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	}

	size_t SetSize()
	{
		size_t size = 0;
		for (size_t i = 0; i < _ufs.size(); i++)
		{
			if (_ufs[i] < 0)
				size++;
		}
		return size;
	}

private:
	std::vector<int> _ufs;
};

