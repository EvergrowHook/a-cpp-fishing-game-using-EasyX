/*
 FILE: cannon.h/cpp
 FUNCTION: create class bullet, cannon and web(which are all related to catching a fish)
 COPYRIGHT: Evergrow Hook
*/
#pragma once
using namespace std;
class Cannon;
class Bullet
{
public://variables
	IMAGE img;//image of a bullet
	int x, y;//the location of a bullet
	int kind;//the kind of a bullet(according to the size of the cannon)
	double v = 2;//velocity of bullets
	double vx, vy;//velocity on x and y axis
public://functions
	Bullet(Cannon c, double angle);//define a bullet's basic info
	bool in_canvas();//judge if a bullet is still in canvas
	void move();//calculate a bullet's movement in every loop
	void show();//show the image of a bullet
};

class Cannon
{
public://variables
	deque<Bullet> bullets;//the list of bullets of the cannon
	IMAGE img;//the image of the cannon
	IMAGE nowimg;//the real-time image of the cannon
	IMAGE minus, plus;//the '+' '-' button used to change the cannon's size
	int length,width;//the size of img
	int b_length, b_width;//the size of buttons
	int kind;//the size of the cannon
	int cost;//the cost for firing one bullet
	double angle;//the cannon's rotating angle
	int x, y;//the location of the cannon
public://functions
	void init();//define the cannon's basic info
	int update(MOUSEMSG &m);//update the cannon's size if click the '+' or '-' button
	void show();//show the images of the cannon
	void rotate(MOUSEMSG &m);//rotate the cannon according to the location of the mouse
	void fire();//create a new bullet when click
	void show_bullets();//update the bullets' status
	void clear();//remove all the bullets
};

class web {
public://variables
	POINT center;//the center of a web
	int r;//the radius of a web
	IMAGE img;//the image of a web
	IMAGE explode;//the image of a bomb exploding
	IMAGE gold;//the image of the gold coins
	int time;//the lasting time of a web
	int g_vx, g_vy;//the velocity of gold coins on x and y axis
	bool is_bomb;//mark if a bomb in a web
	bool is_show;//mark whether a web should be show
	bool is_gold;//mark whether gold coins should be show
public://functions
	void create(Bullet b);//create a web when a bullet hits a fish
	void show();//show a web
};
