#include "pch.h"

void score::init() {
	num = SCORE_INIT;
}

void score::show() {
	createbutton(578, 622, 18, 32, 10, _T("µÃ·Ö"));
	createbutton(578, 622, 38, 52, 10, _T(""));
	puttextxy(580, 40, num);
	settextstyle(20, 0, _T("ºÚÌå"));
	settextcolor(YELLOW);
	if (numtmp >= 0) {
		outtextxy(570, 60, _T("+"));
		puttextxy(595, 60, numtmp);
	}
	else {
		outtextxy(570, 60, _T("-"));
		puttextxy(595, 60, -numtmp);
	}
}