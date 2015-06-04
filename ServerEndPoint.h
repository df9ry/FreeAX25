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

#ifndef SERVERENDPOINT_H_
#define SERVERENDPOINT_H_

namespace FreeAX25 {

#include <string>

class ServerEndPoint {
public:
	/**
	 * Default constructor.
	 */
	ServerEndPoint():
		m_name{""}, m_url{""} {}

	/**
	 * Constructor
	 * @param name Name of this ServerEndPoint
	 * @param e Global environment
	 */
	ServerEndPoint(const std::string& name, const std::string& url, Environment* e):
		m_name{name}, m_url{url} {};

	/**
	 * Destructor
	 */
	~ServerEndPoint() {};

	/**
	 * Get the setting name
	 * @return setting name
	 */
	const std::string& getName() const { return m_name; }

	/**
	 * Get the setting name
	 * @return setting name
	 */
	const std::string& getUrl() const { return m_url; }

private:
	const std::string m_name;
	const std::string m_url;
};

} /* namespace FreeAX25 */

#endif /* SERVERENDPOINT_H_ */
