#include "resources.h"
#include "enemy.h"
#include "player.h"
extern player_class player;
extern char map[MAXR][MAXC];//引入地图，map最开始在main中被定义 
extern char map_copy[MAXR][MAXC];
extern int R;
extern int C;
extern int sx,sy,ex,ey;
extern int px,py;
extern int z_num;
extern queue<zombie_class> Zombie;
extern char towards;
extern player_class player;
void gotoxy(int x, int y) //将光标移动到坐标为(x,y)的地方
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    HANDLE hConsoleOut;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
    csbiInfo.dwCursorPosition.X = x;
    csbiInfo.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
int isright(int x, int y) //检测点是否能走
{
	if (map[x][y] != FENCE && map[x][y] != EDGE && map[x][y] != END&&map[x][y]!=ZOMBIE)
        return true;
    else
        return false;
}
int store_map(void)
{
    freopen("maze.txt","r",stdin);
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) //建图
    {
        scanf("%s", map[i]);
        getchar();
        for (int j = 0; j < C; j++)
        {
            switch (map[i][j])
            {
            case 'S':
                map[i][j] = PLAYER;
                sx = i;
                sy = j;
                px = i;
                py = j;
                break;
            case '#':
                map[i][j] = FENCE;
                break;
            case '.':
                map[i][j] = ROAD;
                break;
            case 'G':
                map[i][j] = END;
                ex = i;
                ey = j;
                break;
            case '$':
                map[i][j] = EDGE;
                break;
            case 'Z':
            	zombie_class tem=zombie_class(i, j);
            	tem.zombie_node.x=i,tem.zombie_node.y=j;
                Zombie.push(tem); //将一个僵尸入队
                z_num++;
                map[i][j] = ZOMBIE;
                break;
            }
        }
    }
    memcpy(map_copy,map,MAXR*MAXC*sizeof(char));
    return 0;
}
void initial(void)
{
	system("chcp 936");
	system("CLS");


	//================================
    //***********读取地图************
    store_map();
    //=================================
    //*********初始化僵尸的路径************
    for (int count = 0; count < z_num; count++)
    {
        zombie_class tem = Zombie.front();
        Zombie.pop();
        tem.flash_path(px,py);
        Zombie.push(tem);
    }
    //===============================
    //**************打印地图框架***********
    for(int i=1;i<R-1;i++)
    {
        for(int j=1;j<C-1;j++)
        switch (map[i][j])
                {
                case START:
                    printf("◆");
                    break;
                case FENCE:
                    printf("※");
                    break;
                case ROAD:
                    printf("　");
                    break;
                case END:
                    printf("◇");
                    break;
                case PLAYER:
                    printf("○");
                    break;
                case ZOMBIE:
                    printf("●");
                    break;
                }
        printf("\n");
    }
	gotoxy(HP_X, R + 1);
	printf("HP:%d", player.return_HP());
	gotoxy(BULLET_X, R + 1);
	printf("BULLET:%d", player.return_BULLET());
    gotoxy(0, 0);
}
bool isplayerwin(void)
{
	if(px == ex && py == ey) return true;
	else return false;
}

/*int print(void)
{
    for(int i=1;i<R-1;i++)
    {
        for(int j=1;j<C-1;j++)
        {
            if(map[i][j]!=map_copy[i][j]){
                gotoxy(2*(j-1),i-1);
                switch (map[i][j])
                {
                case START:
                    printf("◆");
                    break;
                case FENCE:
                    printf("※");
                    break;
                case ROAD:
                    printf("　");
                    break;
                case END:
                    printf("◇");
                    break;
                case PLAYER:
                    if(player.player_forward==Forward::down) printf("┯");
                    else if(player.player_forward == Forward::up) printf("┷");
                    else if(player.player_forward == Forward::left) printf("┥");
                    else if(player.player_forward == Forward::right) printf("├");
                    break;
                case ZOMBIE:
                    printf("●");
                    break;
                }
            }
        }
    }
    gotoxy(0,0);
    memcpy(map_copy,map,sizeof(map));
    return 0;
}*/
/*int flash_zombie_path(void)
{
	for (int count = 0; count < z_num; count++)
    {
        zombie_class tem = Zombie.front();
        Zombie.pop();
        tem.flash_path(px,py);
        Zombie.push(tem);
    }
    return 0;
}
int flash_zombie_position(void)
{
	for (int count = 0; count < z_num; count++)
    {
    	zombie_class tem = Zombie.front();
        Zombie.pop();
        if(!tem.iscd()) tem.movezombie();
        Zombie.push(tem);
    }
    return 0;
}*/
