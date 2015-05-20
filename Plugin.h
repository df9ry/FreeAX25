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

#ifndef PLUGIN_H_
#define PLUGIN_H_

#include "Map.h"
#include "Instance.h"
#include "Setting.h"

#include <string>

namespace FreeAX25 {

class Environment;

class Plugin {
public:
	/**
	 * Constructor
	 * @param name Name of this plugin
	 * @param e Global environment
	 */
	Plugin(const std::string& name, const std::string& file, Environment* e);

	/**
	 * Destructor
	 */
	~Plugin();

	/**
	 * Settings of this plugin
	 */
	Map<Setting> settings{};

	/**
	 * Instance of this plugin
	 */
	Map<Instance>    instances{};

	/**
	 * Get the plugin name
	 * @return plugin name
	 */
	const std::string& getName() const { return m_name; }

	/**
	 * Load and link the shared object or builtin
	 */
	void load();

	void init() {
		if (m_init != nullptr) m_init(m_environment, this);
	}

	void start() {
		if (m_start != nullptr) m_start();
	}

private:
	const std::string m_name;
	const std::string m_file;
	Environment*      m_environment;
	void*             m_handle{nullptr};
	void(*m_init)(Environment* e, Plugin* p){nullptr};
	void(*m_start)(){nullptr};
};

} /* namespace FreeAX25 */

#endif /* PLUGIN_H_ */
