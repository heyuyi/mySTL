#pragma once
#ifndef _HEAP_H_
#define _HEAP_H_

#include "algorithm.h"

namespace mySTL {
// heap structure
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

		template<typename _TIt>
		heap(_TIt _First, _TIt _Last)
			: container(_First, _Last), compare()
		{
			_Build_heap(container.begin(), container.end() - container.begin(), compare);
		}

		template<typename _TIt>
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


	protected:
		_Container container;
		_FT compare;
	};

}
#endif // !_HEAP_H_
