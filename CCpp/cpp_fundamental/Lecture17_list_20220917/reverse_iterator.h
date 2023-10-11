#pragma once

namespace wjf
{
	// 复用，迭代器适配器
	template<class Iterator, class Ref, class Ptr>
	struct __reverse_iterator
	{
		Iterator _curr; // 类成员，当前的正向迭代器
		typedef __reverse_iterator<Iterator, Ref, Ptr> RIterator;
		__reverse_iterator(Iterator it) 
		// 反向迭代器里封装的是正向迭代器，正向迭代器里封装的是指针或节点
			:_curr(it)
		{}

		RIterator operator++() // 前置++
		{
			--_curr;
			return *this;
		}

		RIterator operator++(int)
		{
			RIterator tmp(*this);
			--_curr;
			return tmp;
		}

		RIterator operator--()
		{
			++_curr;
			return *this;
		}

		RIterator operator--(int)
		{
			RIterator tmp(*this);
			++_curr;
			return tmp;
		}

		Ref operator*()
		{ // 正向迭代器_curr已经重载了*
		// 但不能知道*_curr到底是什么数据类型，所以使用显示的模板参数
			//return *_curr;
			auto tmp = _curr;
			--tmp;
			return *tmp;
		}

		Ptr operator->()
		{// 不能知道_curr到底是什么数据类型，所以使用显示的模板参数
			//return _curr.operator->();
			//return &(*_curr);
			return &(operator*());
		}

		bool operator!=(const RIterator& it)
		{
			return _curr != it._curr;
		}
	};
}
