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

#include <exception>

namespace FreeAX25 {

using namespace std;
using namespace std::chrono;

static TimerManager* instance{nullptr};

TimerManager::TimerManager(Environment* e): m_environment{e} {
	if (instance != nullptr) throw runtime_error(
			"TimerManager already instantiated");
	instance = this;
}

TimerManager::~TimerManager() {
	terminate();
}

/**
 * Plugin initialize.
 * @param e The environment struct
 * @param p The plugin struct
 */
void initTimerManager(Environment* e, Plugin* p) {
	e->logInfo("Init plugin \"" + p->getName() + "\"");
	if (instance == nullptr) throw runtime_error(
			"TimerManager not instantiated");
	instance->init(p);
}

/**
 * Plugin start.
 */
void startTimerManager() {
	if (instance == nullptr) throw runtime_error(
			"TimerManager not instantiated");
	instance->start();
}

/**
 * Plugin init
 * @param p Plugin data structure
 */
void TimerManager::init(Plugin* p) {
	int tick = Setting::asInt(p->settings, "tick", 100);
	m_tick = milliseconds{tick};
	m_environment->logInfo("Tick set to " + to_string(tick) + "ms");
}

/**
 * Run the timer thread
 */
void TimerManager::start() {
	m_environment->logInfo("Start plugin \"/_TIMER\"");
	std::thread _t{&TimerManager::_run, this};
	m_thread = std::move(_t);
}

void TimerManager::_run() {
	m_environment->logInfo("Timer thread running");
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
					auto timer = head->second;
					lock_guard<mutex> lock2(timer->m_mutex);
					callback = timer->m_function;
					timer->m_running = false;
					m_activeTimers.erase(head);
					timer->m_iterator = m_activeTimers.end();
				} // end protected block //
				// Here we are not longer locked
				callback();
			}
			catch (const exception& ex) {
				m_environment->logError(
						string("Timer callback with exception: ") +
						ex.what());
			}
			catch (...) {
				m_environment->logError(
						"Timer callback with unknown exception");
			}
		} // end while //
		// Nothing more left, sleep to next poll:
		m_nextPoll += m_tick;
		this_thread::sleep_until(m_nextPoll);
	} // end while //
	m_environment->logInfo("Timer thread stopping");
}

} /* namespace FreeAX25 */
