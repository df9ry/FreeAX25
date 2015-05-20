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

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "Map.h"
#include "Plugin.h"
#include "Setting.h"

#include <string>

namespace FreeAX25 {

class Environment;

class Configuration {
public:
	/**
	 * Constructor
	 * @param e Global Environment
	 */
	Configuration(Environment* e);

	/**
	 * Destructor
	 */
	~Configuration();

	/**
	 * Get ID of this configuration
	 * @return ID
	 */
	const std::string& getId() const {
		return m_id;
	}

	/**
	 * Set the ID of this config
	 * @param id The ID to set
	 */
	void setId(const std::string& id) {
		m_id = id;
	}

	/**
	 * Map of plugins
	 */
	Map<Plugin>  plugins{};

	/**
	 * Map of settings
	 */
	Map<Setting> settings{};

private:
	Environment* m_environment;

	std::string  m_id{};
};

} /* namespace FreeAX25 */

#endif /* CONFIGURATION_H_ */
