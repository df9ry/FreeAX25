/*
 * Environment.cpp
 *
 *  Created on: 17.05.2015
 *      Author: tania
 */

#include "Environment.h"

#include <cstdlib>

namespace FreeAX25 {

using namespace std;

Environment::Environment():
		m_logger{new Logger(this)},
		m_timerManager{new TimerManager(this)},
		m_configuration{new Configuration(this)}
{
	const char* _debug = getenv("LOG_LEVEL");
	try {
		getLogger()->setLevel(
				(_debug != nullptr) ? Logger::decode(_debug) : LogLevel::NONE);
	}
	catch (...) {
		// Ignore any errors
	}
}

Environment::~Environment() {
}

} /* namespace FreeAX25 */
