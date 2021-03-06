#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <tinyxml2.h>

constexpr bool queryOk(tinyxml2::XMLError code)
{
	return code == tinyxml2::XML_SUCCESS;
}

template<typename T>
constexpr bool derefLess(const T & lhs, const T & rhs)
{
	return *lhs < *rhs;
}

#endif
