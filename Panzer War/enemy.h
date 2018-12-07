#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "head.h"
#include "resources.h"

//======================
//********僵尸类的宏定义*******
#define HURT 1
#define NORMAL 0

extern char  map[MAXR][MAXC];
class zombie_class //僵尸类
{
  public:
    int bfs(Node from, Node to, Forward arr_path[MAXR][MAXC]);
    zombie_class()
    {
        path_size = MAXR * MAXC * sizeof(Forward);
        /*path=(Forward (*)[MAXC])calloc(1,path_size);*/
        memset(path, Forward::noway, path_size);
        zombie_start = clock();
        zombie_cd=500;
    }
    zombie_class(int zxvaluve, int zyvalue)
        : zx(zxvaluve), zy(zyvalue),damage(1)
    {
        path_size = MAXR * MAXC * sizeof(Forward);
        memset(path, Forward::noway, path_size);
        zombie_start = clock();
        zombie_cd=500;
    }
public:
	bool iscd(void);
public:
	int flash_path(int tx, int ty);
    int movezombie(void);
public:
    Forward path[MAXR][MAXC];
    Node zombie_node;
public:
	static int flash_zombie_path(void);
	static int flash_zombie_position(void);
	static int zombie_incident_judge(void);
	static int Attack_damage;//造成的伤害总额
	static int delete_zombie(int x, int y);//从队列删除一个僵尸
private:
    Node player;
    long long zombie_cd; //ms
    long zombie_start;
    long zombie_clock;
    int path_size;
    int zx, zy;
	int damage;//一个僵尸的伤害
};

#endif
