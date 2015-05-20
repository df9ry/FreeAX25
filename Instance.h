/*
 * Instance.h
 *
 *  Created on: 19.05.2015
 *      Author: tania
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "Setting.h"
#include "Map.h"

#include <string>

namespace FreeAX25 {

class Environment;

class Instance {
public:
	/**
	 * Constructor
	 * @param name Name of the instance
	 * @param e Global environment
	 */
	Instance(const std::string& name, Environment* e):
		m_name{name}, m_environment{e} {};

	/**
	 * Destructor
	 */
	~Instance() {}

	/**
	 * Settings of this instance
	 */
	Map<Setting> settings{};

	/**
	 * Get the instance name
	 * @return instance name
	 */
	const std::string& getName() const { return m_name; }

private:
	const std::string m_name;
	Environment*      m_environment;
};

} /* namespace FreeAX25 */

#endif /* INSTANCE_H_ */
