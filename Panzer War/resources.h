#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include "head.h"



//______________
//Ԥ���峣�� 
#define MAXR 100
#define MAXC 100
#define HP_X 0
#define BULLET_X 10

//________________
// ��ͼ���Ԫ��
#define START 0
#define FENCE 1
#define ROAD 2
#define END 3
#define PLAYER 4
#define EDGE 5
#define ZOMBIE 6
#define BULLET 7

//_________________
//  ����
#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1

//________________
//һЩԤ����ṹ
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


void gotoxy(int x, int y); //������ƶ�������Ϊ(x,y)�ĵط�
int isright(int x, int y);//�����Ƿ�����,��ΪFENCE��EDGE��Ϊ���� 
int store_map(void);      //��map.txt��ȡ��ͼ�������ͼ
int print(void);          //���ڱȽ�ˢ�µĴ�ӡ���� 
void initial(void);
/*int flash_zombie_path(void);
int flash_zombie_position(void);*/
bool isplayerwin(void);
#endif
