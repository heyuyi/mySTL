#pragma once
#ifndef _QUEUE_H_
#define _QUEUE_H_

namespace mySTL {
// queue structure, P129, <<Introduction to Algorithms>>
template<typename _T,
	typename _Container = deque<_T>>
	class queue
	{
	public:
		typedef typename queue<_T, _Container> _Myt;
		typedef typename _Container container_type;
		typedef typename _Container::value_type value_type;
		typedef typename _Container::size_type size_type;
		typedef typename _Container::reference reference;
		typedef typename _Container::const_reference const_reference;

		queue()
			: container()
		{
		}

		size_type size(void) const
		{
			return container.size();
		}

		bool empty(void) const
		{
			return container.empty();
		}

		reference head(void)
		{
			return container.front();
		}

		const_reference head(void) const
		{
			return container.front();
		}

		reference tail(void)
		{
			return container.back();
		}

		const_reference tail(void) const
		{
			return container.back();
		}

		void push(const value_type& _Val)
		{
			container.push_back(_Val);
		}

		void push(value_type&& _Val)
		{
			container.push_back(std::move(_Val));
		}

		void pop(void)
		{
			container.pop_front();
		}

		template<typename... _ValsT>
		void emplace(_ValsT&&... _Vals)
		{
			container.emplace_back(std::forward<_ValsT>(_Vals)...);
		}

	protected:
		_Container container;
	};

// Achieve a queue using two stacks, P131, <<Introduction to Algorithms>>
template<typename _T,
	typename _Stack = stack<_T>>
	class queue_2stack
	{
	public:
		typedef typename _Stack::value_type value_type;
		typedef typename _Stack::size_type size_type;
		typedef typename _Stack::reference reference;
		typedef typename _Stack::const_reference const_reference;

		queue_2stack()
			: a(), b()
		{
		}

		size_type size(void) const
		{
			return a.size() + b.size();
		}

		bool empty(void) const
		{
			return (a.empty() && b.empty());
		}

		reference head(void)
		{
			if (b.empty())
				return a.bottom();
			else
				return b.top();
		}

		const_reference head(void) const
		{
			if (b.empty())
				return a.bottom();
			else
				return b.top();
		}

		reference tail(void)
		{
			if (a.empty())
				return b.bottom();
			else
				return a.top();
		}

		const_reference tail(void) const
		{
			if (a.empty())
				return b.bottom();
			else
				return a.top();
		}

		void push(const value_type& _Val)
		{
			a.push(_Val);
		}

		void push(value_type&& _Val)
		{
			a.push(std::move(_Val));
		}

		void pop(void)
		{
			if (b.empty()) {
				while (!a.empty()) {
					b.push(a.top());
					a.pop();
				}
			}
			b.pop();
		}

	protected:
		_Stack a, b;
	};
}
#endif // !_QUEUE_H_
