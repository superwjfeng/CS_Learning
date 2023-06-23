#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
using namespace std;

// 最好不要用全局变量，线程不安全
mutex mtx;


//void Print(int n) {
//void Print(int m, mutex& mtx) {
void Print(int n, int& count) {
	mtx.lock();
	for (int i = 0; i < n; i++) {
		cout << this_thread::get_id() << ":" << i << endl;
		//std::this_thread::sleep_for(std::chrono::miliseconds(100));
	}
	count = 5;
	mtx.unlock();
}


// RAII
template<class Lock>
class LockGuard
{
public:
	LockGuard(Lock &lk)
		:_lock(lk)
	{
		_lock.lock();
		cout << "thread:" << this_thread::get_id() << "加锁" << endl;
	}

	~LockGuard()
	{
		cout << "thread:" << this_thread::get_id() << "解锁" << endl << endl;
		_lock.unlock();
	}
private:
	Lock &_lock;
};

int main() {
	mutex mtx;
	//int count = 0;
	atomic<int> x = 0;
	//int x = 0;
	int n = 10;
	// 报错：mutex禁止拷贝传参，就算是写成引用传参，从迪岑固实现的角度看本质还是拷贝，所以依然报错
	//thread t1(Print, 100, ref(count));
	//thread t2(Print, 100, ref(count));

	int m;
	cin >> m;
	vector<thread> v;
	v.resize(m);

	for (int i = 0; i < m; i++) {
		//移动赋值给vector中的线程
		v[i] = thread([&]() {
			for (int i = 0; i < n; i++) {
				mtx.lock();
				try {
					cout << this_thread::get_id() << ":" << i << endl;
					//std::this_thread::sleep_for(std::chrono::miliseconds(100));
				}
				catch (...) { // ... 表示捕获跑出来的任何异常
					mtx.unlock();
					throw;
				}
				mtx.unlock();
			}
		});
	}

	for (auto &t : v) {
		t.join();
	}

	cout << x << endl;

	return 0;
}