#pragma once
#include <deque>

namespace wjf
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		// 默认生成的构造、析构、拷贝都够用了，会自动调用vector的
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}

		T& top()
		{
			return _con.back();
		}
		const T& top() const
		{
			return _con.back();
		}
		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}
	private:
		Container _con; // 用已有的容器进行封装
	};
}
