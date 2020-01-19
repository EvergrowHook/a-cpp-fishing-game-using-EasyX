#include "pch.h"
void fish_collect::init(int i) {
	kind = i;
	switch (kind) {
	case 1:
		loadimage(&img, _T("img\\fish1.png"), 80, 80, false);
		x = 110;
		y = 90;
		break;
	case 2:
		loadimage(&img, _T("img\\fish2.png"), 80, 80, false);
		x = 220;
		y = 90;
		break;
	case 3:
		loadimage(&img, _T("img\\fish3.png"), 80, 80, false);
		x = 330;
		y = 90;
		break;
	case 4:
		loadimage(&img, _T("img\\fish4.png"), 80, 80, false);
		x = 440;
		y = 90;
		break;
	case 5:
		loadimage(&img, _T("img\\fish5.png"), 80, 80, false);
		x = 110;
		y = 200;
		break;
	}
	num = 0;
}

void fish_collect::update() {
	num++;
}

void fish_collect::show() {
	putimage(x, y, &img);
	TCHAR ss[20];
	swprintf_s(ss, _T("x %d"), num);
	outtextxy(x, y + 85, ss);
}