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
#include "TimerManager.h"
#include "Timer.h"
#include "Plugin.h"
#include "Setting.h"

#include <exception>
#include <string>

namespace FreeAX25 {

using namespace std;
using namespace std::chrono;

TimerManager::TimerManager() {
}

TimerManager::~TimerManager() {
	terminate();
}

/**
 * Plugin initialize.
 * @param e The environment struct
 * @param p The plugin struct
 */
void initTimerManager(Plugin& p) {
	environment.logInfo(string("Init plugin \"/_TIMER\""));
	environment.timerManager.init(p);
}

/**
 * Plugin start.
 */
void startTimerManager() {
	environment.logInfo(string("Init plugin \"/_TIMER\""));
	environment.timerManager.start();
}

/**
 * Plugin init
 * @param p Plugin data structure
 */
void TimerManager::init(Plugin& p) {
	int tick = Setting::asIntValue(p.settings, "tick", 100);
	m_tick = milliseconds{tick};
	environment.logInfo("Tick set to " + to_string(tick) + "ms");
}

/**
 * Run the timer thread
 */
void TimerManager::start() {
	environment.logInfo(string("Start plugin \"/_TIMER\""));
	std::thread _t{&TimerManager::_run, this};
	m_thread = std::move(_t);
}

void TimerManager::_run() {
	environment.logInfo(string("Timer thread running"));
	m_nextPoll = steady_clock::now();
	while (!m_terminate) {
		while (!m_terminate) {
			try {
				// The function to call:
				function<void()> callback{nullptr};
				{ // begin protected block //
					// Lock the manager:
					lock_guard<mutex> lock1(m_mutex);
					auto head = m_activeTimers.begin();
					// If not more to do, exit inner loop:
					if ((head == m_activeTimers.end()) ||
							(head->first > m_nextPoll))
						break;
					// Ok, this timer is ripe:
					Timer& timer = head->second;
					lock_guard<mutex> lock2(timer.m_mutex);
					callback = timer.m_function;
					timer.m_running = false;
					m_activeTimers.erase(head);
					timer.m_iterator = m_activeTimers.end();
				} // end protected block //
				// Here we are not longer locked
				callback();
			}
			catch (const exception& ex) {
				environment.logError(
						string("Timer callback with exception: ") +
						ex.what());
			}
			catch (...) {
				environment.logError(
						string("Timer callback with unknown exception"));
			}
		} // end while //
		// Nothing more left, sleep to next poll:
		m_nextPoll += m_tick;
		this_thread::sleep_until(m_nextPoll);
	} // end while //
	environment.logInfo(string("Timer thread stopping"));
}

} /* namespace FreeAX25 */
