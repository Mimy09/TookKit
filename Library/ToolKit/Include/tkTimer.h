#pragma once

namespace tk
{
    class Timer {
    public:

        Timer();

        void start();
        void stop();
        double elapsed() const;
        bool running() const;
        bool isHighPerformance() const;

		void calcFPS();
		bool SetFPS(const int FPS);
		int GetFPS() const { return m_fps; }

    private:
        double m_frequency;
        __int64 m_startTime;
        bool m_isHighPerformance;
        bool m_running;

		int m_fps;
		int m_frames;
		double m_timePassed;
		double m_timePassed_fps;
    };

} // namespace aie

