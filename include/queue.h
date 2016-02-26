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
}
#endif // !_QUEUE_H_
