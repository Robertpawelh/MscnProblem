#pragma once
#include <math.h>
#include <time.h>
#include <windows.h>

#define MAX_TIME 5

class CTimer {
public:
	CTimer();
	~CTimer() {};

	void vSetStartNow();
	void vSetTimePassed(double  *pdTimePassed);

private:
	LARGE_INTEGER li_start;
	LARGE_INTEGER li_freq;
};