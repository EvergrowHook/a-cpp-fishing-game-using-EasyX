/*
 FILE: fish.h/cpp
 FUNCTION: create class fish, and define fish's action and characteristic in it
 COPYRIGHT: Evergrow Hook
 */
#pragma once
class fish_collect;
class fish {
public://variables
	IMAGE img;//store the original picture of the fish in it
	IMAGE nowimg;//store the picture to show
	int state;//0:dead 1:swim 2:out of canvas   now unused
	int kind;//the kind of the fish
	int length, width;//size of img
	int nowlength, nowwidth;//size of nowimg
	int x, y;//location of the picture
	double value;//the value of the fish
	double v;//velocity
	int angle;//to change the moving route a little
public://functions
	fish();//define fish's kind when a new fish is created
	bool in_canvas();//judge if a fish is still in the canvas
	void init();//init a fish's basic info
	void emerge();//decide the location where a fish would emerge
	void move();//calculate a fish's movement in every loop
	void show();//show a fish's real-time image on canvas
	bool is_dead(int cost);//judge if a fish is dead
	void dead(fish_collect *fc);//update the fish-collecting system when a fish is dead
};
