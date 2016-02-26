#pragma once
#ifndef _STACK_H_
#define _STACK_H_

namespace mySTL {
// stack structure, P129, <<Introduction to Algorithms>>
template<typename _T,
	typename _Container = vector<_T>>
	class stack
	{
	public:
		typedef typename stack<_T, _Container> _Myt;
		typedef typename _Container container_type;
		typedef typename _Container::value_type value_type;
		typedef typename _Container::size_type size_type;
		typedef typename _Container::reference reference;
		typedef typename _Container::const_reference const_reference;

		stack()
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

		reference top(void)
		{
			return container.back();
		}

		const_reference top(void) const
		{
			return constainer.back();
		}

		reference bottom(void)
		{
			return container.front();
		}

		const_reference bottom(void) const
		{
			return constainer.front();
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
			container.pop_back();
		}

		template<typename... _ValsT>
		void emplace(_ValsT&&... _Vals)
		{
			container.emplace_back(std::forward<_ValsT>(_Vals)...);
		}

	protected:
		_Container container;
	};

// Achieve a stack using two queues, P131, <<Introduction to Algorithms>>
template<typename _T,
	typename _Queue = queue<_T>>
	class stack_2queue
	{
	public:
		typedef typename _Queue::value_type value_type;
		typedef typename _Queue::size_type size_type;
		typedef typename _Queue::reference reference;
		typedef typename _Queue::const_reference const_reference;

		stack_2queue()
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

		reference top(void)
		{
			return valid_queue().tail();
		}

		const_reference top(void) const
		{
			return valid_queue().tail();
		}

		reference bottom(void)
		{
			return valid_queue().head();
		}

		const_reference bottom(void) const
		{
			return valid_queue().head();
		}

		void push(const value_type& _Val)
		{
			valid_queue().enqueue(_Val);
		}

		void push(value_type&& _Val)
		{
			valid_queue().enqueue(std::move(_Val));
		}

		void pop(void)
		{
			_Queue& x = valid_queue();
			_Queue& y = empty_queue();
			while (x.size() > 1) {
				y.enqueue(x.head());
				x.dequeue();
			}
			x.dequeue();
		}

	private:
		_Queue& empty_queue(void)
		{
			if (b.empty())
				return b;
			else
				return a;
		}

		_Queue& valid_queue(void)
		{
			if (b.empty())
				return a;
			else
				return b;
		}

	protected:
		_Queue a, b;
	};
}
#endif // !_STACK_H_
