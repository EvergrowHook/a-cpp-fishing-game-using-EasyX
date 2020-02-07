/*
 FILE: score.h/cpp
 FUNCTION: create and update the score board
 COPYRIGHT: Evergrow Hook
*/
#pragma once
class score {
public://variables
	int num;//the score
	int numtmp=0;//the temporary change of score caused by what a web catches
public://functions
	void init();//init the score board
	void show();//update and show the score board
};
