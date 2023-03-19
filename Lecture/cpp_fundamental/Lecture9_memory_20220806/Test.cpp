#include <iostream>;

using namespace std;

void Test1()
{
	// cpp支持C中的内存函数
	int* p1 = (int*)malloc(sizeof(int));
	free(p1);
	int* p2 = (int*)calloc(4, sizeof(int));
	int* p3 = (int*)realloc(p2, sizeof(int) * 10);
}

void Test2()
{
	int* p1 = (int*)malloc(sizeof(int));
	int* p2 = new int; // 申请1个int数据，不会初始化
	int* p3 = new int[5]; // 申请开5个int类型数据的数据
	int* p4 = new int(5); // 申请1个int对象，初始化为5
	//Cpp11 开始支持new数组初始化
	int* p5 = new int[5]{ 1,2,3 }; // 申请开5个int类型数据的数据

	free(p1);
	delete p2;
	delete[] p3; // 注意操作符的匹配
	delete p4;
	delete[] p5;

	// 针对内置类型，new/delte跟malloc/free没有本质的区别，只有用法的区别，new/delete简化了一些
	// Cpp没有和calloc和realloc对应的操作符
}

class A
{
public:
	A(int a = 0)
		:_a(a)
	{
		cout << "A():" << this << endl;
	}
	~A()
	{
		cout << "~A():" << this << endl;
	}
private:
	int _a;
};

void Test3()
{
	// 1、堆上申请空间
	A* p1 = (A*)malloc(sizeof(A)); // 不会初始化
	if (p1 == NULL)
	{
		perror("malloc failed\m");
		return;
	}
	// 1、堆上申请空间 2、调用构造函数初始化
	A* p2 = new A; // 调用构造函数初始化
	A* p3 = new A(5); // 显式初始化

	// 1、调用析构函数清理对象中资源 2、释放空间
	delete p2;
	delete p3;

	// 结论：new/delete 是为自定义类型准备的。不仅在堆上申请出来，还会调用构造函数初始化和析构函数清理

	cout << endl << endl;

	A* p4 = new A[5]; // 每个对象都初始化
//	A* p5 = new A[5]{ 1,2,3,4,5 }; // 若自定义类没有给出默认构造函数

	delete[] p4;
}

void Test4()
{
	// malloc 失败返回 NULL，
	char* p1 = (char*)malloc(1024u * 1024u * 1024u * 2 - 1);
	// cout << p1 << endl; // 注意char*指针用cout输出流比较特殊，会识别为字符串而不是指针，要用printf打印char*
	printf("%p\n", p1);
	
	// new 失败时抛异常，不需要检查返回值
	try
	{
		char* p2 = new char[1024u * 1024u * 1024u * 2 - 1];
		printf("%p\n", p2);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
}

int main()
{
	Test4();

	return 0;
}