/*
 FILE: pch.h/cpp
 FUNCTION: store the used headers in it(which is needed in visual studio)
 COPYRIGHT: Evergrow Hook
*/
#ifndef PCH_H
#define PCH_H

// TODO: 添加要在此处预编译的标头

//------------------headers-------------------
#include <iostream>
#include<Windows.h>
#include<stdio.h>
#include<easyx.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<deque>
#include <mmsystem.h>
#include "fish.h"
#include "collision.h"
#include "cannon.h"
#include "background.h"
#include "score.h"
#include "achievement.h"

//----------------definitions------------------
#define t 1.5//proportion of velocity
#define PI 3.14//value of pi
#define rad *PI/180//convert from degree to rad
#define CANVAS_WIDTH 480
#define CANVAS_LENGTH 640//size of the canvas
#define SCORE_INIT 50//the initial score
#define KIND 5//how many kinds of fish

//---------------other orders------------------
using namespace std;
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")//use this for the playsound function

#endif //PCH_H
