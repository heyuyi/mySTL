#pragma once
#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <functional>

namespace mySTL {
// some kinds of sort algorithm
// insertion-sort
template<typename _TIt, 
	typename _FPtr> inline
	void insertSort(_TIt beg, _TIt end, _FPtr func)
	{
		_TIt it1, it2;
		for (it1 = beg + 1; it1 < end; ++it1)
		{
			auto val = *it1;
			for (it2 = it1; it2 > beg && func(val, *(it2 - 1)); --it2)
				*it2 = *(it2-1);
			*it2 = val;
		}
	}

template<typename _TIt> inline
	void insertSort(_TIt beg, _TIt end)
	{
		insertSort(beg, end, std::less<>());
	}

// heap-sort
template<typename _TIt,
	typename _Diff,
	typename _FPtr> inline
	void _Adjust_heap(_TIt beg, _Diff n, _Diff i, _FPtr func)
	{
		auto val = *(beg + i);
		_Diff child = 2 * i + 2;
		for (; child < n; child = 2 * child + 2)
		{
			if (func(*(beg + child), *(beg + child - 1)))
				--child;
			if (func(val, *(beg + child)))
			{
				*(beg + i) = *(beg + child);
				i = child;
			}
			else
				break;
		}
		if (child == n && func(val, *(beg + child - 1)))
		{
			*(beg + i) = *(beg + child - 1);
			*(beg + child - 1) = val;
		}
		else
			*(beg + i) = val;
	}

template<typename _TIt,
	typename _Diff,
	typename _FPtr> inline
	void _Build_heap(_TIt beg, _Diff n, _FPtr func)
	{
		for (_Diff i = n / 2 - 1; i >= 0; --i)
			_Adjust_heap(beg, n, i, func);
	}

template<typename _TIt,
	typename _Diff,
	typename _FPtr> inline
	void _Sort_heap(_TIt beg, _Diff n, _FPtr func)
	{
		for (_Diff i = n - 1; i > 0; --i)
		{
			swap(*beg, *(beg + i));
			_Adjust_heap(beg, i, 0, func);
		}
	}

template<typename _TIt,
	typename _FPtr> inline
	void heapSort(_TIt beg, _TIt end, _FPtr func)
	{
		_Build_heap(beg, end - beg, func);
		_Sort_heap(beg, end - beg, func);
	}

template<typename _TIt> inline
	void heapSort(_TIt beg, _TIt end)
	{
		heapSort(beg, end, std::less<>());
	}

// quick-sort
template<typename _TIt,
	typename _FPtr> inline
	void quickSort(_TIt beg, _TIt end, _FPtr func)
	{

	}

template<typename _TIt> inline
	void quickSort(_TIt beg, _TIt end)
	{
		quickSort(beg, end, std::less<>());
	}
}
#endif