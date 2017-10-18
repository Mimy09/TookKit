// ################################################################## //
// ##							Timer							   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 Sep 5 - AIE			   ## //
// ################################################################## //
#pragma once
_BPD_BEGIN
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

	bool StopWatch(float time);

private:
    double m_frequency;
    __int64 m_startTime;
    bool m_isHighPerformance;
    bool m_running;

	int m_fps;
	int m_frames;

	double m_timePassed;
	double m_timePassed_fps;
	double m_timePassed_sw;

};
_BPD_END