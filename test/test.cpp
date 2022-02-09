
#include <iostream>
#include <math.h>
#include <time.h>
#include <graphics.h>
#define flower_num   30
#define num 30
#define max_speed 1.35f
#define PI 3.1415926
#define G 0.055
#define g G*8
float xa[13];
float ya[13];
int color_data[3] = { RGB(236,176,238),WHITE,GREEN };
using namespace std;

struct particle
{
	int x, y;
	int hx, hy;
	bool shoot;
	unsigned long t1, t2, dt;
	IMAGE img[2];
	byte n : 1;
}particle[num];


void load()
{
	IMAGE bigimg;
	loadimage(&bigimg, L"shoot.jpg", 200, 50);

	SetWorkingImage(&bigimg);
	for (int i = 0; i < num; i++)
	{
		int n = rand() % 5;
		getimage(&particle[i].img[0], n * 20, 0, 20, 50);
		getimage(&particle[i].img[1], (n + 5) * 20, 0, 20, 50);

	}


	SetWorkingImage(NULL);


}
void initt(int i)
{
	particle[i].x = 0;
	particle[i].y = 0;
	particle[i].hx = 0;
	particle[i].hy = 0;
	particle[i].n = 0;
	particle[i].t1 = GetTickCount();
	particle[i].t2 = 0;
	particle[i].dt = rand() % 10 + 1;
	particle[i].shoot = false;


}

typedef struct
{
	double x_start, y_start;
	double x, y;
	double x_speed, y_speed;
	double x_speed2, y_speed2;
	int color_num;
	int tim1, tim2;
	int t, t2;

}lizi_t;
struct fire_flower
{
	int x_start, y_start;
	int x_end, y_end;
	int x_speed, y_speed;
	int color_num;
	int tim1, tim2;
	float t;
	lizi_t lizi[30];
	bool flag;
}flower[flower_num];

void init()
{
	for (int i = 0; i < flower_num; i++)
	{
		flower[i].x_start = 0;
		flower[i].y_start = 0;
		flower[i].x_end = 0;
		flower[i].y_end = 0;
		flower[i].x_speed = 0;
		flower[i].y_speed = 0;
		flower[i].color_num = 0;
		flower[i].flag = false;
		flower[i].tim1 = GetTickCount();
		flower[i].tim2 = 0;
	}
}
void choice_flower(DWORD& tt3, int x, int y,int n)
{
	DWORD tt4 = GetTickCount();

	cout << n << endl;
	if (tt4 - tt3 > 100)
	{

		if (flower[n].flag == false)
		{
			int a = rand() % 3;
			for (int i = 0; i < 20; i++)
			{
				flower[n].t = 0;
				flower[n].x_start = x;
				flower[n].y_start = y;
				flower[n].lizi[i].color_num = a;
				flower[n].lizi[i].x_start = x;
				flower[n].lizi[i].y_start = y;
				flower[n].lizi[i].x = x;
				flower[n].lizi[i].y = y;
				double levelangle = rand() % 360;
				double uprightangle = rand() % 360;
				double xy_speed = max_speed * cos(uprightangle * PI / 180.0f);

				flower[n].lizi[i].y_speed = xy_speed * sin(levelangle * PI / 180.0f);
				flower[n].lizi[i].x_speed = xy_speed * cos(levelangle * PI / 180.0f);
				flower[n].lizi[i].x_speed2 = xy_speed * cos(levelangle * PI / 180.0f);
				flower[n].lizi[i].y_speed2 = xy_speed * sin(levelangle * PI / 180.0f);

				flower[n].lizi[i].tim1 = GetTickCount();
				flower[n].flag = true;


			}

		}
		tt3 = tt4;
	}
}


void choice(DWORD& tt1)
{
	DWORD tt2 = GetTickCount();
	if (tt2 - tt1 > 100)
	{
		int i = rand() % num;
		if (particle[i].shoot == false)
		{
			particle[i].x = rand() % (1000 - 20) + 20;
			particle[i].y = rand() % 100 + 400;
			particle[i].hx = particle[i].x;
			particle[i].hy = rand() % 400;
			particle[i].shoot = true;
			putimage(particle[i].x, particle[i].y, &particle[i].img[0]);

		}
		tt1 = tt2;
	}


}
double t = 0;
void boom()
{
	for (int i = 0; i < flower_num; i++)
	{

	flower[i].tim2 = flower[i].t;
	static int asc = 0;

	float time_d = (flower[i].tim2 - flower[i].tim1);
	if (flower[i].flag == true && flower[i].t < 300)
	{
		asc++;
		for (int j = 0; j < 30; j++)
		{
			if (flower[i].t < 150)
			{

				flower[i].lizi[j].x_start += time_d * flower[i].lizi[j].x_speed;
				flower[i].lizi[j].y_start += (time_d * flower[i].lizi[j].y_speed + 0.5f * G * time_d * time_d);
				setfillcolor(color_data[flower[i].lizi[j].color_num]);

				solidcircle(flower[i].lizi[j].x_start, flower[i].lizi[j].y_start, 0.2);
				flower[i].lizi[j].y_speed += G * time_d * 0.1;
			}

			if (flower[i].t > 150)
			{

					flower[i].lizi[j].x += time_d * 1.5 * flower[i].lizi[j].x_speed2;
				flower[i].lizi[j].y += (time_d * 1.5 * flower[i].lizi[j].y_speed2 + 0.5f * G * time_d * time_d * 1.5 * 1.5);
				setfillcolor(BLACK);
			
				solidcircle(flower[i].lizi[j].x, flower[i].lizi[j].y, 2.5);
				flower[i].lizi[j].y_speed2 += G * time_d * 1.5 * 0.1;
			}
			flower[i].t += 0.005;
			flower[i].tim1 = flower[i].tim2;
		}

	}

	}


}
DWORD tt3 = GetTickCount();
void shoot(DWORD &tt3,int& x, int& y)
{
	
	for (int i = 0; i < num; i++)
	{
		particle[i].t2 = GetTickCount();

		if (particle[i].t2 - particle[i].t1 > particle[i].dt && particle[i].shoot == true)
		{

			if (particle[i].y >= particle[i].hy)
			{
				particle[i].y -= 5;
				particle[i].n++;


				putimage(particle[i].x, particle[i].y, &particle[i].img[particle[i].n]);
				putimage(particle[i].x, particle[i].y, &particle[i].img[particle[i].n]);

				particle[i].t1 = particle[i].t2;
			}
			else
			{
				int n = 1;
				setfillcolor(BLACK);
				if (n == 1)
				{
					solidcircle(particle[i].x + 10, particle[i].y + 25, 20);
					n++;
				}
				choice_flower(tt3, particle[i].x,particle[i].y,i);
		
				xa[i] = particle[i].hx;
				ya[i] = particle[i].hy;

			}

		}
		boom();
	}

}

int main()
{
	DWORD tt1 = GetTickCount();
	DWORD tt3 = GetTickCount();
	int Xx, Yy;
	srand(time(NULL));
	initgraph(1200, 800);
	for (int i = 0; i < num; i++)
	{
		initt(i);
	}
	load();
	while (1)
	{
		choice(tt1);
		shoot(tt3,Xx, Yy);
	}
	system("pause");
}
