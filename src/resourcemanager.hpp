#pragma once
#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "resource.hpp"

#include <map>
#include <memory>
#include <string>
#include <utility>

class ResourceManager
{
public:
	template<typename T>
	void loadFromFile(const std::string & path)
	{
		std::unique_ptr<Resource> ptr = std::make_unique<T>(T());

		bool result = ptr->loadFromFile(path);

		if(!result)	//Resource did not load
		{
			std::terminate();
		}

		m_map[path] = std::move(ptr);
	}

	template<typename T>
	T* access(const std::string & path)
	{
		auto ptr = m_map.find(path);

		if(ptr == m_map.end()) //If resource does not exist, load it
		{
			loadFromFile<T>(path);
		}
			
		return static_cast<T*>(ptr->second.get());
	}

private:
	std::map<std::string, std::unique_ptr<Resource>> m_map;
};

#endif
