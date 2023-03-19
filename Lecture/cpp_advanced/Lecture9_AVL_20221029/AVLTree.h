#pragma once

#include <iostream>
#include <assert.h>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent; // 三叉链，更方便找祖先

	pair<K, V> _kv;
	int _bf; // 平衡因子

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}
};

template<class K, class V>
struct AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* curr = _root;
		while (curr) // 找插入点
		{
			if (curr->_kv.first < kv.first) // 要插入的pair比curr大就往右走
			{
				parent = curr;
				curr = curr->_right;
			}
			else if (curr->_kv.first > kv.first)
			{
				parent = curr;
				curr = curr->_left;
			}
			else
				return false;
		}
		// 插入后连接指针关系
		curr = new Node(kv);
		if (parent->_kv.first < kv.first)
			parent->_right = curr;
		else
			parent->_left = curr;
		curr->_parent = parent; //三叉链

		// 控制平衡
		// 1. 更新平衡因子
		while (parent) // 可能要更新到根节点，最差情况为高度次更新+一次旋转
		{
			if (curr == parent->_right)
				parent->_bf++;
			else
				parent->_bf--;

			if (parent->_bf == 0) //parent所在子树没有发生高度变化，不需要继续向上更新
				break;
			else if (abs(parent->_bf) == 1) //parent所在分支发生了高度变化，需要继续向上更新
			{
				parent = parent->_parent;
				curr = curr->_parent;
			}
			else if (abs(parent->_bf) == 2) //超过了高度差临界值，需要对parent所在子树做旋转处理
			{// 2. 旋转
				if (parent->_bf == 2 && curr->_bf == 1) // 因为两个_bf>0，所以可以判断是右边高 -- 右右左旋
					RotateL(parent); // 左旋
				else if (parent->_bf == -2 && curr->_bf == -1) // 左左右旋
					RotateR(parent);
				else if (parent->_bf == -2 && curr->_bf == 1) // 左右双旋
					RotateLR(parent);
				else if (parent->_bf == 2 && curr->_bf == -1) // 右左双旋
					RotateRL(parent);
				else
					assert(false);
				break; // 若进行旋转，只要进行一次旋转肯定就更新完毕了，不用继续往上走
			}
			else
				assert(false);
		}
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		return _IsBalance(_root); //要递归走，判断每一棵子树都是AVL树
	}

private: // 旋转是私有属性，因为不能主动调用
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		// 需要改动6个指针的指向
		parent->_right = subRL;
		if (subRL) //subRL的高度为0时为空节点
			subRL->_parent = parent;

		Node* ppNode = parent->_parent; //记录parent的parent

		subR->_left = parent;
		parent->_parent = subR;
		// 旋转前的parent既可能是整棵树的root，也有可能是子树的root
		if (_root == parent) //parent是整棵树的root
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else //parent是子树的root
		{
			if (ppNode->_left == parent) //不知道parent是ppNode的左子树还是右子树
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
		subR->_bf = parent->_bf = 0; // 平衡因子都变成0
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		
		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
		subL->_bf = parent->_bf = 0;
	}

	void RotateLR(Node* parent) //先左旋再右旋，即左右双旋
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf; //单旋会修改平衡因子，先记录一下
		RotateL(subL); //以subL为核心进行左旋
		RotateR(parent); //以parent为核心进行右旋
		// 针对3钟情况分别处理平衡因子的更新
		subLR->_bf = 0;
		if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
		}
		else if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = 0;
		}
		else
			assert(false);
	}

	void RotateRL(Node* parent) //先右旋再左旋，即右左双旋
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf; //单旋会修改平衡因子，先记录一下
		RotateR(subR); //以subR为核心进行右旋
		RotateL(parent); //以parent为核心进行左旋
		// 针对3钟情况分别处理平衡因子的更新
		subRL->_bf = 0;
		if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
		}
		else if (bf == 0)
		{
			parent->_bf = 0;
			subR->_bf = 0;
		}
		else
			assert(false);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	
	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int leftHt = Height(root->_left);
		int rightHt = Height(root->_right);

		return max(leftHt, rightHt) + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;
		int leftHT = Height(root->_left);
		int rightHT = Height(root->_right);
		
		int diff = rightHT - leftHT;
		if (diff != root->_bf)
		{
			cout << root->_kv.first << "Wrong BF" << endl;
			return false;
		}
		return abs(diff) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right); // 递归判断子树是否平衡
	}

private:
	Node* _root = nullptr;
};

void TestAVLTree1()
{
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 }; //测试双旋平衡因子
	AVLTree<int, int> t1;
	for (auto e : a)
		t1.Insert(make_pair(e, e));
	t1.InOrder();
	cout << t1.IsBalance() << endl;
}

void TestAVLTree2()
{
	size_t N = 10000;
	srand(time(0));
	AVLTree<int, int> t1;
	for (size_t i = 0; i < N; i++)
	{
		int x = rand();
		t1.Insert(make_pair(x, i));
	}
	cout << "IsBalance:" << t1.IsBalance() << endl;
}
