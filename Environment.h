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

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Logger.h"
#include "TimerManager.h"
#include "Configuration.h"
#include "ServerProxy.h"
#include "SharedPointerDict"

namespace FreeAX25 {

/**
 * The class Environment provides a single distribution point
 * for "global" data structures.
 */
class Environment {
public:

	/**
	 * Constructor.
	 */
	Environment() {}

	/**
	 * Environment can not be copied.
	 * @param other Not used.
	 */
	Environment(const Environment& other) = delete;

	/**
	 * Environment can not be moved.
	 * @param other Not used.
	 */
	Environment(Environment&& other) = delete;

	/**
	 * Environment can not be copy assigned.
	 * @param other Not used.
	 * @return Not used.
	 */
	Environment& operator=(const Environment& other) = delete;

	/**
	 * Environment can not be move assigned.
	 * @param other Not used.
	 * @return Not used.
	 */
	Environment& operator=(Environment&& other) = delete;

	/**
	 * Destructor.
	 */
	~Environment() {}

	/**
	 * Logger service.
	 */
	Logger logger{};

	/**
	 * Timer service;
	 */
	TimerManager timerManager{};

	/**
	 * Configuration info.
	 */
	Configuration configuration{};

	/**
	 * Server proxies.
	 */
	SharedPointerDict<ServerProxy>   serverProxies{};


	/**
	 * Write a DEBUG log message
	 * @param msg The message to log
	 */
	inline void logDebug(const std::string& msg) {
		logger.log(LogLevel::DEBUG, msg);
	}

	/**
	 * Write a DEBUG log message
	 * @param msg The message to log
	 */
	inline void logDebug(const char* msg) {
		logger.log(LogLevel::DEBUG, std::string(msg));
	}

	/**
	 * Write a INFO log message
	 * @param msg The message to log
	 */
	inline void logInfo(const std::string& msg) {
		logger.log(LogLevel::INFO, msg);
	}

	/**
	 * Write a INFO log message
	 * @param msg The message to log
	 */
	inline void logInfo(const char* msg) {
		logger.log(LogLevel::INFO, std::string(msg));
	}

	/**
	 * Write a WARNING log message
	 * @param msg The message to log
	 */
	inline void logWarning(const std::string& msg) {
		logger.log(LogLevel::WARNING, msg);
	}

	/**
	 * Write a WARNING log message
	 * @param msg The message to log
	 */
	inline void logWarning(const char* msg) {
		logger.log(LogLevel::WARNING, std::string(msg));
	}

	/**
	 * Write a ERROR log message
	 * @param msg The message to log
	 */
	void logError(const std::string& msg) {
		logger.log(LogLevel::ERROR, msg);
	}

	/**
	 * Write a ERROR log message
	 * @param msg The message to log
	 */
	void logError(const char* msg) {
		logger.log(LogLevel::ERROR, std::string(msg));
	}
};

/**
 * Global environment.
 */
Environment environment{};

} /* namespace FreeAX25 */

#endif /* ENVIRONMENT_H_ */
