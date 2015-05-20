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

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

namespace FreeAX25 {

class Environment;
class Plugin;

/**
 * Specifies the weight of a log message.
 */
enum class LogLevel {
	NONE,
	ERROR,
	WARNING,
	INFO,
	DEBUG
};

/**
 * Plugin initialize.
 * @param e The environment struct
 * @param p The plugin struct
 */
void initLogger(Environment* e, Plugin* p);

/**
 * Plugin start.
 */
void startLogger();

class Logger {
public:

	/**
	 * Constructor
	 * @param e Global environment
	 */
	Logger(Environment* e);

	/**
	 * Destructor
	 */
	~Logger();

	/**
	 * Initialize the Logger
	 * @param p Plugin data structure
	 */
	void init(Plugin* p);

	/**
	 * Start the Logger
	 */
	void start() {}

	/**
	 * Set the log level
	 */
	inline void setLevel(LogLevel l) {
		m_level = l;
	}

	/**
	 * Get the log level
	 */
	inline LogLevel getLevel() const {
		return m_level;
	}

	/**
	 * Log an error
	 */
	inline void logError(const std::string& msg) {
		log(LogLevel::ERROR, msg);
	}

	/**
	 * Log a warning
	 */
	inline void logWarning(const std::string& msg) {
		log(LogLevel::WARNING, msg);
	}

	/**
	 * Log an info
	 */
	inline void logInfo(const std::string& msg) {
		log(LogLevel::INFO, msg);
	}

	/**
	 * Log a debug
	 */
	inline void logDebug(const std::string& msg) {
		log(LogLevel::DEBUG, msg);
	}

	/**
	 * Write to log
	 */
	inline void log(LogLevel l, const std::string& msg) {
		if (l <= m_level) _log(l, msg);
	}

	/**
	 * Returns a log level corresponding to given string s. Throws
	 * exception when no log level matches.
	 * @param s The textual log level
	 * @return The decoded log level
	 */
	static LogLevel decode(const std::string& s);

private:
	Environment* m_environment;
	LogLevel     m_level{LogLevel::NONE};
	void _log(LogLevel l, const std::string& msg);
};

} /* namespace FreeAX25 */

#endif /* LOGGER_H_ */
