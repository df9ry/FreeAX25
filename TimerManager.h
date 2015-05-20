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

#include <map>
#include <chrono>
#include <mutex>
#include <memory>
#include <atomic>
#include <thread>

namespace FreeAX25 {

class Timer;
class Plugin;

/**
 * Plugin initialize.
 * @param e The environment struct
 * @param p The plugin struct
 */
void initTimerManager(Environment* e, Plugin* p);

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
	 * @param e Global environment
	 */
	TimerManager(Environment* e);

	/**
	 * Destructor
	 */
	~TimerManager();

	/**
	 * Initialize the TimerManager
	 * @param p Plugin data structure
	 */
	void init(Plugin* p);

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
	Environment*                          m_environment;
	std::multimap<std::chrono::steady_clock::time_point, Timer*>
					                      m_activeTimers{};
	std::mutex		                      m_mutex{};
	std::chrono::steady_clock::time_point m_nextPoll{};
	std::atomic<bool>                     m_terminate{false};
	std::thread                           m_thread{};
	Plugin*                               m_plugin{};
	std::chrono::steady_clock::duration   m_tick{std::chrono::milliseconds{100}};
};

} /* namespace FreeAX25 */

#endif /* TIMERMANAGER_H_ */
