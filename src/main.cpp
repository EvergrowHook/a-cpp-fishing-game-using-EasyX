/*
 FILE: main.cpp
 FUNCTION: the main loop
 COPYRIGHT: Evergrow Hook
*/
#include "pch.h"

//some environment configrations
void sysinit() {
	srand((unsigned)time(NULL));
	initgraph(CANVAS_LENGTH, CANVAS_WIDTH, NOMINIMIZE);
	setbkmode(TRANSPARENT);
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, _T("捕鱼达人"));
	cleardevice();
}

//main
int main() {
	//---------------init----------------
	sysinit();
	//--------variable definitions-------
	IMAGE bk, bk2;
	MOUSEMSG m;
	deque<obb> o;
	deque<web> w;
	score s;
	fish_collect fc[KIND+1];
	Cannon c;
	DWORD start, stop;
	int game_state = 0, time = 0, numtmp;
	bool is_grass, is_bomb;
	RECT r;
	//-------------main loop-------------
	while (1) {
		switch (game_state) {
		case 0://开始界面 the starting interface
			//some initialization
			s.init();
			for (int i = 1; i <= KIND; i++) fc[i].init(i);
			c.clear();
			o.clear();
			PlaySound(_T("wave\\bgm1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			//loop
			while (game_state == 0) {
				//draw the interface
				BeginBatchDraw();
				loadimage(&bk, _T("img\\background2.jpg"), CANVAS_LENGTH, CANVAS_WIDTH);
				putimage(0, 0, &bk);
				setheadline(CANVAS_LENGTH / 2 - 80, CANVAS_WIDTH / 2 - 60, 40, _T("捕鱼达人"));
				createbutton(CANVAS_LENGTH / 2 - 25, CANVAS_LENGTH / 2 + 25, CANVAS_WIDTH / 2 + 40, CANVAS_WIDTH / 2 + 60, 10, _T("开始游戏"));
				createbutton(CANVAS_LENGTH / 2 - 25, CANVAS_LENGTH / 2 + 25, CANVAS_WIDTH / 2 + 70, CANVAS_WIDTH / 2 + 90, 10, _T("退出游戏"));
				createbutton(CANVAS_LENGTH / 2 - 25, CANVAS_LENGTH / 2 + 25, CANVAS_WIDTH / 2 + 100, CANVAS_WIDTH / 2 + 120, 10, _T("游戏帮助"));
				EndBatchDraw();
				//judge if game state should be changed
				if (MouseHit()) {
					m = GetMouseMsg();
					//if click "begin game"
					if (m.uMsg == WM_LBUTTONDOWN && m.x >= CANVAS_LENGTH / 2 - 25 && m.x <= CANVAS_LENGTH / 2 + 25 && m.y >= CANVAS_WIDTH / 2 + 40 && m.y <= CANVAS_WIDTH / 2 + 60) {
						PlaySound(NULL, NULL, SND_FILENAME);
						PlaySound(_T("wave\\menu.wav"), NULL, SND_FILENAME | SND_SYNC);
						c.init();
						game_state = 1;
					}
					//if click "help"
					if (m.uMsg == WM_LBUTTONDOWN && m.x >= CANVAS_LENGTH / 2 - 25 && m.x <= CANVAS_LENGTH / 2 + 25 && m.y >= CANVAS_WIDTH / 2 + 100 && m.y <= CANVAS_WIDTH / 2 + 120) {
						PlaySound(NULL, NULL, SND_FILENAME);
						PlaySound(_T("wave\\menu.wav"), NULL, SND_FILENAME | SND_SYNC);
						game_state = 4;
					}
					//if click "exit"
					if (m.uMsg == WM_LBUTTONDOWN && m.x >= CANVAS_LENGTH / 2 - 25 && m.x <= CANVAS_LENGTH / 2 + 25 && m.y >= CANVAS_WIDTH / 2 + 70 && m.y <= CANVAS_WIDTH / 2 + 90) {
						PlaySound(NULL, NULL, SND_FILENAME);
						PlaySound(_T("wave\\menu.wav"), NULL, SND_FILENAME | SND_SYNC);
						exit(0);
					}
				}
			}
			break;
		case 1://游戏界面 the playing interface
			//some initializations
			loadimage(&bk2, _T("img\\background.jpg"), CANVAS_LENGTH, CANVAS_WIDTH);
			PlaySound(_T("wave\\bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			s.numtmp = 0;
			//loop
			while (1) {
				//begin to draw the interface
				BeginBatchDraw();
				start = GetTickCount();
				//show the background
				putimage(0, 0, &bk2);
				//get mouse's information
				if (MouseHit()) {
					m = GetMouseMsg();
					if (m.uMsg == WM_LBUTTONDOWN) {
						//if click "back"
						if (m.x >= 18 && m.x <= 62 && m.y >= 18 && m.y <= 32) game_state = 0;
						//if click "suspend"
						if (m.x >= 18 && m.x <= 62 && m.y >= 38 && m.y <= 52) game_state = 2;
						//if click "achievement system
						if (m.x >= 20 && m.x <= 60 && m.y >= 460 && m.y <= 470) game_state = 3;
						if (game_state != 1) {
							PlaySound(NULL, NULL, SND_FILENAME);
							PlaySound(_T("wave\\menu.wav"), NULL, SND_FILENAME | SND_SYNC);
							EndBatchDraw();
							break;
						}
						//else fire the cannon
						if (!c.update(m)) {
							c.fire();
							s.numtmp = -c.cost;
							s.num += s.numtmp;
							s.show();
						}
						//PlaySound(_T("wave\\fire.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
					}
					//update the cannon according to the mouse
					c.rotate(m);
				}
				//create a new fish after 12 loops
				if (time == 12) {
					fish ftmp;
					obb otmp;
					otmp.f = ftmp;
					otmp.init();
					o.emplace_back(otmp);
					time = 0;
				}
				//judge if bullets hit fish and create webs and update bullets
				if (!c.bullets.empty())
					for (auto i = c.bullets.begin(); i != c.bullets.end();) {
						auto j = o.begin();
						while (j != o.end()) {
							if (in_obb(*j, *i)) {
								web wtmp;
								wtmp.create(*i);
								w.emplace_back(wtmp);
								break;
							}
							else j++;
						}
						if (j != o.end()) i = c.bullets.erase(i);
						else {
							if (!(*i).in_canvas()) i = c.bullets.erase(i);
							else {
								(*i).move();
								i++;
							}
						}
					}
				//update fish
				if (!o.empty())
					for (auto i = o.begin(); i != o.end();) {
						if (!(*i).f.in_canvas()) {
							i = o.erase(i);
						}
						else {
							(*i).f.move();
							(*i).update();
							i++;
						}
					}
				//judge which fish are caught by webs and judge whether bombs and grasses are caught
				if (!w.empty())
					for (auto i = w.begin(); i != w.end(); i++) {
						if (!(*i).is_show) {
							is_grass = false;
							is_bomb = false;
							numtmp = 0;
							for (auto j = o.begin(); j != o.end();) {
								if (collision(*j, *i)) {
									(*j).is_collision = true;
									if ((*j).f.kind == 7) {
										is_bomb = true;
										j = o.erase(j);
									}
									else if ((*j).f.kind == 6) {
										is_grass = true;
										j = o.erase(j);
									}
									else j++;
								}
								else j++;
							}
							//if a bomb is caught, every fish in the web is dead and values are got
							if (is_bomb==true) {
								(*i).is_bomb = true;
								for (auto j = o.begin(); j != o.end();) {
									if ((*j).is_collision==true) {
										(*j).f.dead(fc);
										numtmp += (*j).f.value;
										j = o.erase(j);
									}
									else j++;
								}
							}
							//if a grass is caught, every fish in the web is dead but score is -20
							else if (is_grass==true) {
								for (auto j = o.begin(); j != o.end();) {
									if ((*j).is_collision==true) j = o.erase(j);
									else j++;
								}
								numtmp = -20;
							}
							//in common cases, fish caught by webs are probably not dead
							else {
								for (auto j = o.begin(); j != o.end();) {
									if ((*j).is_collision==true){
										if ((*j).f.is_dead(c.cost)) {
											(*j).f.dead(fc);
											numtmp += (*j).f.value;
											j = o.erase(j);
										}
										else {
											(*j).is_collision = false;
											j++;
										}
									}
									else j++;
								}
							}
							//update webs' and score's status 
							(*i).is_show = true;
							(*i).time = 0;
							(*i).g_vx = (590 - (*i).center.x) / 15;
							(*i).g_vy = ((*i).center.y - 50) / 15;
							s.numtmp = numtmp;
							s.num += s.numtmp;
							if (s.numtmp > 0) (*i).is_gold = true;
						}
					}
				//show the fish
				if (!o.empty())
					for (auto i = o.begin(); i != o.end(); i++) {
						(*i).f.show();
					}
				//show the webs
				if (!w.empty())
					for (auto i = w.begin(); i != w.end();) {
						if ((*i).is_show) {
							if ((*i).time > 15) {
								i = w.erase(i);
							}
							else {
								(*i).show();
								(*i).time++;
								i++;
							}
						}
						else i++;
					}
				//show the bullets
				c.show_bullets();
				//show the buttons
				createbutton(18, 62, 18, 32, 10, _T("回主菜单"));
				createbutton(18, 62, 38, 52, 10, _T("暂停游戏"));
				createbutton(0, 640, 430, 480, 20, _T(""));
				createbutton(20, 60, 460, 470, 10, _T("成就系统"));
				//show the cannon and score
				c.show();
				s.show();
				//if score<0, game over
				if (s.num < 0) {
					game_state = 5;
					break;
				}
				stop = GetTickCount();
				EndBatchDraw();
				time++;
				//control loop's frequency
				if (stop - start < 30) Sleep(30 - (stop - start));
			}
			break;
		case 2://游戏暂停 game suspending
			PlaySound(NULL, NULL, SND_FILENAME);
			//create the interface
			BeginBatchDraw();
			createbutton(18, 62, 18, 32, 10, _T("回主菜单"));
			createbutton(18, 62, 38, 52, 10, _T("继续游戏"));
			EndBatchDraw();
			m = GetMouseMsg();
			//if click "continue"
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 18 && m.x <= 62 && m.y >= 38 && m.y <= 52) {
				PlaySound(_T("wave\\menu.wav"), NULL, SND_FILENAME | SND_SYNC);
				game_state = 1;
			}
			//if click "back"
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 18 && m.x <= 62 && m.y >= 18 && m.y <= 32) {
				PlaySound(_T("wave\\menu.wav"), NULL, SND_FILENAME | SND_SYNC);
				game_state = 0;
			}
			break;
		case 3://成就系统 achievement system
			//create the interface
			BeginBatchDraw();
			createbutton(40, 600, 50, 430, 20, _T(""));
			createbutton(100, 540, 50, 80, 20, _T("成就系统"));
			createbutton(520, 540, 50, 60, 10, _T("返回"));
			createbutton(40, 600, 305, 320, 15, _T("十全十美——除一种鱼其余鱼各捕获十条时该鱼命中率提升一倍，时间持续五次射击"));
			createbutton(50, 590, 330, 345, 15, _T("水逆消失——捕获水草十次时消除水草，时间持续五次射击"));
			createbutton(50, 590, 355, 370, 15, _T("欧皇附体——捕获炸弹五次时各种鱼命中率提升一倍，时间持续五次射击"));
			for (int i = 1; i <=KIND; i++) fc[i].show();
			EndBatchDraw();
			m = GetMouseMsg();
			//if click "back"
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 520 && m.x <= 540 && m.y >= 50 && m.y <= 60) {
				PlaySound(NULL, NULL, SND_FILENAME);
				PlaySound(_T("wave\\menu.wav"), NULL, SND_FILENAME | SND_SYNC);
				game_state = 1;
			}
			break;
		case 4://游戏帮助 help
			//create the interface
			BeginBatchDraw();
			putimage(0, 0, &bk);
			createbutton(100, 540, 50, 430, 20, _T(""));
			createbutton(100, 540, 50, 80, 20, _T("游戏帮助"));
			createbutton(520, 540, 50, 60, 10, _T("返回"));
			r = { 110, 90, 530, 540 };
			settextstyle(15, 0, _T("黑体"));
			drawtext(_T("像玩传统的捕鱼达人一样去玩这个游戏\nENJOY YOURSELF:)\n\nTIPS:\n网到水草  -20\n网到炸弹  网内鱼类全部收获"), &r, DT_LEFT | DT_WORDBREAK);
			EndBatchDraw();
			//if click "back"
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN && m.x >= 520 && m.x <= 540 && m.y >= 50 && m.y <= 60) game_state = 0;
			break;
		case 5://游戏结束 game over
			//create the interface
			PlaySound(_T("wave\\end.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			r = { 0,190,640,250 };
			cleardevice();
			setbkcolor(BLACK);
			settextstyle(50, 0, _T("黑体"));
			settextcolor(YELLOW);
			//loop
			while (game_state == 5) {
				BeginBatchDraw();
				drawtext(_T("GAME OVER"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				createbutton(295, 345, 300, 310, 10, _T("重新开始"));
				createbutton(295, 345, 320, 330, 10, _T("退出游戏"));
				EndBatchDraw();
				m = GetMouseMsg();
				//if click "restart"
				if (m.uMsg == WM_LBUTTONDOWN && m.x >= 295 && m.x <= 345 && m.y >= 300 && m.y <= 310) {
					PlaySound(NULL, NULL, SND_FILENAME);
					PlaySound(_T("wave\\menu.wav"), NULL, SND_FILENAME | SND_SYNC);
					game_state = 0;
				}
				//if click "exit"
				else if (m.uMsg == WM_LBUTTONDOWN && m.x >= 295 && m.x <= 345 && m.y >= 320 && m.y <= 330) {
					PlaySound(NULL, NULL, SND_FILENAME);
					PlaySound(_T("wave\\menu.wav"), NULL, SND_FILENAME | SND_SYNC);
					exit(0);
				}
			}
			break;
		}
	}
}
