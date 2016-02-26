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
}
#endif // !_STACK_H_
