/*
 FILE: achievement.h/cpp
 FUNCTION: create a fish-collection system
 COPYRIGHT: Evergrow Hook
*/
#pragma once
class fish_collect {
public://variables
	IMAGE img;//the image of the kind of fish
	int kind;//the kind of fish of the system
	int num;//the number of the kind of fish which have been caught
	int x, y;//the location of the system
public://functions
	void init(int i);//init the fish-collection system
	void update();//update the fish-collection system
	void show();//show the fish-collection system
};
