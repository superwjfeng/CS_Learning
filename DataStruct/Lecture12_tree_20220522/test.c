#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Queue.h"

typedef int BTDataType;
typedef struct BinaryTreeNode
{
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
	BTDataType data;
}BTNode;

BTNode* BuyNode(BTDataType x)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode*));
	assert(node);
	node->data = x;
	node->left = node->right = NULL;
	return node;
}

BTNode* CreatBinaryTree()
{
	BTNode* node1 = BuyNode(1);
	BTNode* node2 = BuyNode(2);
	BTNode* node3 = BuyNode(3);
	BTNode* node4 = BuyNode(4);
	BTNode* node5 = BuyNode(5);
	BTNode* node6 = BuyNode(6);
//	BTNode* node7 = BuyNode(7);

	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;
//	node3->right = node7;
	return node1;
}

void PreOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("# ");
		return;
	}

	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}

void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("# ");
		return;
	}

	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);
}

void PostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("# ");
		return;
	}

	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
}

int count = 0;
int TreeSize1(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	++count;
	TreeSize1(root->left);
	TreeSize1(root->right);
}

int TreeSize2(BTNode* root) //分治思想
{
	return root == NULL ? 0 :
		TreeSize2(root->left) + TreeSize2(root->right) + 1;
}

int count_leaf = 0;
int TreeLeafSize1(BTNode* root)
{
	if (root == NULL)
		return;
	if (root->left == NULL && root->right == NULL)
		++count_leaf;

	TreeLeafSize1(root->left);
	TreeLeafSize1(root->right);
}

int TreeLeafSize2(BTNode* root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;

	return  TreeLeafSize2(root->left) + TreeLeafSize2(root->right);
}

// 转换成子问题：求左子树的第K-1层+求右子树的第K-1层
int TreeKLevel(BTNode* root, int k)
{
	assert(k >= 1);
	if (root == NULL)
		return 0;

	if (k == 1)
		return 1;

	return TreeKLevel(root->left, k - 1) + TreeKLevel(root->right, k - 1); //如果用k--在右侧递归时k已经改变了，发生错误
}

// 二叉树查找值为x的结点
BTNode* TreeFind(BTNode* root, BTDataType x)
{
	if (root == NULL)
		return NULL;
	if (root->data = x)
		return root;
	
	BTNode* ret1 = TreeFind(root->left, x); //前序遍历是最优的
	if (ret1)
		return ret1;

	//如果放在这里就是中序，但这样效率可能没前序高
	//if (root->data = x)
	//	return root;
	
	BTNode* ret2 = TreeFind(root->right, x);
	if (ret2)
		return ret2;
	return NULL;
}

int TreeDepth(BTNode* root)
{
	if (root == NULL)
		return 0;

	int leftDepth = TreeDepth(root->left) + 1;
	int rightDepth = TreeDepth(root->right) + 1;
	return leftDepth > rightDepth ? leftDepth : rightDepth;
}

void TreeDestroy(BTNode* root)
{
	if (root == NULL)
		return;
	//后序销毁 
	TreeDestroy(root->left);
	TreeDestroy(root->right);
	free(root);
 }

void LevelOrder(BTNode* root) //层序遍历，借助队列实现
{
	Queue q;
	QueueInit(&q);
	if (root)
	{
		QueuePush(&q, root);
	}
	while(!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		printf("%d ", front->data);
		QueuePop(&q);
		if (front->left)
		{
			QueuePush(&q, front->left);
		}
		if (front->right)
		{
			QueuePush(&q, front->right);
		}
	}
	printf("\n");
	QueueDestroy(&q);
}

////判断是否是完全二叉树
//int BinaryTreeComplete(BTNode* root)
//{
//
//}

int main()
{
	BTNode* root = CreatBinaryTree();
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
	printf("\n");

	count = 0; //保险起见每次调用TreeSize之前count置0一下
	TreeSize1(root);
	printf("Tree size:%d\n", count); 
	
	printf("Tree size:%d\n", TreeSize2(root));

	count_leaf = 0; //保险起见每次调用TreeSize之前count置0一下
	TreeLeafSize1(root);
	printf("Tree leaf size:%d\n", count_leaf);
	
	printf("Tree leaf size:%d\n", TreeLeafSize2(root));
	printf("Tree leaf size in 2 level: %d\n", TreeKLevel(root, 2));
	printf("Tree leaf size in 3 level: %d\n", TreeKLevel(root, 3));
	printf("Tree leaf size in 4 level: %d\n", TreeKLevel(root, 4));
	printf("%p\n", TreeFind(root, 5));
	printf("Tree depth is: %d\n", TreeDepth(root));

	LevelOrder(root);
	//TreeDestroy(root);
	root = NULL;
	return 0; 
}