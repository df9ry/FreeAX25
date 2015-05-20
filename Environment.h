/*
 * Environment.h
 *
 *  Created on: 17.05.2015
 *      Author: tania
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Logger.h"
#include "TimerManager.h"
#include "Configuration.h"

#include <memory>

namespace FreeAX25 {

/**
 * The class Environment provides a single distribution point
 * for "global" data structures.
 */
class Environment {
public:
	Environment();
	~Environment();

	/**
	 * Get the Logger object
	 * @return Logger
	 */
	inline Logger* getLogger() {
		return m_logger.get();
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
		return m_timerManager.get();
	}

	/**
	 * Get the Configuration object
	 * @return Configuration
	 */
	inline Configuration* getConfiguration() {
		return m_configuration.get();
	}

private:
	std::unique_ptr<Logger>        m_logger;
	std::unique_ptr<TimerManager>  m_timerManager;
	std::unique_ptr<Configuration> m_configuration;
};

} /* namespace FreeAX25 */

#endif /* ENVIRONMENT_H_ */
