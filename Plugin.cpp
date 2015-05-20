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

#include "Plugin.h"
#include "Environment.h"

#include <dlfcn.h>
#include <exception>

using namespace std;

namespace FreeAX25 {

/**
 * Constructor
 * @param name Name of this plugin
 * @param e Global environment
 */
Plugin::Plugin(const std::string& name, const std::string& file, Environment* e):
	m_name{name}, m_file{file}, m_environment{e} {}

/**
 * Destructor
 */
Plugin::~Plugin() {
	if (m_handle) dlclose(m_handle);
}

void Plugin::load() {
	m_environment->logInfo("Loading plugin \"" + m_name +"\"");
	if (m_file.length() == 0) { // Builtin
		if (m_name == "/_TIMER") {
			m_init  = initTimerManager;
			m_start = startTimerManager;
		} else if (m_name == "/_LOGGER") {
			m_init  = initLogger;
			m_start = startLogger;
		} else {
			throw runtime_error(
				"Unknown builtin plugin \"" + m_name + "\"");
		}
	} else {
		char* error;
		m_handle = dlopen(m_file.c_str(), RTLD_NOW);
		if (!m_handle) throw runtime_error(
				"Unable to load " + m_name + "! Cause: " + dlerror());
		dlerror(); // Clear error messages
		m_init = (void(*)(Environment*, Plugin*)) dlsym(m_handle, "init");
		error = dlerror();
		if (error != nullptr) throw runtime_error(
				"Unable to link \"init\" from " + m_name + "! Cause: " +error);
		m_start = (void(*)()) dlsym(m_handle, "start");
		if ((error = dlerror()) != nullptr) throw runtime_error(
				"Unable to link \"start\" from " + m_name + "! Cause: " +error);
	}
}

} /* namespace FreeAX25 */
