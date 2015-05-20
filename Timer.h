/*
 * Timer.h
 *
 *  Created on: 17.05.2015
 *      Author: tania
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <mutex>
#include <map>
#include <atomic>

namespace FreeAX25 {

class Environment;
class TimerManager;

class Timer {
	friend class TimerManager;
public:

	/**
	 * Create a new Timer. The timer is not started.
	 * @param e  Environment object
	 * @param id Id of this Timer. Mainly for debugging
	 * @param d  How long this timer normally should run after started.
	 *           This can be overridden in the start() or restart()
	 *           method.
	 * @param f  The function object to call when the timer expires.
	 *           Usually this is a lambda.
	 */
	Timer(	Environment* e,
			const std::string& id,
			const std::chrono::steady_clock::duration& d,
			std::function<void()> f);

	/**
	 * Destructor. Stops timer, if necessary.
	 */
	~Timer();

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
	Environment*                          m_environment;
	const std::string                     m_id;
	std::chrono::steady_clock::duration   m_stdDuration;
	std::function<void()>                 m_function;
	TimerManager*                         m_manager;
	std::multimap<std::chrono::steady_clock::time_point, Timer*>::iterator
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
