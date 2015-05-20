/*
 * Map.h
 *
 *  Created on: 18.05.2015
 *      Author: tania
 */

#ifndef MAP_H_
#define MAP_H_

#include <map>
#include <string>
#include <memory>
#include <exception>

namespace FreeAX25 {

/**
 * Typename for base class for Map<T>
 */
template <typename T>
using MapBase = typename std::map<std::string, std::unique_ptr<T>>;

/**
 * Typename for iterator for Map<T>
 */
template <typename T>
using MapIterator = typename MapBase<T>::iterator;

/**
 * Template for hashed maps with string keys and unique_ptr support.
 */
template <typename T>
class Map: public MapBase<T> {
public:

	/**
	 * Constructor
	 */
	Map() {}

	/**
	 * Destructor
	 */
	~Map() {}

	/**
	 * Insert a value into the map
	 * @param key Key of the entry
	 * @param value Value of the entry
	 * @return Iterator
	 */
	MapIterator<T> insert(const std::string& key, T* value)
	{
		std::unique_ptr<T> _ptr{value};
		std::pair<std::string, std::unique_ptr<T>>
			_pair{key, std::move(_ptr)};
		auto result = MapBase<T>::insert(std::move(_pair));
		if (!result.second)
			throw std::invalid_argument("Double key: " + key);
		return result.first;
	}

	/**
	 * Remove and delete entry by iterator
	 * @param iter Iterator of the entry to remove
	 * @return True, if entry was removed
	 */
	bool remove(const MapIterator<T> iter) {
		return(MapBase<T>::erase(iter) == 1);
	}

	/**
	 * Remove and delete entry by key
	 * @param key Key of the entry to remove
	 * @return True, if entry was removed
	 */
	bool erase(const std::string& key) {
		return(MapBase<T>::erase(key) == 1);
	}

	/**
	 * Find element with key
	 * @param key The key to lookup
	 * @return pointer to value or nullptr
	 */
	T* find(const std::string& key) {
		MapIterator<T> x = MapBase<T>::find(key);
		return (x == MapBase<T>::end()) ? nullptr : x->second.get();
	}
};

} /* namespace FreeAX25 */

#endif /* MAP_H_ */
