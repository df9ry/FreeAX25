/*
    Project FreeAX25
    Copyright (C) 2015  tania@df9ry.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
 * Typename for Map pairs
 */
template <typename T>
using MapPair = typename std::pair<const std::string, std::unique_ptr<T>>;
/**
 * Typename for iterator for Map<T>
 */
template <typename T>
using MapIterator = typename MapBase<T>::iterator;

template <typename T>
using MapConstIterator = typename MapBase<T>::const_iterator;

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
	 * Insert a value into the map.
	 * @param key Key of the entry.
	 * @param value Value of the entry.
	 * @return Iterator.
	 */
	MapIterator<T> insert(const std::string& key, T* value)
	{
		auto result = MapBase<T>::insert(
				MapPair<T>{key, std::unique_ptr<T>{value}});
		if (!result.second)
			throw std::invalid_argument("Double key: " + key);
		return result.first;
	}

	/**
	 * Insert a value into the map.
	 * @param key Key of the entry.
	 * @param pv Unique pointer to the entry.
	 * @return Iterator.
	 */
	MapIterator<T> insert2(const std::string& key,
			std::unique_ptr<T>&& pv)
	{
		auto result = MapBase<T>::insert(
				MapPair<T>{key, move(pv)});
		if (!result.second)
			throw std::invalid_argument("Double key: " + key);
		return result.first;
	}

	/**
	 * Find element with key
	 * @param key The key to lookup
	 * @return pointer to value or nullptr
	 */
	const T* findAndGet(const std::string& key) {
		MapIterator<T> x = MapBase<T>::find(key);
		return (x == MapBase<T>::end()) ? nullptr : x->second.get();
	}
};

} /* namespace FreeAX25 */

#endif /* MAP_H_ */
