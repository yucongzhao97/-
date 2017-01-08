#include<iostream>
#include<string>
#include<easyx.h>
#include<graphics.h>
#include<conio.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
using namespace std;

#define Map_width 600//��Ϸ��ͼ��600
#define Map_height 600//��Ϸ��ͼ��600
#define MAP_ITEM int
#define FACE_LEFT 1         //̹�˷�����
#define FACE_RIGHT 2		//̹�˷�����
#define FACE_UP 3			//̹�˷�����
#define FACE_DOWN 4			//̹�˷�����

class Cimage
{
public:
	Cimage() { load(); }
	IMAGE	backImage,//����ͼ
		backGround,   //��ͼ����
		hbuttonImage[3], //������ťͼ
		lbuttonImage[3], //�Ǹ�����ťͼ
		block[4], //����ש��
		end,    //������־
		tank[4],    //̹��4������ 0_up 1_right 2_down 3_left
		Bullet[4],//�ӵ�4������
		Gamebackground,//��Ϸ�ڱ���ͼ
		howto,//��Ϸ˵��
		back[2], replay[2];//���أ����¿�ʼ
private:
	void load() {
		loadimage(&backGround, "ͼƬ\\��ͼ����.jpg");
		loadimage(&backImage, "ͼƬ\\����ͼ.jpg");
		loadimage(&hbuttonImage[0], "ͼƬ\\��ʼ��Ϸ1.jpg");
		loadimage(&hbuttonImage[1], "ͼƬ\\��Ϸ˵��1.jpg");
		loadimage(&hbuttonImage[2], "ͼƬ\\�˳���Ϸ1.jpg");
		loadimage(&lbuttonImage[0], "ͼƬ\\��ʼ��Ϸ.jpg");
		loadimage(&lbuttonImage[1], "ͼƬ\\��Ϸ˵��.jpg");
		loadimage(&lbuttonImage[2], "ͼƬ\\�˳���Ϸ.jpg");
		loadimage(&back[0], "ͼƬ\\�����ϼ�1.jpg");
		loadimage(&back[1], "ͼƬ\\�����ϼ�.jpg");
		loadimage(&replay[0], "ͼƬ\\���¿�ʼ1.jpg");
		loadimage(&replay[1], "ͼƬ\\���¿�ʼ.jpg");
		loadimage(&block[0], "ͼƬ\\ש��0.jpg");
		loadimage(&block[1], "ͼƬ\\ש��0.5.jpg");
		loadimage(&block[2], "ͼƬ\\ש��1.jpg");
		loadimage(&block[3], "ͼƬ\\ש��2.jpg");
		loadimage(&end, "ͼƬ\\������־.jpg");
		loadimage(&tank[0], "ͼƬ\\tank_up.jpg");
		loadimage(&tank[1], "ͼƬ\\tank_right.jpg");
		loadimage(&tank[2], "ͼƬ\\tank_down.jpg");
		loadimage(&tank[3], "ͼƬ\\tank_left.jpg");
		loadimage(&Bullet[2], "ͼƬ\\bullet_up.jpg");
		loadimage(&Bullet[1], "ͼƬ\\bullet_right.jpg");
		loadimage(&Bullet[3], "ͼƬ\\bullet_down.jpg");
		loadimage(&Bullet[0], "ͼƬ\\bullet_left.jpg");
		loadimage(&Gamebackground, "ͼƬ\\gamebackground.jpg");
		loadimage(&howto, "ͼƬ\\��Ϸ˵��ҳ1.jpg");

	}
};

class Csound {
public:
	Csound() { loadsound(); }
private:
	void loadsound()
	{
		mciSendString("open ����\\������.mp3", NULL, 0, NULL);
		mciSendString("open ����\\��Ϸ����.mp3", NULL, 0, NULL);
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

	int width = 600; //��ͼ��600
	int height = 600; //��ͼ��600
	int level = 1;    //�ؿ�1

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
	int num = 10;     //�ӵ�����10
	int distance;  //�ӵ���Ҫ���ߵľ���
	int Bx, By;    //�ӵ����Ͻ�����
	int bullet_x;//�ӵ��ھ�����X����
	int bullet_y;//�ӵ��ھ�����Y����

	 //�ӵ��������
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
	//�ӵ����ҷ���
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
	//�ӵ����Ϸ���
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
	//�ӵ����·���
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
	int length = 60;//̹�˳���Ϊ60
	int distance = 60;//̹��ÿ���ƶ�����Ϊ60
	int step = 1;//ÿ֡�ƶ�1px
	int bullet = 10;//̹�˿�����10���ӵ�
	int x = 0; //̹�������Ͻ���ͼ��X��λ��
	int y = 0; //̹�������Ͻ���ͼ��Y��λ��
	int tank_x;//̹���ھ�����Xλ��
	int tank_y;//̹���ھ�����Yλ��
	int face;   //̹�˳���

	void Left() //����
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
	void Right()//����
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
	void Up()//����
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
	void Down()//����
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
		//mciSendString("play ����\\��Ϸ����.mp3", NULL, 0, NULL);
		Cmap level1;
		Cimage img;
		level1.InitMap();
		Ctank tank;
		char c;
		putimage(0, 0, &img.tank[0]);
		while (1)
		{
			c = getch();//��ȡ����
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
	int width = 800; //�������800
	int height = 600; //�������600
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
		//mciSendString("play ����\\������.mp3", NULL, 0, NULL);
		putimage(70, 170, &hbuttonImage[0]);
		putimage(70, 290, &hbuttonImage[1]);
		putimage(70, 410, &hbuttonImage[2]);
		MOUSEMSG msg;
		Cgame game;
		while (1)
		{
			msg = GetMouseMsg();
			//��ʼ��Ϸ
			if (msg.x >= 70 && msg.x <= 280 && msg.y >= 170 && msg.y <= 170 + bHeight && msg.uMsg == WM_LBUTTONDOWN)
			{
				putimage(70, 170, &lbuttonImage[0]);
			}
			else if (msg.x >= 70 && msg.x <= 280 && msg.y >= 170 && msg.y <= 170 + bHeight && msg.uMsg == WM_LBUTTONUP)
			{
				putimage(70, 170, &hbuttonImage[0]);
				mciSendString("stop ����\\������.mp3", NULL, 0, NULL);
				game.start();
				break;
			}
			//��Ϸ˵��
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
			//������Ϸ
			if (msg.x >= 70 && msg.x <= 280 && msg.y >= 410 && msg.y <= 410 + bHeight && msg.uMsg == WM_LBUTTONDOWN)
			{
				putimage(70, 410, &lbuttonImage[2]);
			}
			else if (msg.x >= 70 && msg.x <= 280 && msg.y >= 410 && msg.y <= 410 + bHeight && msg.uMsg == WM_LBUTTONUP)
			{
				putimage(70, 410, &hbuttonImage[2]);
				mciSendString("stop ����\\������.mp3", NULL, 0, NULL);
				closegraph();
			}
		}
	}
	void gamescene()
	{

	}
private:
	int width = 800; //�������800
	int height = 600; //�������600
	int bWidth = 210; //��ť��210
	int bHeight = 55;//��ť��55
	void howtoplay()
	{
		clearcliprgn();
		putimage(0, 0, &howto);
		putimage(560, 500, &back[0]);
		MOUSEMSG msg;
		while (1)
		{
			msg = GetMouseMsg();
			//��ʼ��Ϸ
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