#pragma once
using namespace std;
class Cannon;
class Bullet
{
public:
	IMAGE img;
	int x, y;
	int kind;
	double v = 2;
	double vx, vy;
	Bullet(Cannon c, double angle);
	bool in_canvas();
	void move();
	void show();
};

class Cannon
{
public:
	deque<Bullet> bullets;
	IMAGE img;
	IMAGE nowimg;
	IMAGE minus, plus;
	int length,width;
	int b_length, b_width;
	int kind;
	int cost;
	double angle;
	int x, y;
	void init();
	int update(MOUSEMSG &m);
	void show();
	void rotate(MOUSEMSG &m);
	void fire();
	void show_bullets();
	void clear();
};

class web {
public:
	POINT center;
	int r;
	IMAGE img, explode, gold;
	int time;
	int g_vx, g_vy;
	bool is_bomb;
	bool is_show;
	bool is_gold;
	void create(Bullet b);
	void show();
};