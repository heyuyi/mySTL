#pragma once
#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

//#include <functional>

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

//merge-sort
template<typename _TIt,
	typename _FPtr> inline
	void _Merge(_TIt beg, _TIt mid, _TIt end, _FPtr func)
	{
		auto n1 = mid - beg;
		auto n2 = end - mid;
		decltype(n1) i, j;
		auto *_Lp = new remove_reference<decltype(*beg)>::type[n1];
		auto *_Rp = new remove_reference<decltype(*beg)>::type[n2];
		for (i = 0; i < n1; ++i)
			_Lp[i] = *(beg + i);
		for (j = 0; j < n2; ++j)
			_Rp[j] = *(mid + j);
		i = 0; j = 0;
		for (_TIt it = beg; it < end; ++it) {
			if (i < n1) {
				if (j < n2) {
					if (func(_Lp[i], _Rp[j]))
						*it = _Lp[i++];
					else
						*it = _Rp[j++];
				}
				else
					*it = _Lp[i++];
			}
			else {
				*it = _Rp[j++];
			}
		}
		delete[]_Lp;
		delete[]_Rp;
	}

template<typename _TIt,
	typename _FPtr> inline
	void mergeSort(_TIt beg, _TIt end, _FPtr func)
	{
		auto n = end - beg;
		if (n > 1) {
			_TIt mid = beg + (end - beg) / 2;
			mergeSort(beg, mid, func);
			mergeSort(mid, end, func);
			_Merge(beg, mid, end, func);
		}
	}

template<typename _TIt> inline
	void mergeSort(_TIt beg, _TIt end)
	{
		mergeSort(beg, end, std::less<>());
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
	void _Quick_sort_0(_TIt beg, _TIt end, _FPtr func)
	{
		auto s = end - beg;
		if (s > 1) {
			auto val = *beg;
			_TIt i = beg + 1, j = beg;
			for (; i < end; ++i) {
				if (func(*i, val)) {
					++j;
					swap(*j, *i);
				}
			}
			if (j != beg)
				swap(*beg, *j);
			_Quick_sort_0(beg, j, func);
			_Quick_sort_0(j + 1, end, func);
		}
	}

template<typename _TIt,
	typename _FPtr> inline
	void _Quick_sort_1(_TIt beg, _TIt end, _FPtr func)
	{
		auto s = end - beg;
		if (s > 1) {
			auto val = *beg;
			_TIt i = beg, j = end;
			for (;;) {
				do {
					++i;
				} while (i < end && func(*i, val));
				do {
					--j;
				} while (/*j >= beg && */func(val, *j));
				if (i < j)
					swap(*i, *j);
				else
					break;
			}
			swap(*beg, *j);
			_Quick_sort_1(beg, j, func);
			_Quick_sort_1(j + 1, end, func);
		}
	}

template<typename _TIt,
	typename _FPtr> inline
	typename _TIt mid3(_TIt a1, _TIt a2, _TIt a3, _FPtr func)
	{
		if (func(*a1, *a2)) {
			if (func(*a2, *a3))
				return a2;
			else if (func(*a1, *a3))
				return a3;
			else
				return a1;
		}
		else {
			if (func(*a1, *a3))
				return a1;
			else if (func(*a2, *a3))
				return a3;
			else
				return a2;
		}
	}

template<typename _TIt,
	typename _FPtr> inline
	void _Quick_sort_2(_TIt beg, _TIt end, _FPtr func)
	{
		auto len = end - beg;
		if (len > 1) {
			if (len > 7) {
				_TIt l = beg;
				_TIt m = beg + len / 2;
				_TIt n = end - 1;
				if (len > 40) {
					auto d = len / 8;
					l = mid3(l, l + d, l + 2 * d, func);
					m = mid3(m - d, m, m + d, func);
					n = mid3(n - 2 * d, n - d, n, func);
				}
				_TIt it = mid3(l, m, n, func);
				swap(*beg, *it);
			}			

			auto val = *beg;
			_TIt i = beg, j = end;
			for (;;) {
				do {
					++i;
				} while (i < end && func(*i, val));
				do {
					--j;
				} while (/*j >= beg && */func(val, *j));
				if (i < j)
					swap(*i, *j);
				else
					break;
			}
			swap(*beg, *j);
			_Quick_sort_2(beg, j, func);
			_Quick_sort_2(j + 1, end, func);
		}
	}

template<typename _TIt,
	typename _FPtr> inline
	void quickSort(_TIt beg, _TIt end, _FPtr func)
	{
		/*if(n == 0)
			_Quick_sort_0(beg, end, func);
		else if (n == 1)
			_Quick_sort_1(beg, end, func);
		else*/
			_Quick_sort_2(beg, end, func);
	}

template<typename _TIt> inline
	void quickSort(_TIt beg, _TIt end)
	{
		quickSort(beg, end, std::less<>());
	}
}
#endif