#pragma once

//数据是存在磁盘，K是磁盘地址
template<class K, size_t M>
struct BTreeNode
{
	K _keys[M]; //最多M-1个关键字/磁盘地址，为了方便插入以后再分裂，多给一个空间
	BTreeNode<K, M>* _subs[M + 1]; // 最多M个孩子，为了方便插入以后再分裂，多给一个空间
	BTreeNode<K, M>* _parent;
	size_t _n; //记录实际存储多少个关键字

	BTreeNode()
	{
		for (size_t i = 0; i < M; i++)
		{
			_keys[i] = K();
			_subs[i] = nullptr;
		}
		_subs[M] = nullptr; //少初始化了一个
		_parent = nullptr;
		_n = 0;
	}
};

template<class K, size_t M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	pair<Node*, int> Find(const K& key) //返回节点地址和它在当前层的序号i
	{
		Node* parent = nullptr; //记录一下父亲，方便插入节点
		Node* curr = _root;
		while (curr)
		{
			// 在一个节点中查找
			size_t i = 0;
			while (i < curr->_n)
			{
				if (key < curr->_keys[i])
				{
					break;
				}
				else if (key > curr->_keys[i])
				{
					++i;
				}
				else // 相等，找到了。找到的不一定是在叶子，找不到才会一路跳到叶子
				{
					return make_pair(curr, i);
				}
			}
			// 有两种可能性会走到这里
			// 1. curr在当前层的中间位置，判断key < curr->_keys[i]成功后break
			// 2. curr走到当前层的最后，i = curr->_n
			// 但两种情况都是在_keys[i]的左孩子，左孩子跟他下标相等，往孩子去跳
			parent = curr;
			curr = curr->_subs[i];
		}

		//不这么写的原因是因为要方便叶子节点的插入
		//return make_pair(nullptr, -1);
		
		return make_pair(parent, -1); //没有找到的话那就是到了叶子，返回它的父亲parent
		//因为下标不可能是小于0的，所以序号为-1就是叶子
		
		
	}

	void InsertKey(Node* node, const K& key, Node* child)
	{
		int end = node->_n - 1;
		while (end >= 0)
		{
			if (key < node->_keys[end]) //key比end小，就要往后挪
			{
				//既要挪动父节点中的key，也要挪动父节点的孩子指针，否则分割关系就错了
				node->_keys[end + 1] = node->_keys[end];
				node->_subs[end + 2] = node->_subs[end + 1];

				--end;
			}
			else
			{
				break;
			}
		}
		node->_keys[end + 1] = key;
		node->_subs[end + 2] = child;
		if (child)
		{
			child->_parent = node; //父亲要指向新分裂的兄弟
		}
		node->_n++;
	}

	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_n++;
			return true;
		}

		//这里假设没有冗余（实际上也是合理的，因为硬盘的物理地址是唯一的）：
		//若key已经存在（Find不返回nullptr），就不允许插入了
		pair<Node*, int> ret = Find(key);
		if (ret.second >= 0)
		{
			return false;
		}

		//如果没有找到，find顺便带回了要插入的叶子节点
		//循环每次往parent插入newKey和child
		Node* parent = ret.first;
		K newKey = key; //不能用key的原因是因为key是一个const引用参数，不能修改它
		Node* child = nullptr;

		while (1)
		{
			InsertKey(parent, newKey, child);

			//插入之后要检查n是否超过上限，满了就要分裂，没有满的话插入就结束
			if (parent->_n < M) //关键字K的数量最多为M-1
			{
				return true;
			}
			else //满了进行分裂
			{
				size_t mid = M / 2;
				//分裂一半[mid+1, M-1]给兄弟[0, mid-1]
				Node* brother = new Node;
				size_t j = 0;
				size_t i = mid + 1;
				for (; i <= M - 1; i++)
				{
					//要拷贝key和key的左孩子subs[j]
					brother->_keys[j] = parent->_keys[i];
					brother->_subs[j] = parent->_subs[i];

					if (parent->_subs[i]) //如果孩子的父亲不是空，就也要更新一下
					{
						parent->_subs[i]->_parent = brother;
					}
					++j;

					//清理一下原来的内容，方便观察。其实不清理也行，后面会覆盖的
					parent->_keys[i] = K();
					parent->_subs[i] = nullptr;
				}
				//还有最后一个右孩子没有拷贝
				brother->_subs[j] = parent->_subs[i];
				if (parent->_subs[i])
				{
					parent->_subs[i]->_parent = brother;
				}

				brother->_n = j;
				parent->_n -= (brother->_n + 1); //还有一个要给父亲


				K midKey = parent->_keys[mid];
				parent->_keys[mid] = K(); //清理一下方便观察

				//连接父亲与兄弟，转换为往parent的父亲插入节点parent->mid和孩子

				//刚刚分裂的本来就是根节点，要产生一个新的根
				if (parent->_parent == nullptr)
				{
					_root = new Node;
					_root->_keys[0] = midKey;
					_root->_subs[0] = parent;
					_root->_subs[1] = brother;
					_root->_n = 1;

					parent->_parent = _root; //和新的根连接起来
					brother->_parent = _root; //和新的根连接起来
					break;
				}
				else //不为空就往父亲中插入
				{
					newKey = midKey;
					child = brother;
					parent = parent->_parent;
				}
			}
		}
		return true;
	}

	void _InOrder(Node* curr)
	{
		if (curr == nullptr)
			return;

		// 左 根 左 根 ... 右
		size_t i = 0;
		for (; i < curr->_n; i++)
		{
			_InOrder(curr->_subs[i]); //左子树
			cout << curr->_keys[i] << " "; //根
		}

		_InOrder(curr->_subs[i]); //最后的那个右子树

	}

	void InOrder() //中序遍历
	{
		_InOrder(_root);
	}

private:
	Node* _root = nullptr;
};

void TestBtree()
{
	//int a[] = { 53, 139, 75, 49, 145, 36, 50, 47, 101 };
	int a[] = { 53, 139, 75, 49, 145, 36, 101 };
	BTree<int, 3> t;
	for (auto e : a)
	{
		t.Insert(e);
	}

	t.InOrder();
}
