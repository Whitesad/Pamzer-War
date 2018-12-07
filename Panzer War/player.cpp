#include "player.h"
#include "resources.h"
#include "enemy.h"
extern player_class player;
extern	int R, C;
extern int px, py;
extern char map[MAXR][MAXC];
bool player_class::iswalkcd(void)
{
	walkclock = clock();
	if ((walkclock - walkstart) >= walkcd)
	{
		walkstart = clock();
		return false;
	}
	else return true;
}
bool player_class::isguncd(void)
{
	gun_clock = clock();
	if ((gun_clock - gun_start) >= guncd)
	{
		gun_start = clock();
		return false;
	}
	else return true;
}
bool player_class::hasbullet(void)
{
	if (bullet > 0)
	{
		bullet--;
		gotoxy(BULLET_X, R + 1);
		printf("             ");
		gotoxy(BULLET_X, R + 1);
		printf("BULLET:%d", player.return_BULLET());
		return true;
	}
	else return false;
}
int player_class::moveplayer(char move)
{
	static int tch = START;
	static int tx, ty;
	tx = px, ty = py;
	switch (move)
	{
	case 'w':
		tx = px + UP;
		break;
	case 's':
		tx = px + DOWN;
		break;
	case 'a':
		ty = py + LEFT;
		break;
	case 'd':
		ty = py + RIGHT;
		break;
	}
	if (map[tx][ty]!=FENCE&&map[tx][ty]!=EDGE)
	{
		map[px][py] = tch;
		if (map[tx][ty] == START || map[tx][ty] == END || map[tx][ty] == ROAD)
			tch = map[tx][ty];
		map[tx][ty] = PLAYER;
		px = tx, py = ty;
	}
	return 0;
}
void player_class::setforward(char move)
{
	switch (move)
	{
	case 's':player_forward = Forward::down; break;
	case 'a':player_forward = Forward::left; break;
	case 'd':player_forward = Forward::right; break;
	case 'w':player_forward = Forward::up; break;
	}
}
bool player_class::is_Invincible_Time(void)
{
	Invincible_Time_clock = clock();
	if ((Invincible_Time_clock - Invincible_Time_start) >= Invincible_Time_cd)
	{
		Invincible_Time_start = clock();
		return false;
	}
	else return true;
}
int player_class::get_hurt(int damage)
{
	if (is_Invincible_Time()) return 0;
	else
	{
		if (HP - damage > 0)	HP -= damage;
		else HP = 0;
		gotoxy(0, R + 1);
		printf("HP:%d", player.HP);
		return 0;
	}
}

//================================
//*********×Óµ¯Àà*************
int player_class::shoot(void)
{
	player_class::bullet_class tem(player_forward,px,py);
	player_class::player_bullet.push(tem);
	return 0;
}
bool player_class::bullet_class::isbulletcd(void)
{
	bullet_clock = clock();
	if ((bullet_clock - bullet_start) >= bullet_cd)
	{
		bullet_start = clock();
		return false;
	}
	else return true;
}
int player_class::bullet_class::movebullet(void)
{
	if (isbulletcd()) return 0;
	static char tch = PLAYER;
	map[bx][by] = tch;
	switch (bullet_forward)
	{
	case Forward::up:
		if (bx + UP < 0 || map[bx + UP][by] == FENCE||map[bx+UP][by]==END||map[bx+UP][by]==ZOMBIE)
			destory = true;
		bx += UP;
		break;
	case Forward::down:
		if (bx + DOWN > R || map[bx + DOWN][by] == FENCE || map[bx + DOWN][by] == END || map[bx + DOWN][by] == ZOMBIE)
			destory = true;
		bx += DOWN;
		break;
	case Forward::left:
		if (by + LEFT < 0 || map[bx][by+LEFT] == FENCE || map[bx][by+LEFT] == END || map[bx][by+LEFT] == ZOMBIE)
			destory = true;
		by += LEFT;
		break;
	case Forward::right:
		if (by + RIGHT > C || map[bx][by+RIGHT] == FENCE || map[bx][by+RIGHT] == END || map[bx][by+RIGHT] == ZOMBIE)
			destory = true;
		by += RIGHT;
		break;
	}
	tch = map[bx][by];
	if (map[bx][by] == FENCE) map[bx][by] = ROAD;
	if (map[bx][by] == ZOMBIE) zombie_class::delete_zombie(bx, by);
	if(destory!=true) map[bx][by] = BULLET;
	return 0;
}
int player_class::flash_bullet_position(void)
{
	player_class::bullet_class tem, front;
	int bullet_num;
	bullet_num = player_class:: player_bullet.size();
	while (bullet_num--)
	{
		front = player_class::player_bullet.front();
		front.movebullet();
		if (front.destory != true)
			player_class::player_bullet.push(front);
		player_class::player_bullet.pop();
	}
	return 0;
}

extern queue<zombie_class> Zombie;
/*int player_class::bullet_class::bullet_incident_judge(void)
{
	int bullet_num = player_class::player_bullet.size();
	player_class::bullet_class front;
	while(bullet_num--)
	{ 
		front = player_class::player_bullet.front();
		if (map[front.bx][front.by] == ZOMBIE)
		{
			zombie_class::delete_zombie(front.bx, front.by);
			player_class::player_bullet.pop();
		}
		else
		{
			player_class::player_bullet.push(front);
			player_class::player_bullet.pop();
		}
	}
	return 0;
}*/