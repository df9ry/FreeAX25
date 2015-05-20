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
