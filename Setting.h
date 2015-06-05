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
	Setting(): m_name{""}, m_value{""}, m_set{false} {};

	/**
	 * Constructor
	 * @param name Name of this setting.
	 * @param value Value of this setting.
	 */
	Setting(const std::string& name, const std::string& value):
		m_name{name}, m_value{value}, m_set{true} {};

	/**
	 * Copy constructor.
	 * @param other Setting to copy from.
	 */
	Setting(const Setting& other):
		m_name{other.m_name}, m_value{other.m_value}, m_set{other.m_set} {};

	/**
	 * Move constructor.
	 * @param other Setting to move.
	 */
	Setting(Setting&& other): m_name{""}, m_value{""}, m_set{false} {
		std::swap(m_name,  other.m_name);
		std::swap(m_value, other.m_value);
		std::swap(m_set,   other.m_set);
	}

	/**
	 * Copy assignment.
	 * @param other The Setting to assign.
	 * @return Reference to this.
	 */
	Setting& operator=(const Setting& other) {
		m_name  = other.m_name;
		m_value = other.m_value;
		m_set   = other.m_set;
		return *this;
	}

	/**
	 * Move assignment.
	 * @param other The Setting to move.
	 * @return Reference to this.
	 */
	Setting& operator=(Setting&& other) {
		std::swap(m_name,  other.m_name);
		std::swap(m_value, other.m_value);
		std::swap(m_set,   other.m_set);
		return *this;
	}

	/**
	 * Destructor
	 */
	~Setting() {}

	/**
	 * Test if this Setting is set.
	 * @return If Setting is set.
	 */
	bool isSet() const noexcept { return m_set; }

	/**
	 * Test if this Setting is empty.
	 * @return If Setting is empty.
	 */
	bool isEmpty() const noexcept { return !m_set; }

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
		if (!m_set) throw std::runtime_error("Value is not set");
		if (m_value == "true") return true;
		if (m_value == "false") return false;
		throw std::invalid_argument("Invalid boolean value: " + m_value);
	}

	/**
	 * Get value as string.
	 */
	explicit operator std::string() const {
		if (!m_set) throw std::runtime_error("Value is not set");
		return asString();
	}

	/**
	 * Get value as int.
	 */
	explicit operator int() const {
		if (!m_set) throw std::runtime_error("Value is not set");
		return asInt();
	}

	/**
	 * Get value as boolean.
	 */
	explicit operator bool() const {
		if (!m_set) throw std::runtime_error("Value is not set");
		return asBool();
	}

	/**
	 * Helper function to retrieve values.
	 * @param dict The dictionary to look in.
	 * @param key The key to look for.
	 * @param def Default value, if value is not found.
	 * @return Value or default value, if key is not found.
	 */
	static const std::string asStringValue(
			const UniquePointerDict<Setting>& dict,
			const std::string& key,
			const std::string& def = "")
	{
		const Setting setting{dict.findEntryConst(key)};
		return setting.m_set ? setting.asString() : def;
	}

	/**
	 * Helper function to retrieve values.
	 * @param dict The dictionary to look in.
	 * @param key The key to look for.
	 * @param def Default value, if value is not found.
	 * @return Value or default value, if key is not found.
	 */
	static int asIntValue(
			const UniquePointerDict<Setting>& dict,
			const std::string& key,
			int def = -1)
	{
		const Setting setting{dict.findEntryConst(key)};
		return setting.m_set ? setting.asInt() : def;
	}

	/**
	 * Helper function to retrieve values.
	 * @param dict The dictionary to look in.
	 * @param key The key to look for.
	 * @param def Default value, if value is not found.
	 * @return Value or default value, if key is not found.
	 */
	static bool asBoolValue(
			const UniquePointerDict<Setting>& dict,
			const std::string& key,
			bool def = false)
	{
		const Setting& setting{dict.findEntryConst(key)};
		return setting.m_set ? setting.asBool() : def;
	}

private:
	std::string       m_name;
	std::string       m_value;
	bool              m_set;
};

} /* namespace FreeAX25 */

#endif /* SETTING_H_ */
