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

#ifndef SETTING_H_
#define SETTING_H_

#include "Map.h"

#include <string>

namespace FreeAX25 {

class Environment;

class Setting {
public:

	/**
	 * Constructor
	 * @param name Name of this setting
	 * @param e Global environment
	 */
	Setting(const std::string& name, const std::string& value, Environment* e):
		m_name{name}, m_value{value}, m_environment{e} {};

	/**
	 * Destructor
	 */
	~Setting() {};

	/**
	 * Get the setting name
	 * @return setting name
	 */
	const std::string& getName() const { return m_name; }

	/**
	 * Get the setting value
	 * @return setting value
	 */
	const std::string& asString() const { return m_value; }

	/**
	 * Find string value from settings map
	 * @param map The map to lookup
	 * @param key The value key
	 * @param def The default value
	 * @return string value
	 */
	static const std::string asString(
			Map<Setting>& map, const std::string& key, const std::string def="");

	/**
	 * Get value as integer
	 * @return int value
	 */
	int asInt() const { return std::stoi(m_value); }

	/**
	 * Find integer value from settings map
	 * @param map The map to lookup
	 * @param key The value key
	 * @param def The default value
	 * @return int value
	 */
	static int asInt(Map<Setting>& map, const std::string& key, int def=0);

private:
	const std::string m_name;
	const std::string m_value;
	Environment*      m_environment;
};

} /* namespace FreeAX25 */

#endif /* SETTING_H_ */
