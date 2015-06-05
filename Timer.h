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

#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <mutex>
#include <map>
#include <atomic>

namespace FreeAX25 {

class TimerManager;

class Timer {
	friend class TimerManager;

public:
	/**
	 * Create a new Timer. The timer is not started.
	 * @param id Id of this Timer. Mainly for debugging
	 * @param d  How long this timer normally should run after started.
	 *           This can be overridden in the start() or restart()
	 *           method.
	 * @param f  The function object to call when the timer expires.
	 *           Usually this is a lambda.
	 */
	Timer(	const std::string& id,
			const std::chrono::steady_clock::duration& d,
			std::function<void()> f);

	/**
	 * A Timer can not be copied.
	 * @param other Not used.
	 */
	Timer(const Timer& other) = delete;

	/**
	 * A Timer can not be moved.
	 * @param other Not used.
	 */
	Timer(Timer&& other) = delete;

	/**
	 * Destructor. Stops timer, if necessary.
	 */
	~Timer();

	/**
	 * You can not assign a timer.
	 * @param other Not used.
	 * @return Not used.
	 */
	Timer& operator=(const Timer& other) = delete;

	/**
	 * You can not assign a timer.
	 * @param other Not used.
	 * @return Not used.
	 */
	Timer& operator=(Timer&& other) = delete;

	/**
	 * Start the timer
	 * @param d The duration this timer should run
	 */
	void start(const std::chrono::steady_clock::duration& d) {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_running) _stop();
		_start(d);
	}

	/**
	 * Start the timer with the standard duration
	 */
	void start() {
		start(m_stdDuration);
	}

	/**
	 * Stop the timer
	 */
	void stop() {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_running) _stop();
	}

	/**
	 * Restart the timer
	 * @param d The duration this timer should run
	 */
	void restart(const std::chrono::steady_clock::duration& d) {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_running) _stop();
		_start(d);
	}

	/**
	 * Restart the timer with the standard duration
	 */
	void restart() {
		restart(m_stdDuration);
	}

	/**
	 * Get the standard duration
	 * @return Standard duration
	 */
	std::chrono::steady_clock::duration getStdDuration() const {
		return m_stdDuration;
	}

	/**
	 * Test if the timer is running
	 * @return If the timer is running
	 */
	bool isRunning() {
		return m_running;
	}

private:
	const std::string                     m_id;
	std::chrono::steady_clock::duration   m_stdDuration;
	std::function<void()>                 m_function;
	std::multimap<std::chrono::steady_clock::time_point, Timer&>::iterator
	                                      m_iterator;
	std::atomic<bool>                     m_running{false};
	std::mutex                            m_mutex{};
	std::chrono::steady_clock::time_point m_deadline{};
	// Unprotected by mutex:
	void _start(const std::chrono::steady_clock::duration& d);
	void _stop();
};

} /* namespace FreeAX25 */

#endif /* TIMER_H_ */
