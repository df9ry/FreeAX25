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

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "Setting.h"
#include "ServerEndPoint.h"
#include "UniquePointerDict"

#include <string>

namespace FreeAX25 {

class Environment;

class Instance {
public:
	/**
	 * Default constructor.
	 */
	Instance():
		m_name{""}, m_environment{nullptr} {}

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
	UniquePointerDict<Setting> settings{};

	/**
	 * ServerEndPoints of this instance.
	 */
	UniquePointerDict<ServerEndPoint> serverEndPoints{};

	/**
	 * ClientEndPoints of this instance.
	 */
	UniquePointerDict<ClientEndPoint> clientEndPoints{};

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
