/*
 * Configuration.h
 *
 *  Created on: 18.05.2015
 *      Author: tania
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
