#include "tkTimer.h"
#include <Windows.h>

namespace tk {
	Timer::Timer()
		: m_running(false), m_startTime(0), m_fps(0), m_frames(0), m_timePassed(0), m_timePassed_fps(0){
		LARGE_INTEGER ticksPerSec;
		m_isHighPerformance = QueryPerformanceFrequency(&ticksPerSec) == TRUE;
		m_frequency = 1.0 / (m_isHighPerformance ? ticksPerSec.QuadPart : 1000);
	}

	double tk::Timer::elapsed() const {
		if (m_running) {
			LONGLONG now;
			if (m_isHighPerformance) {
				LARGE_INTEGER qwTime;
				QueryPerformanceCounter(&qwTime);
				now = qwTime.QuadPart;
			}
			else {
				now = GetTickCount();
			}
			return (now - m_startTime) * m_frequency;
		}
		else {
			return 0.0;
		}
	}


	bool tk::Timer::running() const {
		return m_running;
	}

	void Timer::calcFPS() {
		m_frames++;
		if (elapsed() - m_timePassed >= 1.0) {
			m_fps = m_frames;
			m_frames = 0;
			m_timePassed = elapsed();
		}
	}

	bool Timer::SetFPS(const int FPS) {
		if (elapsed() - m_timePassed_fps >= 1.0 / (double)FPS) {
			m_timePassed_fps = elapsed();
			return true;
		} return false;
	}

	void tk::Timer::start() {
		m_running = true;

		if (m_isHighPerformance) {
			LARGE_INTEGER qwTime;
			QueryPerformanceCounter(&qwTime);
			m_startTime = qwTime.QuadPart;
		}
		else {
			m_startTime = GetTickCount();
		}
	}

	void tk::Timer::stop() {
		m_running = false;
	}

}