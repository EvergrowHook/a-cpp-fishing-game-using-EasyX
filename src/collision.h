/*
 FILE: collision.h/cpp
 FUNCTION: define the functions and classes used for detecting collisions
 COPYRIGHT: Evergrow Hook
*/
#pragma once
class Bullet;
class web;
class obb {
public://variables
	fish f;//the fish orbited by the obb rectangle
	POINT center;//the center point of an obb rectangle
	POINT point[4];//the corners of an obb rectangle
	int angle;//the bank angle of an obb rectangle
	int length, width;//the size of an obb rectangle
	double radius;//the radius of the circumcircle of an obb rectangle
	bool is_collision;//judge if a fish has a collision
public://functions
	void init();//create an obb rectangle orbiting a fish
	void update();//update an obb rectangle
	void show();//show an obb rectangle
};

double distance(POINT a, POINT b);//calculate the distance between two points

double line_dst(POINT a, POINT p, POINT q);//calculate the distance between a line and a point

int dotmul(POINT origin, POINT p, POINT q);//calculate the dot multiply of two segments

bool collision(obb a, web b);//judge if a web has caught a fish

bool in_obb(obb a, Bullet b);//judge if a bullet has hit a fish
