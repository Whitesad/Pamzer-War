#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "head.h"
#include "resources.h"

class player_class
{
public:
	//========================
	//*********�ӵ���*********
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
		int movebullet(void);//�ڵ�ͼ���ƶ�����ӵ���λ��
		//static int bullet_incident_judge(void);
	public:
		bool destory;
		int bx, by;
	private:
		Forward bullet_forward;
		int bullet_cd;//�����ӵ��ƶ����ٶ�
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
	int moveplayer(char move); //���ݴ�����moveָ����ĵ�ͼ���ڵ�ͼ�ϸ�����ҵ�����
	int shoot(void);//��ǹ�ı��ʾ��Ǵ���һ��bulltet��
	int flash_bullet_position(void);//ͨ����player��ԭ�е�player_bullet�Ĵ�������ӵ��������Լ��ƶ�
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
