#pragma once

namespace wjf
{
	// Compare是一个进行比较的仿函数类，默认为less，因此默认为建大堆
	// greater为建小堆
	template<class T, class Container = vector<T>, class Compare = std::less<T>>
	class priority_queue
	{
	public:
		priority_queue()
		{}; // 初始化列表中Container会自动调用它的构造函数

		Compare com;

		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
		{
			while (first != last)
				_con.push_back(*first++); 
			// 向下调整建堆 -- O(N)
			for (int i = (_con.size() - 1); i >= 0; i--)
				adjust_down(i);
		}
		void adjust_up(size_t child)
		{

			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				//if (_con[child] > _con[parent]) // 建大堆
				//if (_con[child] < _con[parent]) // 建小堆
				if (com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
					break;
			}
		}

		void adjust_down(size_t parent)
		{
			size_t child = parent * 2 + 1; // 默认为左孩子
			while (child < _con.size())
			{
				// 防止孩子越界，挑选大孩子
				//if (child + 1 < _con.size() && _con[child] < _con[child + 1]) // 大堆
				//if (child + 1 < _con.size() && _con[child] > _con[child + 1]) // 小堆
				if (child + 1 < _con.size() && com(_con[child], _con[child+1]))
					child++; 

				//if (_con[child] > _con[parent]) // 大堆
				//if (_con[child] < _con[parent]) // 小堆
				if (com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					break;
			}
		}

		void push(const T& x) // 队尾插入等价堆插入进行向上调整于
		{
			_con.push_back(x);
			adjust_up(_con.size() - 1);
		}

		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]); // 交换堆顶和最后一个
			_con.pop_back(); //删除最后一个
			adjust_down(0);
		}
		
		const T& top() // 取堆顶数据
		{
			return _con[0];
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
		Container _con;
	};
}
