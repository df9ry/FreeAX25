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
#include "Null.h"
#include "TimerManager.h"

#include <dlfcn.h>
#include <exception>

using namespace std;

namespace FreeAX25 {

Plugin::Plugin(): m_name{""}, m_file{""} {}

Plugin::Plugin(Plugin&& other): m_name{""}, m_file{""}
{
	swap(m_name,   other.m_name);
	swap(m_file,   other.m_file);
	swap(m_handle, other.m_handle);
	swap(m_init,   other.m_init);
	swap(m_start,  other.m_start);
}

Plugin::Plugin(const std::string& name, const std::string& file):
	m_name{name}, m_file{file} {}

Plugin::~Plugin() {
	if (m_handle) dlclose(m_handle);
}

Plugin& Plugin::operator=(Plugin&& other) {
	swap(m_name,   other.m_name);
	swap(m_file,   other.m_file);
	swap(m_handle, other.m_handle);
	swap(m_init,   other.m_init);
	swap(m_start,  other.m_start);
	return *this;
}

void Plugin::load() {
	environment.logInfo("Loading plugin \"" + m_name +"\"");
	if (m_file.length() == 0) { // Builtin
		if (m_name == "/_TIMER") {
			m_init  = FreeAX25::initTimerManager;
			m_start = FreeAX25::startTimerManager;
		} else if (m_name == "/_LOGGER") {
			m_init  = FreeAX25::initLogger;
			m_start = FreeAX25::startLogger;
		} else if (m_name == "/_NULL") {
			m_init  = FreeAX25::initNull;
			m_start = FreeAX25::startNull;
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
		m_init = (void(*)(Plugin&)) dlsym(m_handle, "init");
		error = dlerror();
		if (error != nullptr) throw runtime_error(
				"Unable to link \"init\" from " + m_name + "! Cause: " +error);
		m_start = (void(*)()) dlsym(m_handle, "start");
		if ((error = dlerror()) != nullptr) throw runtime_error(
				"Unable to link \"start\" from " + m_name + "! Cause: " +error);
	}
}

} /* namespace FreeAX25 */
