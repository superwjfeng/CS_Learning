#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

enum Colour
{
	RED,
	BLACK
};

template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	T _data;
	Colour _col;

	RBTreeNode(const T& data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
	{}
};

template<class T, class Ref, class Ptr>
struct __RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef __RBTreeIterator<T, Ref, Ptr> Self;
	Node* _node; // 唯一的类成员
	
	__RBTreeIterator(Node* node)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}

	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}

	Self& operator++() // 前置
	{
		if (_node->_right)
		{  // 右子树不为空就去找右子树的最左节点
			Node* left = _node->_right;
			while (left->_left)
				left = left->_left;
			_node = left;
		}
		else // 右子树为空就去找祖先里面当前孩子分支不是祖先的右的祖先
		{
			Node* parent = _node->_parent;
			Node* curr = _node;
			while (parent && curr == parent->_right) // parent为空就说明走完了
			{
				curr = curr->_parent;
				parent = curr->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Self& operator--() // 前置
	{
		if (_node->_left)
		{
			Node* right = _node->_left;
			while (right->_right)
				right = right->_right;
			_node = right;
		}
		else
		{
			Node* parent = _node->_parent;
			Node* curr = _node;
			while (parent && curr == parent->_left)
			{
				curr = curr->_parent;
				parent = curr->_parent;
			}
			_node = parent;
		}

		return *this;
	}

};

template<class K, class T, class KeyOfT>
struct RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef __RBTreeIterator<T, T&, T*> iterator;
	
	iterator begin()
	{
		Node* left = _root;
		while (left && left->_left)
		{
			left = left->_left;
		}

		return iterator(left);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	pair<iterator, bool> Insert(const T& data)
	{
		KeyOfT kot; //定义仿函数对象
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(iterator(_root), true);
		}
		Node* parent = nullptr;
		Node* curr = _root;
		while (curr) // 找插入点
		{
			if (kot(curr->_data) < kot(data)) // 要插入的pair比curr大就往右走
			{
				parent = curr;
				curr = curr->_right;
			}
			else if (kot(curr->_data) > kot(data))
			{
				parent = curr;
				curr = curr->_left;
			}
			else
				return make_pair(iterator(curr), false);
		}
		// 插入后连接指针关系
		curr = new Node(data);
		Node* newnode = curr;
		curr->_col = RED; // 插入红色最多只影响局部，插入黑色影响整棵树
		if (kot(parent->_data) < kot(data))
			parent->_right = curr;
		else
			parent->_left = curr;
		curr->_parent = parent; //三叉链

		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			assert(grandfather);
			assert(grandfather->_col == BLACK); // 祖父一定为黑
			// 关键看uncle
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				// 情况一，第一种情况不关心方向，变色+继续往上处理
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					// 继续往上处理
					curr = grandfather;
					parent = curr->_parent;
				}
				// 情况二+情况三：uncle不存在 + 存在且为黑
				else
				{
					// 情况二：右单旋+变色
					//       g
					//     p   u
					// curr
					if (curr == parent->_left)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						// 情况三：左右 左单旋 + 右单旋 + 变色
						//         g
						//     p      u
						//       curr
						RotateL(parent);
						RotateR(grandfather);
						curr->_col = BLACK;
						grandfather->_col = RED;
					}
					break; // 旋转完了之后不会影响树的其他部分，肯定处理完了
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				//  情况一，第一种情况不关心方向
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					// 继续网上处理
					curr = grandfather;
					parent = curr->_parent;
				}
				else
				{
					// 情况二：左单旋+变色
					//       g
					//     u   p
					//           curr
					if (curr == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						// 情况三：右左 右单旋 + 左单旋 + 变色
						//         g
						//      u      p
						//          curr
						RotateR(parent);
						RotateL(grandfather);
						curr->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK; //根节点是黑色的
		return make_pair(iterator(newnode), true);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBalance() // 检查是否满足红黑树的规则
	{
		if (_root == nullptr)
			return true;
		if (_root->_col == RED)
		{
			cout << "Root is not black" << endl;
			return false;
		}
		int benchmark = 0;
		Node* curr = _root;
		while (curr)
		{
			if (curr->_col == BLACK)
				benchmark++;
			curr = curr->_left;
		}

		return PrevCheck(_root, 0, benchmark); // 检查每条路径黑色节点的数量是否相同
	}

private:
	bool PrevCheck(Node* root,int blackNum, int benchmark)
	{
		if (root == nullptr)
		{
			//cout << blackNum << endl;
			//return;
			if (blackNum != benchmark)
			{
				cout << "Black num is not equal" << endl;
				return false;
			}
			else
				return true;
		}
		if (root->_col == BLACK)
			blackNum++;
		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "存在连续的红色节点" << endl;
			return false;
		}
		return PrevCheck(root->_left, blackNum, benchmark)
			&& PrevCheck(root->_right, blackNum, benchmark);
	}

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
	}

	void RotateLR(Node* parent) //先左旋再右旋，即左右双旋
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf; //单旋会修改平衡因子，先记录一下
		RotateL(subL); //以subL为核心进行左旋
		RotateR(parent); //以parent为核心进行右旋
	}

	void RotateRL(Node* parent) //先右旋再左旋，即右左双旋
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf; //单旋会修改平衡因子，先记录一下
		RotateR(subR); //以subR为核心进行右旋
		RotateL(parent); //以parent为核心进行左旋
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
private:
	Node* _root = nullptr;
};

//void TestRBTree1()
//{
//	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
//	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 }; //测试双旋平衡因子
//	RBTree<int, int> t1;
//	for (auto e : a)
//		t1.Insert(make_pair(e, e));
//	t1.InOrder();
//	cout << "IsBalance:" << t1.IsBalance() << endl;
//}
