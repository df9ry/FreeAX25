/*
    Project FreeAX2570
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

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Logger.h"
#include "ServerProxy.h"
#include "SharedPointerDict"

namespace FreeAX25 {

class TimerManager;
class Configuration;
class Null;

/**
 * The class Environment provides a single distribution point
 * for "global" data structures.
 */
class Environment {
public:
	/**
	 * Constructor.
	 */
	Environment();

	/**
	 * Destructor.
	 */
	~Environment();

	/**
	 * Get the Logger object
	 * @return Logger
	 */
	inline Logger* getLogger() {
		return m_logger;
	}

	/**
	 * Write a DEBUG log message
	 * @param msg The message to log
	 */
	inline void logDebug(const std::string& msg) {
		getLogger()->log(LogLevel::DEBUG, msg);
	}

	/**
	 * Write a INFO log message
	 * @param msg The message to log
	 */
	inline void logInfo(const std::string& msg) {
		getLogger()->log(LogLevel::INFO, msg);
	}

	/**
	 * Write a WARNING log message
	 * @param msg The message to log
	 */
	inline void logWarning(const std::string& msg) {
		getLogger()->log(LogLevel::WARNING, msg);
	}

	/**
	 * Write a ERROR log message
	 * @param msg The message to log
	 */
	inline void logError(const std::string& msg) {
		getLogger()->log(LogLevel::ERROR, msg);
	}

	/**
	 * Get the TimerManager object
	 * @return TimerManager
	 */
	inline TimerManager* getTimerManager() {
		return m_timerManager;
	}

	/**
	 * Get the Configuration object
	 * @return Configuration
	 */
	inline Configuration* getConfiguration() {
		return m_configuration;
	}

	/**
	 * Register a server proxy.
	 * @param url URL for registration.
	 * @param sp ServerProxy to register.
	 */
	void registerServerProxy(const std::string& url, const ServerProxy& sp);

	/**
	 * Lookup a server and get a ServerProxy for it. If he server could not
	 * be found an exception is thrown.
	 * @param url The server url to look for.
	 * @return ServerProxy.
	 */
	ServerProxy findServerProxy(const std::string& url);

private:
	Logger*        m_logger;
	TimerManager*  m_timerManager;
	Configuration* m_configuration;
	Null*          m_null;

	SharedPointerDict<ServerProxy>   m_serverProxies{};
};

} /* namespace FreeAX25 */

#endif /* ENVIRONMENT_H_ */
