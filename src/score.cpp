/*
 FILE: score.h/cpp
 FUNCTION: create and update the score board
 COPYRIGHT: Evergrow Hook
*/
#include "pch.h"

//init the score board
void score::init() {
	num = SCORE_INIT;
}

//update and show the score board
void score::show() {
	createbutton(578, 622, 18, 32, 10, _T("得分"));
	createbutton(578, 622, 38, 52, 10, _T(""));
	puttextxy(580, 40, num);
	settextstyle(20, 0, _T("黑体"));
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
