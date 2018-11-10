#pragma once
#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP

#include <array>

template<class Object, size_t size>
class ObjectPool
{
public:
	ObjectPool() = default;

	Object* operator()();

private:
	std::array<Object, size> m_pool;
	size_t m_index = 0;
};

#endif

template<class Object, size_t size>
Object* ObjectPool<Object, size>::operator()()
{
	return nullptr;
}
