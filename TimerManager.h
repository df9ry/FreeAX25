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

#ifndef TIMERMANAGER_H_
#define TIMERMANAGER_H_

#include "Timer.h"
#include "Plugin.h"

#include <map>
#include <chrono>
#include <mutex>
#include <memory>
#include <atomic>
#include <thread>

namespace FreeAX25 {

/**
 * Plugin initialize.
 * @param e The environment struct
 * @param p The plugin struct
 */
void initTimerManager(const Plugin& p);

/**
 * Plugin start.
 */
void startTimerManager();

/**
 * The TimerManager supply the system heart beat.
 */
class TimerManager {
	friend class Timer;

public:
	/**
	 * Constructor
	 */
	TimerManager();

	/**
	 * You can not copy a TimerManager.
	 * @param other Not used.
	 */
	TimerManager(const TimerManager& other) = delete;

	/**
	 * You can not move a TimerManager.
	 * @param other Not used.
	 */
	TimerManager(TimerManager&& other) = delete;

	/**
	 * Destructor
	 */
	~TimerManager();

	/**
	 * You can not assign a TimerManager.
	 * @param other Not used.
	 * @return Not used.
	 */
	TimerManager& operator=(const TimerManager& other) = delete;

	/**
	 * You can not assign a TimerManager.
	 * @param other Not used.
	 * @return Not used.
	 */
	TimerManager& operator=(TimerManager&& other) = delete;

	/**
	 * Initialize the TimerManager
	 * @param p Plugin data structure
	 */
	void init(const Plugin& p);

	/**
	 * Run the timer thread
	 */
	void start();

	/**
	 * Terminate the timer thread
	 */
	void terminate() {
		m_terminate = true;
	}

	/**
	 * Wait for timer thread exit.
	 */
	void join() {
		if (m_thread.native_handle() != 0) m_thread.join();
	}

	/**
	 * Thread function, invoked by "run()". Do not call it directly!
	 */
	void _run();

private:
	std::multimap<std::chrono::steady_clock::time_point, Timer&>
					                      m_activeTimers{};
	std::mutex		                      m_mutex{};
	std::chrono::steady_clock::time_point m_nextPoll{};
	std::atomic<bool>                     m_terminate{false};
	std::thread                           m_thread{};
	std::chrono::steady_clock::duration   m_tick{std::chrono::milliseconds{100}};
};

} /* namespace FreeAX25 */

#endif /* TIMERMANAGER_H_ */
