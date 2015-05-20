/*
 * Plugin.cpp
 *
 *  Created on: 18.05.2015
 *      Author: tania
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
