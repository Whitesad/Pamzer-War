#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "head.h"
#include "resources.h"

class player_class
{
public:
	//========================
	//*********子弹类*********
	class bullet_class 
	{
	public:
		bullet_class(){/**/ }
		bullet_class(Forward forward_value, int bxvalue, int byvalue)
		{
			bullet_start = clock();
			bullet_forward = forward_value;
			bx = bxvalue, by = byvalue;
			bullet_cd = 50;
			destory = false;
		}
	public:
		int movebullet(void);//在地图上移动这个子弹的位置
		//static int bullet_incident_judge(void);
	public:
		bool destory;
		int bx, by;
	private:
		Forward bullet_forward;
		int bullet_cd;//决定子弹移动的速度
		bool isbulletcd(void);
		int bullet_start, bullet_clock;
	};
	//========================
public:
	player_class()
	{
		walkstart = clock();
		Invincible_Time_start = clock();
		bullet = 100;
		HP = 5;
	}
	void setforward(char move);
	int get_hurt(int damage);
	int return_HP(void) { return HP; }
	int return_BULLET(void) { return bullet; }
public:
	bool iswalkcd(void);
	bool isguncd(void);
	bool hasbullet(void);
	bool is_Invincible_Time(void);
public:
	int moveplayer(char move); //根据传来的move指令更改地图，在地图上更改玩家的坐标
	int shoot(void);//开枪的本质就是创建一个bulltet类
	int flash_bullet_position(void);//通过对player类原有的player_bullet的处理进行子弹的销毁以及移动
public:
	Forward player_forward;
	queue<player_class::bullet_class> player_bullet;

private:
	long walkstart, walkclock;
	long gun_start, gun_clock;
	long Invincible_Time_start, Invincible_Time_clock;
	unsigned int bullet;
	const int walkcd = 100;
	const int guncd = 500;
	const int Invincible_Time_cd = 1000;
	int HP;
};


#endif
