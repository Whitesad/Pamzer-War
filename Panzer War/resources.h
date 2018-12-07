#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include "head.h"



//______________
//预定义常量 
#define MAXR 100
#define MAXC 100
#define HP_X 0
#define BULLET_X 10

//________________
// 地图组成元素
#define START 0
#define FENCE 1
#define ROAD 2
#define END 3
#define PLAYER 4
#define EDGE 5
#define ZOMBIE 6
#define BULLET 7

//_________________
//  方向
#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1

//________________
//一些预定义结构
typedef struct node
{
    int x, y;
} Node;
typedef enum Fowar
{
    noway,
    up,
    down,
    right,
    left
} Forward;


void gotoxy(int x, int y); //将光标移动到坐标为(x,y)的地方
int isright(int x, int y);//检测点是否能走,不为FENCE与EDGE即为能走 
int store_map(void);      //从map.txt读取地图并储存地图
int print(void);          //基于比较刷新的打印函数 
void initial(void);
/*int flash_zombie_path(void);
int flash_zombie_position(void);*/
bool isplayerwin(void);
#endif
