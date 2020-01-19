#pragma once
class fish_collect {
public:
	IMAGE img;
	int kind;
	int num;
	int x, y;
	void init(int i);
	void update();
	void show();
};