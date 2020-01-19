#pragma once
class Bullet;
class web;
class obb {
public:
	fish f;
	POINT center;
	POINT point[4];
	int angle;
	int length, width;
	double radius;
	bool is_collision;
	void init();
	void update();
	void show();
};

double distance(POINT a, POINT b);

double line_dst(POINT a, POINT p, POINT q);

int dotmul(POINT origin, POINT p, POINT q);

bool collision(obb a, web b);

bool in_obb(obb a, Bullet b);