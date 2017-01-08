#include<iostream>
#include<string>
#include<easyx.h>
#include<graphics.h>
#include<conio.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
using namespace std;

#define Map_width 600//游戏地图宽600
#define Map_height 600//游戏地图高600
#define MAP_ITEM int
#define FACE_LEFT 1         //坦克方向朝左
#define FACE_RIGHT 2		//坦克方向朝右
#define FACE_UP 3			//坦克方向朝上
#define FACE_DOWN 4			//坦克方向朝下

class Cimage
{
public:
	Cimage() { load(); }
	IMAGE	backImage,//背景图
		backGround,   //地图背景
		hbuttonImage[3], //高亮按钮图
		lbuttonImage[3], //非高亮按钮图
		block[4], //三种砖块
		end,    //结束标志
		tank[4],    //坦克4个方向 0_up 1_right 2_down 3_left
		Bullet[4],//子弹4个方向
		Gamebackground,//游戏内背景图
		howto,//游戏说明
		back[2], replay[2];//返回，重新开始
private:
	void load() {
		loadimage(&backGround, "图片\\地图背景.jpg");
		loadimage(&backImage, "图片\\背景图.jpg");
		loadimage(&hbuttonImage[0], "图片\\开始游戏1.jpg");
		loadimage(&hbuttonImage[1], "图片\\游戏说明1.jpg");
		loadimage(&hbuttonImage[2], "图片\\退出游戏1.jpg");
		loadimage(&lbuttonImage[0], "图片\\开始游戏.jpg");
		loadimage(&lbuttonImage[1], "图片\\游戏说明.jpg");
		loadimage(&lbuttonImage[2], "图片\\退出游戏.jpg");
		loadimage(&back[0], "图片\\返回上级1.jpg");
		loadimage(&back[1], "图片\\返回上级.jpg");
		loadimage(&replay[0], "图片\\重新开始1.jpg");
		loadimage(&replay[1], "图片\\重新开始.jpg");
		loadimage(&block[0], "图片\\砖块0.jpg");
		loadimage(&block[1], "图片\\砖块0.5.jpg");
		loadimage(&block[2], "图片\\砖块1.jpg");
		loadimage(&block[3], "图片\\砖块2.jpg");
		loadimage(&end, "图片\\结束标志.jpg");
		loadimage(&tank[0], "图片\\tank_up.jpg");
		loadimage(&tank[1], "图片\\tank_right.jpg");
		loadimage(&tank[2], "图片\\tank_down.jpg");
		loadimage(&tank[3], "图片\\tank_left.jpg");
		loadimage(&Bullet[2], "图片\\bullet_up.jpg");
		loadimage(&Bullet[1], "图片\\bullet_right.jpg");
		loadimage(&Bullet[3], "图片\\bullet_down.jpg");
		loadimage(&Bullet[0], "图片\\bullet_left.jpg");
		loadimage(&Gamebackground, "图片\\gamebackground.jpg");
		loadimage(&howto, "图片\\游戏说明页1.jpg");

	}
};

class Csound {
public:
	Csound() { loadsound(); }
private:
	void loadsound()
	{
		mciSendString("open 音乐\\主界面.mp3", NULL, 0, NULL);
		mciSendString("open 音乐\\游戏音乐.mp3", NULL, 0, NULL);
	}
};

class Cmap :public Cimage {
public:
	void InitMap() {

		if (level == 1) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					switch (map1[i][j])
					{
					case 0:break;
					case 1:putimage(j * 60, i * 60, &block[0]); break;
					case 2:putimage(j * 60, i * 60, &block[1]); break;
					case 3:putimage(j * 60, i * 60, &block[2]); break;
					case 4:putimage(j * 60, i * 60, &block[3]); break;
					case 5:putimage(j * 60, i * 60, &end); break;
					default:
						break;
					}
				}
			}
		}
		else if (level == 2) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					switch (map2[i][j])
					{
					case 0:break;
					case 1:putimage(j * 60, i * 60, &block[0]); break;
					case 2:putimage(j * 60, i * 60, &block[1]); break;
					case 3:putimage(j * 60, i * 60, &block[2]); break;
					case 4:putimage(j * 60, i * 60, &block[3]); break;
					case 5:putimage(j * 60, i * 60, &end); break;
					default:
						break;
					}
				}
			}
		}
		putimage(600, 0, &backGround);
	}
	MAP_ITEM getItem(int level, int x, int y) {
		if (level == 1)
			return map1[x][y];
		else if (level == 2)
			return map2[x][y];
	}
	void changeItem(int level, int x, int y) {
		if (level == 1) {
			int &a = map1[x][y];
			switch (a)
			{
			case 0:break;
			case 1:a = 0; break;
			case 2:a = 0; break;
			case 3:a = 2; break;
			case 4:break;
			default:
				break;
			}
		}
		else if (level == 2) {
			int &a = map2[x][y];
			switch (a)
			{
			case 0:break;
			case 1:a = 0; break;
			case 2:a = 0; break;
			case 3:a = 2; break;
			case 4:break;
			default:
				break;
			}
		}
	}
	int getLevel() {
		return level;
	}
private:
	int map1[10][10] = {
		0,0,1,0,3,0,3,0,3,0,
		0,3,0,1,0,4,0,1,0,1,
		1,0,3,0,1,0,1,0,1,0,
		0,1,0,3,0,4,0,1,0,1,
		3,0,1,0,3,0,4,0,4,0,
		0,4,0,4,0,3,0,1,0,1,
		3,0,1,0,4,0,3,0,1,0,
		0,1,0,1,0,1,0,3,0,1,
		3,0,1,0,4,0,1,0,3,0,
		0,1,0,1,0,1,0,1,0,5
	};
	int map2[10][10] = {
		0,0,0,1,1,1,1,1,1,1,
		0,3,3,0,0,0,0,0,0,1,
		0,1,0,3,3,1,0,3,0,1,
		0,2,0,3,0,3,0,2,0,1,
		1,1,3,1,0,1,1,1,1,1,
		3,1,0,0,0,0,0,0,0,1,
		1,1,1,1,3,2,2,2,0,1,
		0,0,1,0,0,0,0,0,0,1,
		0,3,3,3,3,3,2,2,3,2,
		0,0,0,0,0,0,0,0,0,5
	};

	int width = 600; //地图宽600
	int height = 600; //地图高600
	int level = 1;    //关卡1

};

class Cbullet :public Cmap {
public:
	void drawBullet(int face, int x, int y) {
		switch (face)
		{
		case FACE_LEFT:Bx = x - 60; By = y; bullet_x = Bx / 60; bullet_y = By / 60; left(x, y);  break;
		case FACE_RIGHT:Bx = x + 60; By = y; bullet_x = Bx / 60; bullet_y = By / 60; right(x, y); break;
		case FACE_UP:By = y - 60; Bx = x; bullet_x = Bx / 60; bullet_y = By / 60; up(x, y); break;
		case FACE_DOWN:By = y + 60; Bx = x; bullet_x = Bx / 60; bullet_y = By / 60; down(x, y); break;
		default:
			break;
		}
	}
	int getBullet()
	{
		return num;
	}
private:
	int num = 10;     //子弹数量10
	int distance;  //子弹需要行走的距离
	int Bx, By;    //子弹左上角坐标
	int bullet_x;//子弹在矩阵中X坐标
	int bullet_y;//子弹在矩阵中Y坐标

	 //子弹向左飞行
	void left(int x, int y) {
		distance = 0;
		while (getItem(getLevel(), bullet_y, bullet_x - distance / 60) == 0 && Bx - distance >= 0) {
			distance += 60;
		}
		if (Bx < 0)
		{
			num--;
			putimage(x, y, &tank[3]);
		}
		else if (getItem(getLevel(), bullet_y, bullet_x)>0)
		{
			num--;
			changeItem(getLevel(), bullet_y, bullet_x);
			putimage(x, y, &tank[3]);
		}
		else
		{
			for (int i = 0; i < distance; i += 2) {
				Bx -= 2; putimage(Bx, By, &Bullet[0]);
				putimage(x, y, &tank[3]);
				InitMap();
				Sleep(2);
			}
			changeItem(getLevel(), bullet_y, bullet_x - distance / 60);
			BeginBatchDraw();
			putimage(0, 0, &Gamebackground);
			putimage(x, y, &tank[3]);
			InitMap();
			EndBatchDraw();
		}
	}
	//子弹向右飞行
	void right(int x, int y) {
		distance = 0;
		while (getItem(getLevel(), bullet_y, bullet_x + distance / 60) == 0 && Bx + distance <Map_width) {
			distance += 60;
		}

		if (Bx >= Map_width)
		{
			num--;
			putimage(x, y, &tank[1]);
		}
		else if (getItem(getLevel(), bullet_y, bullet_x)>0)
		{
			num--;
			changeItem(getLevel(), bullet_y, bullet_x);
			putimage(x, y, &tank[1]);
		}
		else
		{
			for (int i = 0; i < distance&&Bx<Map_width; i += 2) {
				Bx += 2; putimage(Bx, By, &Bullet[1]);
				putimage(x, y, &tank[1]);
				InitMap();
				Sleep(2);
			}
			if (bullet_x + distance / 60 <= 9)
			{
				changeItem(getLevel(), bullet_y, bullet_x + distance / 60);
			}

			BeginBatchDraw();
			putimage(0, 0, &Gamebackground);
			putimage(x, y, &tank[1]);
			InitMap();
			EndBatchDraw();
		}
	}
	//子弹向上飞行
	void up(int x, int y) {
		distance = 0;
		while (getItem(getLevel(), bullet_y - distance / 60, bullet_x) == 0 && By - distance >= 0) {
			distance += 60;
		}
		if (By < 0)
		{
			num--;
			putimage(x, y, &tank[0]);
		}
		else if (getItem(getLevel(), bullet_y, bullet_x)>0)
		{
			num--;
			changeItem(getLevel(), bullet_y, bullet_x);
			putimage(x, y, &tank[0]);
		}
		else
		{
			for (int i = 0; i < distance; i += 2) {
				By -= 2; putimage(Bx, By, &Bullet[2]);
				putimage(x, y, &tank[0]);
				InitMap();
				Sleep(2);
			}
			changeItem(getLevel(), bullet_y - distance / 60, bullet_x);
			BeginBatchDraw();
			putimage(0, 0, &Gamebackground);
			putimage(x, y, &tank[0]);
			InitMap();
			EndBatchDraw();
		}
	}
	//子弹向下飞行
	void down(int x, int y) {
		distance = 0;
		while (getItem(getLevel(), bullet_y + distance / 60, bullet_x) == 0 && By + distance<Map_height) {
			distance += 60;
		}
		if (By >= 600)
		{
			num--;
			putimage(x, y, &tank[2]);
		}
		else if (getItem(getLevel(), bullet_y, bullet_x)>0)
		{
			num--;
			changeItem(getLevel(), bullet_y, bullet_x);
			putimage(x, y, &tank[2]);
		}
		else
		{
			for (int i = 0; i < distance; i += 2) {
				By += 2; putimage(Bx, By, &Bullet[3]);
				putimage(x, y, &tank[2]);
				InitMap();
				Sleep(2);
			}
			changeItem(getLevel(), bullet_y + distance / 60, bullet_x);
			BeginBatchDraw();
			putimage(0, 0, &Gamebackground);
			putimage(x, y, &tank[2]);
			InitMap();
			EndBatchDraw();
		}
	}

};


class Ctank :public Cbullet {
public:
	void controller(char c)
	{
		tank_x = x / 60;
		tank_y = y / 60;

		putimage(0, 0, &Gamebackground);
		switch (c)
		{
		case 'a':face = FACE_LEFT; Left(); break;
		case 'd':face = FACE_RIGHT; Right(); break;
		case 'w':face = FACE_UP; Up(); break;
		case 's':face = FACE_DOWN; Down(); break;
		case ' ':drawBullet(face, x, y); break;
		default:break;
		}
		InitMap();
	}
private:
	int length = 60;//坦克长宽都为60
	int distance = 60;//坦克每次移动距离为60
	int step = 1;//每帧移动1px
	int bullet = 10;//坦克开局有10个子弹
	int x = 0; //坦克在左上角贴图在X轴位置
	int y = 0; //坦克在左上角贴图在Y轴位置
	int tank_x;//坦克在矩阵中X位置
	int tank_y;//坦克在矩阵中Y位置
	int face;   //坦克朝向

	void Left() //左走
	{
		if (x <= 0)
		{
			putimage(x, y, &tank[3]);
		}
		else if (getItem(getLevel(), tank_y, tank_x - 1)>0)
		{
			putimage(x, y, &tank[3]);
		}
		else
		{
			for (int i = 0; i < distance; i++) {
				x -= step; putimage(x, y, &tank[3]);
				Sleep(2);
				InitMap();
			}
		}
	}
	void Right()//右走
	{
		if (x >= Map_width - length)
		{
			putimage(x, y, &tank[1]);
		}
		else if (getItem(getLevel(), tank_y, tank_x + 1)>0)
		{
			putimage(x, y, &tank[1]);
		}
		else
		{
			for (int i = 0; i < distance; i++) {
				x += step; putimage(x, y, &tank[1]);
				Sleep(2);
				InitMap();
			}
		}
	}
	void Up()//上走
	{
		if (y <= 0)
		{
			putimage(x, y, &tank[0]);
		}
		else if (getItem(getLevel(), tank_y - 1, tank_x)>0)
		{
			putimage(x, y, &tank[0]);
		}
		else
		{
			for (int i = 0; i < distance; i++)
			{
				y -= step; putimage(x, y, &tank[0]);
				Sleep(2);
				InitMap();
			}

		}
	}
	void Down()//下走
	{
		if (y >= Map_height - length)
		{
			putimage(x, y, &tank[2]);
		}
		else if (getItem(getLevel(), tank_y + 1, tank_x)>0)
		{
			putimage(x, y, &tank[2]);
		}
		else
		{
			for (int i = 0; i < distance; i++)
			{
				y += step; putimage(x, y, &tank[2]);
				Sleep(2);
				InitMap();
			}
		}
	}
};

class Cgame{
public:
	void start()
	{
		initgraph(width, height);
		//mciSendString("play 音乐\\游戏音乐.mp3", NULL, 0, NULL);
		Cmap level1;
		Cimage img;
		level1.InitMap();
		Ctank tank;
		char c;
		putimage(0, 0, &img.tank[0]);
		while (1)
		{
			c = getch();//获取按键
			if (c != 'a')
			{
				if (c != 's')
				{
					if (c != 'd')
					{
						if (c != 'w')
						{
							if (c != ' ')
							{
								continue;
							}
						}
					}
				}
			}
			tank.controller(c);
		}
	}
private:
	int width = 800; //主界面宽800
	int height = 600; //主界面高600
};

class UI :public Cimage, public Csound {
public:
	UI()
	{
		initgraph(width, height);
		mainscene();
	}
	void mainscene()
	{
		putimage(0, 0, &backImage);
		//mciSendString("play 音乐\\主界面.mp3", NULL, 0, NULL);
		putimage(70, 170, &hbuttonImage[0]);
		putimage(70, 290, &hbuttonImage[1]);
		putimage(70, 410, &hbuttonImage[2]);
		MOUSEMSG msg;
		Cgame game;
		while (1)
		{
			msg = GetMouseMsg();
			//开始游戏
			if (msg.x >= 70 && msg.x <= 280 && msg.y >= 170 && msg.y <= 170 + bHeight && msg.uMsg == WM_LBUTTONDOWN)
			{
				putimage(70, 170, &lbuttonImage[0]);
			}
			else if (msg.x >= 70 && msg.x <= 280 && msg.y >= 170 && msg.y <= 170 + bHeight && msg.uMsg == WM_LBUTTONUP)
			{
				putimage(70, 170, &hbuttonImage[0]);
				mciSendString("stop 音乐\\主界面.mp3", NULL, 0, NULL);
				game.start();
				break;
			}
			//游戏说明
			if (msg.x >= 70 && msg.x <= 280 && msg.y >= 290 && msg.y <= 290 + bHeight && msg.uMsg == WM_LBUTTONDOWN)
			{
				putimage(70, 290, &lbuttonImage[1]);
			}
			else if (msg.x >= 70 && msg.x <= 280 && msg.y >= 290 && msg.y <= 290 + bHeight && msg.uMsg == WM_LBUTTONUP)
			{
				putimage(70, 290, &hbuttonImage[1]);
				howtoplay();
				break;
			}
			//结束游戏
			if (msg.x >= 70 && msg.x <= 280 && msg.y >= 410 && msg.y <= 410 + bHeight && msg.uMsg == WM_LBUTTONDOWN)
			{
				putimage(70, 410, &lbuttonImage[2]);
			}
			else if (msg.x >= 70 && msg.x <= 280 && msg.y >= 410 && msg.y <= 410 + bHeight && msg.uMsg == WM_LBUTTONUP)
			{
				putimage(70, 410, &hbuttonImage[2]);
				mciSendString("stop 音乐\\主界面.mp3", NULL, 0, NULL);
				closegraph();
			}
		}
	}
	void gamescene()
	{

	}
private:
	int width = 800; //主界面宽800
	int height = 600; //主界面高600
	int bWidth = 210; //按钮宽210
	int bHeight = 55;//按钮高55
	void howtoplay()
	{
		clearcliprgn();
		putimage(0, 0, &howto);
		putimage(560, 500, &back[0]);
		MOUSEMSG msg;
		while (1)
		{
			msg = GetMouseMsg();
			//开始游戏
			if (msg.x >= 560 && msg.x <= 560 + bWidth && msg.y >= 500 && msg.y <= 500 + bHeight && msg.uMsg == WM_LBUTTONDOWN)
			{
				putimage(560, 500, &back[1]);
			}
			else if (msg.x >= 560 && msg.x <= 560 + bWidth && msg.y >= 500 && msg.y <= 500 + bHeight && msg.uMsg == WM_LBUTTONUP)
			{
				putimage(560, 500, &back[0]);
				mainscene();
				break;
			}
		}
	}
};

int main()
{
	UI ui;

	system("pause");
}