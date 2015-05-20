/*
 * Timer.cpp
 *
 *  Created on: 17.05.2015
 *      Author: tania
 */

#include "Timer.h"
#include "TimerManager.h"
#include "Environment.h"

#include <cassert>

namespace FreeAX25 {

using namespace std;
using namespace std::chrono;

Timer::Timer(Environment* e,
		const std::string& id,
		const std::chrono::steady_clock::duration& d,
		std::function<void()> f) :
	m_environment{e},
	m_id{id},
	m_stdDuration{d},
	m_function{f},
	m_manager{e->getTimerManager()},
	m_iterator{m_manager->m_activeTimers.end()}
{
	assert(f != nullptr);
}

Timer::~Timer() {
	lock_guard<mutex> lock(m_mutex);
	if (m_running) _stop();
}

void Timer::_start(const steady_clock::duration& d) {
	//m_environment->logDebug("Start timer " + m_id);
	// Lock the manager:
	lock_guard<mutex> lock(m_manager->m_mutex);
	assert(m_iterator == m_manager->m_activeTimers.end());
	m_deadline = steady_clock::now() + d;
	m_iterator = m_manager->m_activeTimers.insert(
			pair<steady_clock::time_point, Timer*>(m_deadline, this));
	m_running = true;
}

void Timer::_stop() {
	//m_environment->logDebug("Stop timer " + m_id);
	// Lock the manager:
	lock_guard<mutex> lock(m_manager->m_mutex);
	m_running = false;
	if (m_iterator != m_manager->m_activeTimers.end()) return;
	m_manager->m_activeTimers.erase(m_iterator);
	m_iterator = m_manager->m_activeTimers.end();
}

} /* namespace FreeAX25 */
