#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include "tinyxml2.h"

constexpr bool queryOk(tinyxml2::XMLError code)
{
	return code == tinyxml2::XML_SUCCESS;
}

#endif;