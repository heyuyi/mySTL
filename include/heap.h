#pragma once
#ifndef _HEAP_H_
#define _HEAP_H_

#include "algorithm.h"

namespace mySTL {
// heap structure, P84, <<Introduction to Algorithms>>
template<typename _T,
	typename _FT = less<_T>,
	typename _Container = vector<_T>>
	class heap
	{
	public:
		typedef typename heap<_T, _FT, _Container> _Myt;
		typedef typename _Container container_type;
		typedef typename _Container::value_type value_type;
		typedef typename _Container::size_type size_type;
		typedef typename _Container::difference_type difference_type;
		typedef typename _Container::reference reference;
		typedef typename _Container::const_reference const_reference;

		heap()
			: container(), compare()
		{
		}

		heap(const _Myt& _Copy)
			: container(_Copy.container), compare(_Copy.compare)
		{
		}

		heap(const _FT& com)
			: container(), compare(com)
		{
		}

		heap(const _Container& con)
			: container(con), compare()
		{
			_Build_heap(container.begin(), container.end() - container.begin(), compare);
		}

		heap(const _Container& con, const _FT& com)
			: container(con), compare(com)
		{
			_Build_heap(container.begin(), container.end() - container.begin(), compare);
		}

		template<typename _TIt,
			// Next line is very very ... important !!!
			// Check if _TIt is a type of iterator or not.
			// Without it, heap(_TIt _First, _TIt _Last) and heap(_Container&& con) will be
			// confusing, when the parameter is a 2-size initializer_list.
			typename = typename std::enable_if<std::_Is_iterator<_TIt>::value, void>::type>
		heap(_TIt _First, _TIt _Last)
			: container(_First, _Last), compare()
		{
			_Build_heap(container.begin(), container.end() - container.begin(), compare);
		}

		template<typename _TIt,
			typename = typename std::enable_if<std::_Is_iterator<_TIt>::value, void>::type>
		heap(_TIt _First, _TIt _Last, const _FT& com)
			: container(_First, _Last), compare(com)
		{
			_Build_heap(container.begin(), container.end() - container.begin(), compare);
		}

		_Myt& operator= (const _Myt& _Copy)
		{
			container = _Copy.container;
			compare = _Copy.compare;
			return *this;
		}

		heap(_Myt&& _Copy)
			: container(std::move(_Copy.container)), compare(std::move(_Copy.compare))
		{
		}

		heap(_Container&& con)
			: container(std::move(con)), compare()
		{
			_Build_heap(container.begin(), container.end() - container.begin(), compare);
		}

		heap(_Container&& con, const _FT& com)
			: container(std::move(con)), compare(com)
		{
			_Build_heap(container.begin(), container.end() - container.begin(), compare);
		}

		_Myt& operator=(_Myt&& _Copy)
		{
			container = std::move(_Copy.container);
			compare = std::move(_Copy.compare);
			return *this;
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
			return container.front();
		}

		const_reference top(void) const
		{
			return container.front();
		}

		void pop(void)
		{
			if (!container.empty()) {
				swap(container.front(), container.back());
				_Adjust_heap(container.begin(), container.end() - container.begin() - 1,
					static_cast <decltype(container.end() - container.begin())>(0), compare);
				container.pop_back();
			}
		}

		void push(const value_type& _Val)
		{
			container.push_back(_Val);
			_Push_heap(container.begin(), container.end() - container.begin(), compare);
		}

		void push(value_type&& _Val)
		{
			container.push_back(std::move(_Val));
			_Push_heap(container.begin(), container.end() - container.begin(), compare);
		}

		template<typename... _ValsT>
		void emplace(_ValsT&&... _Vals)
		{
			container.emplace_back(std::forward<_ValsT>(_Vals)...);
			_Push_heap(container.begin(), container.end() - container.begin(), compare);
		}
	protected:
		_Container container;
		_FT compare;
	};

}
#endif // !_HEAP_H_
