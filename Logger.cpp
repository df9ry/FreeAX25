/*
 * Logger.cpp
 *
 *  Created on: 16.05.2015
 *      Author: tania
 */

#include "Logger.h"
#include "Utils.h"
#include "Plugin.h"
#include "Environment.h"

#include <chrono>
#include <iostream>
#include <ctime>
#include <mutex>
#include <exception>
#include <cstring>

using namespace std;

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
// The one and only instance
static Logger* instance{nullptr};

/**
 * Plugin initialize.
 * @param e The environment struct
 * @param p The plugin struct
 */
void initLogger(Environment* e, Plugin* p) {
	e->logInfo("Init plugin \"" + p->getName() + "\"");
	if (instance == nullptr) throw runtime_error(
			"Logger not instantiated");
	instance->init(p);
}

/**
 * Plugin start.
 */
void startLogger() {
	if (instance == nullptr) throw runtime_error(
			"Logger not instantiated");
	instance->logInfo("Start plugin \"/_LOGGER\"");
	instance->start();
}

Logger::Logger(Environment* e): m_environment{e} {
	// Be prepared for threaded output:
	cerr.sync_with_stdio(true);
	if (instance != nullptr) throw runtime_error(
			"Logger already instantiated");
	instance = this;
}

Logger::~Logger() {
}

/**
 * Plugin init
 * @param p Plugin data structure
 */
void Logger::init(Plugin* p) {
	string level = Setting::asString(p->settings, "level", "NONE");
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
		if (strcmp(s.c_str(), Utils::rtrim(LEVELS[i]).c_str()) == 0)
			return static_cast<LogLevel>(i);
	throw invalid_argument("Log level \"" + s + "\"");
}

} /* namespace FreeAX25 */
