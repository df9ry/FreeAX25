/*
 * TimerManager.h
 *
 *  Created on: 17.05.2015
 *      Author: tania
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
