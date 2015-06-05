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

#include "Logger.h"
#include "StringUtil.h"
#include "Plugin.h"
#include "Environment.h"

#include <chrono>
#include <iostream>
#include <ctime>
#include <mutex>
#include <exception>
#include <cstring>

using namespace std;
using namespace StringUtil;

namespace FreeAX25 {

static constexpr const char* LEVELS[] = {
	"NONE  ",
	"ERROR ",
	"WARN  ",
	"INFO  ",
	"DEBUG ",
	nullptr
};

// Used to synchronize log writes
static mutex mx;

/**
 * Plugin initialize.
 * @param e The environment struct
 * @param p The plugin struct
 */
void initLogger(Plugin& p) {
	environment.logInfo("Init plugin \"" + p.getName() + "\"");
	environment.logger.init(p);
}

/**
 * Plugin start.
 */
void startLogger() {
	environment.logInfo("Start plugin \"/_LOGGER\"");
	environment.logger.start();
}

Logger::Logger() {
	// Be prepared for threaded output:
	cerr.sync_with_stdio(true);
}

Logger::~Logger() {
}

/**
 * Plugin init
 * @param p Plugin data structure
 */
void Logger::init(Plugin& p) {
	string level = Setting::asStringValue(p.settings, "level", "NONE");
	m_level = decode(level);
	logInfo("Log level set to " + level);
}

/**
 * LogLevel is already checked here.
 */
void Logger::_log(LogLevel l, const string& msg) {
	auto now = chrono::system_clock::now();
	auto now_c = chrono::system_clock::to_time_t(now);

	constexpr size_t S_BUF = 32;
	char buf[S_BUF];
	strftime(buf, S_BUF, "%F %T ", localtime(&now_c));

	lock_guard<mutex> lock(mx);
	cerr << buf << LEVELS[static_cast<int>(l)] << msg << endl;
}

/**
 * Decode a textual representation of a log level. Throws exception, when
 * no match.
 * @param s The text to decode
 * @return Corresponding log level
 */
LogLevel Logger::decode(const string& s) {
	for (int i = 0; LEVELS[i] != nullptr; ++i)
		if (strcmp(s.c_str(), rTrim(LEVELS[i]).c_str()) == 0)
			return static_cast<LogLevel>(i);
	throw invalid_argument("Log level \"" + s + "\"");
}

} /* namespace FreeAX25 */
