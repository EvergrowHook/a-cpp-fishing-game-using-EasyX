#include "pch.h"

void obb::init() {
	length = f.length;
	width = f.width;
	radius = sqrt(pow(length / 2, 2) + pow(width / 2, 2));
	angle = f.angle;
	is_collision = false;
}

void obb::update() {
	center.x = f.x;
	center.y = f.y;
	point[0].x = f.x + f.length*cos(PI*f.angle / 180) / 2 - f.width*sin(PI*f.angle / 180) / 2;
	point[0].y = f.y - f.length*sin(PI*f.angle / 180) / 2 - f.width*cos(PI*f.angle / 180) / 2;
	point[1].x = f.x - f.length*cos(PI*f.angle / 180) / 2 - f.width*sin(PI*f.angle / 180) / 2;
	point[1].y = f.y + f.length*sin(PI*f.angle / 180) / 2 - f.width*cos(PI*f.angle / 180) / 2;
	point[2].x = f.x - f.length*cos(PI*f.angle / 180) / 2 + f.width*sin(PI*f.angle / 180) / 2;
	point[2].y = f.y + f.length*sin(PI*f.angle / 180) / 2 + f.width*cos(PI*f.angle / 180) / 2;
	point[3].x = f.x + f.length*cos(PI*f.angle / 180) / 2 + f.width*sin(PI*f.angle / 180) / 2;
	point[3].y = f.y - f.length*sin(PI*f.angle / 180) / 2 + f.width*cos(PI*f.angle / 180) / 2;
	angle = f.angle;
}

void obb::show() {
	polygon(point, 4);
	settextcolor(GREEN);
	settextstyle(15, 0, _T("黑体"));
	puttextxy(center.x, center.y, (int)is_collision);
}

double distance(POINT a, POINT b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double line_dst(POINT a, POINT p, POINT q) {
	//the distance of point a to line bc
	if (q.x == p.x) {
		return abs(a.x - p.x);
	}
	else {
		//y=kx+b kx-y+b=0
		double k, b;
		k = (double)(q.y - p.y) / (q.x - p.x);
		b = q.y - k * q.x;
		return abs((k*a.x - a.y + b) / (sqrt(pow(k, 2) + 1)));
	}
}

int dotmul(POINT origin, POINT p, POINT q) {
	int x1, x2, y1, y2;
	x1 = p.x - origin.x;
	x2 = q.x - origin.x;
	y1 = p.y - origin.y;
	y2 = q.y - origin.y;
	return x1 * x2 + y1 * y2;
}

bool collision(obb a, web b) {
	//球心投影到矩形的两根轴上的点与矩形中心的距离<length/2||width/2+r
	if (distance(a.center, b.center) > a.radius + b.r) return false;
	POINT axis_l, axis_w;
	axis_l.x = a.center.x + cos(PI*a.angle / 180)*a.length / 2;
	axis_l.y = a.center.y - sin(PI*a.angle / 180)*a.length / 2;
	axis_w.x = a.center.x - sin(PI*a.angle / 180)*a.width / 2;
	axis_w.y = a.center.y - cos(PI*a.angle / 180)*a.width / 2;
	if (abs(dotmul(a.center, axis_l, b.center) / (a.length / 2)) > a.length / 2 + b.r) return false;
	if (abs(dotmul(a.center, axis_w, b.center) / (a.width / 2)) > a.width / 2 + b.r) return false;
	return true;
}

bool in_obb(obb a, Bullet b) {
	double d1, d2, d3, d4;
	POINT bullet;
	bullet.x = b.x;
	bullet.y = b.y;
	d1 = line_dst(bullet, a.point[0], a.point[1]);
	d2 = line_dst(bullet, a.point[1], a.point[2]);
	d3 = line_dst(bullet, a.point[2], a.point[3]);
	d4 = line_dst(bullet, a.point[3], a.point[0]);
	if (d1 <= a.width&&d2 <= a.length&&d3 <= a.width&&d4 <= a.length) return true;
	return false;
}