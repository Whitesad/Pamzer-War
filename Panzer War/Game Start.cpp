#include "head.h"
#include "resources.h"
#include "enemy.h"
#include "player.h"
#include "map.h"
//_________________
//  宏函数
#define CLS system("CLS")

//一些全文件域变量
char map[MAXR][MAXC]; //地图
char map_copy[MAXR][MAXC];//拷贝的地图
int R, C;             //储存地图的行列，实际上是实际的行列各加2
int sx, sy, ex, ey;   //储存地图开始结束
int px, py;           //储存玩家的坐标
int z_num = 0;        //储存僵尸数量

//================================
//**************新建一个玩家类**********
player_class player;
//================================
//**************新建一个地图类**********
map_class MAP;
//_________________

queue<zombie_class> Zombie;
//________________________________
//一些功能函数
int moveplayer(char move); //根据传来的move指令更改地图，在地图上更改玩家的坐标
int main(void)
{
	//=============================
    //************初始化**************
	initial();
    //=============================
    //************游戏部分**************
    char move;
    while (1) //控制键盘输入
    {
        long start, end;
        for (start = clock(), end = clock(); end - start >= 40; end = clock()); //每秒分为25帧

		MAP.map_incident_judge();//地图事件判断
		if (player.return_HP() == 0)
		{
			_getch();
			printf("YOU DEAD!");
			CLS;
			goto end;
		}

		/*for (int count = 0; count < z_num; count++)
        {
            zombie_class tem = Zombie.front();
            Zombie.pop();
            if(tem.zombie_node.x==px&&tem.zombie_node.y==py)
            {
                CLS;
                printf("YOU DEAD!");
                goto end;
            }
            Zombie.push(tem);
        }*/
        //1 FPS
        MAP.print_map();
        //————————————————————————————————————
        //======================================
        //对键盘进行判断，移动玩家
        if (_kbhit())
        {
            move = _getch();
			if (move == 'w' || move == 's' || move == 'a' || move == 'd')
            {
				if (!player.iswalkcd())
				{
					player.setforward(move);
					player.moveplayer(move);
					zombie_class::flash_zombie_path();//刷新僵尸的BFS路径 
				}
			}
			else if (move == 'j')
			{
				if (!player.isguncd())
				{
					if(player.hasbullet())	player.shoot();
				}
			}
        }
		MAP.flash_map_elements();//开始移动地图上的元素，僵尸->子弹
		//zombie_class::flash_zombie_position();//开始移动僵尸在地图上的位置
		
        if( isplayerwin() )
        {
        	CLS;
        	printf("YOU WIN!");
        	break;
		}
    }
    
    char ch;
    end:printf("(按Q退出游戏)");
	while((ch=_getch())!='q');
    return 0;
}
