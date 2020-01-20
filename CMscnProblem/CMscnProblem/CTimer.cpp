#include  "CTimer.h"

CTimer::CTimer() {
}

void CTimer::vSetStartNow(){
	QueryPerformanceFrequency(&li_freq);
	QueryPerformanceCounter(&li_start);
}


void CTimer::vSetTimePassed(double *pdTimePassed){
	LARGE_INTEGER li_now;
	QueryPerformanceCounter(&li_now);

	double  d_result;

	d_result = (li_now.QuadPart - li_start.QuadPart);
	d_result = d_result / li_freq.QuadPart;

	*pdTimePassed = d_result;
}






