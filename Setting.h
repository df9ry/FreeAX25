/*
 * Setting.h
 *
 *  Created on: 19.05.2015
 *      Author: tania
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
