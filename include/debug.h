#pragma once
#ifndef _DEBUG_H_
#define _DEBUG_H_

namespace mySTL {
template<typename _FPtr1,
	typename _FPtr2> inline
	bool isValidFunc(_FPtr1 f1, _FPtr2 f2)
	{
		return (typeid(f1) == typeid(f2));
	}
}
#endif