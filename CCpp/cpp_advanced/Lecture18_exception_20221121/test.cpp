#include <iostream>
#include <string>
#include <windows.h>
#include <time.h> 
using namespace std;

//class Exception //抛异常对象
//{
//public:
//	Exception(const string& errmsg, int id)
//		:_errmsg(errmsg)
//		, _errid(id)
//	{}
//
//	virtual string what() const {
//		return _errmsg;
//	}
//
//	int GetErrid() {
//		return _errid;
//	}
//
//protected:
//	string _errmsg;
//	int _errid;
//};
//
//double Division(int a, int b)
//{
//	// 当b == 0时抛出异常
//	if (b == 0) {
//		Exception e("除0错误", 1);
//		throw e; //生成一个e的拷贝对象抛出，局部对象e销毁
//	}
//	else {
//		return ((double)a / (double)b);
//	}
//}
//
//void Func1() {
//	int len, time;
//	cin >> len >> time;
//	cout << Division(len, time) << endl;
//}
//
//void Func2() {}
//
//// 1、抛异常可以抛任意类型对象
//// 2、捕获时，要求类型匹配
//int main() {
//	while (1) {
//		try {
//			Func1();
//		}
//		catch (const Exception& e) {
//			cout << e.what() << endl;
//		}
//		catch (...) {// 捕获任意类型的异常 -- 防止出现未捕获异常时，程序终止
//			cout << "未知异常" << endl;
//		}
//	}
//	return 0;
//}

//服务器开发中通常使用的异常继承体系
//实际中抛异常抛的都是类对象，不可能是一个数字或字符，因为能表达的太少
class Exception {
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg)
		, _id(id)
	{}
	
	virtual string what() const {
		return _errmsg;
	}

	int getid() const {
		return _id;
	}
protected:
	string _errmsg; //错误信息
	int _id; //错误码
};

//数据库的异常子类
class SqlException : public Exception
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Exception(errmsg, id)
		, _sql(sql)
	{}
	virtual string what() const //虚函数重写实现多态
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;
		return str;
	}
private:
	const string _sql;
};

//缓存的异常子类
class CacheException : public Exception
{
public:
	CacheException(const string& errmsg, int id)
		:Exception(errmsg, id)
	{}
	virtual string what() const
	{
		string str = "CacheException:";
		str += _errmsg;
		return str;
	}
};

//HTTP的异常子类
class HttpServerException : public Exception
{
public:
	HttpServerException(const string& errmsg, int id, const string& type)
		:Exception(errmsg, id)
		, _type(type)
	{}
	virtual string what() const
	{
		string str = "HttpServerException:";
		str += _type;
		str += ":";
		str += _errmsg;
		return str;
	}
protected:
	const string _type;
};

void SQLMgr()
{
	srand(time(0));
	if (rand() % 7 == 0)
	{
		throw SqlException("权限不足", 100, "select * from name = '张三'");
	}
	cout << "请求成功" << endl;
}
void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不足", 200);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 201);
	}
	SQLMgr();
}

//void HttpServer()
//{
//	// ...
//	srand(time(0));
//	if (rand() % 3 == 0)
//	{
//		throw HttpServerException("请求资源不存在", 100, "get");
//	}
//	else if (rand() % 4 == 0)
//	{
//		throw HttpServerException("权限不足", 101, "post");
//	}
//	CacheMgr();
//}

void SendMsg(const string& str)
{
	//要求出现网络错误时先重试三次
	srand(time(0));
	if (rand() % 3 == 0)
	{
		//throw HttpServerException("请求资源不存在", 100, "get");
		throw HttpServerException("网络错误", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("权限不足", 101, "post");
	}
	cout << "发送成功" << endl;
}

void HttpServer() {
	string str("hello");
	//cin >> str;
	//int n = 3;
	//try {
	//	SendMsg(str);
	//}
	//catch (const Exception& e)
	//{
	//	if (e.getid() == 100 && n) {
	//		SendMsg(str);
	//		n--;
	//	}
	//	else {
	//		throw e; //异常的重新抛出
	//	}
	//}

	int n = 3;
	while (n--) {
		try {
			SendMsg(str);
			break; //没有发生异常
		}
		catch (const Exception& e)
		{
			//网络错误 重试3次
			if (e.getid() == 100 && n > 0) {
				continue;
			}
			else {
				throw e; //重新抛出
			}
		}
	}
}

int main() {
	while (1)
	{
		//	this_thread::sleep_for(chrono::seconds(1));
		Sleep(1000);
		try {
			HttpServer();
		}
		catch (const Exception& e) // 这里捕获父类对象就可以
		{
			// 多态
			cout << e.what() << endl;
		}
		// 还可以补充其他的异常体系，也用补充的异常体系的基类来捕
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
	return 0;
}

