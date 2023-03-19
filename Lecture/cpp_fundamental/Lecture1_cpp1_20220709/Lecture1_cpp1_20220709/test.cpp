////兼容C语言
//#include <stdio.h>
//
//int main()
//{
//	printf("hello world\n");
//}

//#include <iostream>
//using namespace std;
//int main()
//{
//	cout << "hello world" << endl;
//}

//// 命名空间的意义
//#include <stdio.h>
//#include <stdlib.h>
////int rand = 0; //与stdlib库中的rand冲突了
//
//namespace bit
//{
//	int rand = 0;
//}
//
//int main()
//{
//	printf("%p\n", rand);
//	printf("%d\n", bit::rand);
//	return 0;
//}


//#include <stdio.h>
//int a = 0;
//
//// 命名空间可以嵌套
//namespace sql
//{
//	int rand = 0;
//	namespace test
//	{
//		int rand = 0;
//		void func()
//		{
//			printf("func()\n");
//		}
//
//		struct TreeNode
//		{
//			struct TreeNode* left;
//			struct TreeNode* right;
//			int val;
//		};
//	}
//}
//
//// using namespace test; //直接使用test命名空间，不需要指定test::
//// 先在全局域去找，如果没有还会到展开的test域中去找
//
//// using namespace std; std是c++标准库的命名空间
//int main()
//{
//	int a = 1;
//	printf("%d\n", a);
//	// ::域作用限定符，去:左边的域找，当左边为空时，就是去全局域找
//	printf("%d\n", ::a);
//
//	sql::test::func();
//	struct sql::test::TreeNode;
//}

#include <iostream>

// using namespace std; // 这样写不太好，因为会把std库中的内容展开出来了，可能会有冲突

// 可以选择只展开部分常用的类或函数

using std::cout;
using std::cin;
using std::endl;

int main()
{
	// << 是流插入运算符
	cout << "hello world" << endl;
	cout << "hello world" << "\n";

	int i = 11;
	double d = 11.11;
	printf("%d, %f\n", i, d);

	// 自动识别类型
	cin >> i >> d; // >> 流提取 
	cout << i << "," << d << endl;
	return 0;
}