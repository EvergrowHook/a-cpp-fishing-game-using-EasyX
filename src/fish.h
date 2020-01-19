#pragma once
class fish_collect;
class fish {
public://variables
	IMAGE img;//store the original picture of the fish in it
	IMAGE nowimg;//store the picture to show
	IMAGE deathimg;
	int state;//0:dead 1:swim 2:out of canvas
	int kind;//the kind of the fish
	int length, width;//size of the picture of the fish
	int nowlength, nowwidth;
	int x, y;//location of the picture
	double value;
	double v;//velocity
	int angle;//to change the moving route a little
public://functions
	fish();
	bool in_canvas();
	void init();//create a new object, load image and set basic info
	void emerge();//let the new object appear on the canvas
	void move();//let the fish move
	void show();
	bool is_dead(int cost);
	void dead(fish_collect *fc);
};