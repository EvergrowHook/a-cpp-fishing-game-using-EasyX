#ifndef PCH_H
#define PCH_H

// TODO: 添加要在此处预编译的标头
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
#define t 1.5
#define PI 3.14
#define rad *PI/180
#define CANVAS_WIDTH 480
#define CANVAS_LENGTH 640//size of the canvas
#define SCORE_INIT 50
#define KIND 5
using namespace std;
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

#endif //PCH_H
