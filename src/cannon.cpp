#include "pch.h"
using namespace std;

Bullet::Bullet(Cannon c, double angle)
	{
		x = c.x;
		y = c.y;
		vx =-sin(angle)*v;
		vy =cos(angle)*v;
		kind = c.kind;
		loadimage(&img, _T("img\\bullet1.png"),0,0,true);
		rotateimage(&img, &img, angle, BLACK, true, true);
	}

bool Bullet::in_canvas() {
	if (x + vx * t <= 20 || y - vy * t <= 20 || x + vx * t >= CANVAS_LENGTH - 20) return false;
	return true;
}

void Bullet::move() {
	x += vx * t;
	y -= vy * t;
}

void Bullet::show()
{
	transparentimage(NULL, x, y, &img, BLACK);
}

void Cannon::init()
{
	loadAlpha(&img, _T("img\\cannon1.png"), 0, 0, true);
	loadAlpha(&minus, _T("img\\minus.png"), 0, 0, true);
	loadAlpha(&plus, _T("img\\plus.png"), 0, 0, true);
	b_length = minus.getwidth();
	b_width = minus.getheight();
	nowimg = img;
	length = img.getwidth();
	width = img.getheight();
	angle = 0;
	x = CANVAS_LENGTH/2;
	y = CANVAS_WIDTH -  width;
	kind = 1;
	cost = 1;
}

void Cannon::show()
{
	transparentimage(NULL, x - length / 2, y - width / 2, &nowimg, BLACK);
	drawAlpha(&minus,x - b_length*3, y );
	drawAlpha(&plus, x + b_length*2, y);
}

void Cannon::rotate(MOUSEMSG &m)
{
	if (m.y >= y) angle = 0;
	else angle = atan((double)(m.x - x) / (m.y - y));
	rotateimage(&nowimg, &img, angle, BLACK, true, true);
	length = nowimg.getwidth();
	width = nowimg.getheight();
}

void Cannon::fire()
{
	bullets.emplace_back(Bullet(*this, angle));
}

void Cannon::show_bullets()
{
	if(!bullets.empty())
	for (auto i = bullets.begin(); i != bullets.end();) {
		if (!(*i).in_canvas()) {
			i = bullets.erase(i);
		}
		else {
			(*i).move();
			(*i).show();
			i++;
		}
	}
}

void Cannon::clear() {
	bullets.clear();
}

int Cannon::update(MOUSEMSG &m) {
	int b=0;
	if (m.x >= x - b_length*3 && m.x <= x - b_length*2 && m.y >= y && m.y <= y + b_width) b = -1;
	else if (m.x >= x + b_length*2 && m.x <= x + b_length*3 && m.y >= y && m.y <= y + b_width) b = 1;
	if (b==1) {
		switch (kind) {
		case 1:
			loadAlpha(&img, _T("img\\cannon2.png"), 0, 0, true);
			kind = 2;
			cost = 2;
			break;
		case 2:
			loadAlpha(&img, _T("img\\cannon3.png"), 0, 0, true);
			kind = 3;
			cost = 3;
			break;
		case 3:
			loadAlpha(&img, _T("img\\cannon1.png"), 0, 0, true);
			kind = 1;
			cost = 1;
			break;
		}
	}
	else if (b==-1){
		switch (kind) {
		case 1:
			loadAlpha(&img, _T("img\\cannon3.png"), 0, 0, true);
			kind = 3;
			cost = 3;
			break;
		case 2:
			loadAlpha(&img, _T("img\\cannon1.png"), 0, 0, true);
			kind = 1;
			cost = 1;
			break;
		case 3:
			loadAlpha(&img, _T("img\\cannon2.png"), 0, 0, true);
			kind = 2;
			cost = 2;
			break;
		}
	}
	if (b == 0) return 0;
	else return 1;
}

void web::create(Bullet b) {
	switch (b.kind) {
	case 1:
		loadimage(&img, _T("img\\web.png"), 80, 80, false);
		r = 40;
		break;
	case 2:
		loadimage(&img, _T("img\\web.png"), 100, 100, false);
		r = 50;
		break;
	case 3:
		loadimage(&img, _T("img\\web.png"), 120, 120, false);
		r = 60;
		break;
	}
	loadimage(&explode, _T("img\\explode.png"), 60, 60, false);
	loadimage(&gold, _T("img\\gold.png"), 60, 60, false);
	center.x = b.x;
	center.y = b.y;
	is_show = false;
	is_bomb = false;
	is_gold = false;
}

void web::show() {
	if(is_bomb==true) transparentimage(NULL, center.x - 30, center.y - 30, &explode, BLACK);
	transparentimage(NULL, center.x - r, center.y - r, &img, BLACK);
	if(is_gold) transparentimage(NULL, center.x + g_vx * time, center.y - g_vy * time, &gold, BLACK);
}
