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

#include "UniquePointerDict"

#include <string>
#include <stdexcept>

namespace FreeAX25 {

class Environment;

class Setting {
public:

	/**
	 * Standard constructor.
	 */
	Setting(): m_name{""}, m_value{""}, m_environment{nullptr} {};

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
	~Setting() {}

	/**
	 * Test if this Setting is set.
	 * @return If Setting is set.
	 */
	bool isEmpty() const noexcept { return m_environment; }

	/**
	 * Get the setting name
	 * @return setting name
	 */
	const std::string& getName() const noexcept { return m_name; }

	/**
	 * Get the setting value
	 * @return setting value
	 */
	const std::string& asString() const noexcept { return m_value; }

	/**
	 * Get value as integer
	 * @return int value
	 */
	int asInt() const { return std::stoi(m_value); }

	const bool asBool() const {
		if (m_value == "true") return true;
		if (m_value == "false") return false;
		throw std::invalid_argument("Invalid boolean value: " + m_value);
	}

	/**
	 * Get value as string.
	 */
	explicit operator std::string() const noexcept { return asString(); }

	/**
	 * Get value as int.
	 */
	explicit operator int() const { return asInt(); }

	/**
	 * Get value as boolean.
	 */
	explicit operator bool() const { return asBool(); }

	/**
	 * Helper function to retrieve values.
	 * @param dict The dictionary to look in.
	 * @param key The key to look for.
	 * @param def Default value, if value is not found.
	 * @return Value or default value, if key is not found.
	 */
	static std::string asString(
			const UniquePointerDict<Setting>& dict,
			const std::string& key,
			const std::string& def = "")
	{
		const Setting& setting{dict.findEntryConst(key)};
		return setting.isEmpty() ? def : setting.asString();
	}

	/**
	 * Helper function to retrieve values.
	 * @param dict The dictionary to look in.
	 * @param key The key to look for.
	 * @param def Default value, if value is not found.
	 * @return Value or default value, if key is not found.
	 */
	static int asInt(
			const UniquePointerDict<Setting>& dict,
			const std::string& key,
			int def = -1)
	{
		const Setting& setting{dict.findEntryConst(key)};
		return setting.isEmpty() ? def : setting.asInt();
	}

	/**
	 * Helper function to retrieve values.
	 * @param dict The dictionary to look in.
	 * @param key The key to look for.
	 * @param def Default value, if value is not found.
	 * @return Value or default value, if key is not found.
	 */
	static bool asBool(
			const UniquePointerDict<Setting>& dict,
			const std::string& key,
			bool def = false)
	{
		const Setting& setting{dict.findEntryConst(key)};
		return setting.isEmpty() ? def : setting.asBool();
	}

private:
	const std::string m_name;
	const std::string m_value;
	Environment*      m_environment;
};

} /* namespace FreeAX25 */

#endif /* SETTING_H_ */
