#include "enemy.h"



//类zmobie_class使用的BFS
int zombie_class::bfs(Node from, Node to, Forward arr_path[MAXR][MAXC])
{
    //for(int i=1;i<R-1;i++){for(int j=1;j<C-1;j++)printf("%d",arr_path[i][j]);printf("\n");}               //这里是曾经的古战场
    queue<Node> path;                                                                                       //无数的的编程员倒在这里
    while (!path.empty())
        path.pop(); //先清空队列                                                                            //这些被注释的代码
    memset(arr_path,Forward::noway,MAXC*MAXR*sizeof(Forward));
    path.push(to);                                                                                      //是他们曾今存在的最好证明
    Node front, tem;
    bool flag;
    flag = false;
    while (!path.empty())
    {
        if (flag)
            break;
        front = path.front();
        path.pop();
        if ((isright(front.x + UP, front.y)||front.x+UP==from.x&&front.y==from.y )&& arr_path[front.x + UP][front.y] == Forward::noway) //检查上
        {
            tem.x = front.x + UP, tem.y = front.y;
            arr_path[tem.x][tem.y] = down;
            if (tem.x == from.x && tem.y == from.y)
                flag = true;
            path.push(tem);
            // printf("\n\n\n");
            //for(int i=1;i<R-1;i++){for(int j=1;j<C-1;j++)printf("%d",arr_path[i][j]);printf("\n");}
        }
        if ((isright(front.x, front.y + RIGHT) || front.x == from.x&&front.y+RIGHT == from.y)&& arr_path[front.x][front.y + RIGHT] == Forward::noway) //检查右
        {
            tem.x = front.x, tem.y = front.y + RIGHT;
            arr_path[tem.x][tem.y] = Forward::left;
            if (tem.x == from.x && tem.y == from.y)
                flag = true;
            path.push(tem);
            // printf("\n\n\n");
            //for(int i=1;i<R-1;i++){for(int j=1;j<C-1;j++)printf("%d",arr_path[i][j]);printf("\n");}
        }
        if ((isright(front.x + DOWN, front.y) || front.x + DOWN == from.x&&front.y == from.y)&&arr_path[front.x+DOWN][front.y]==Forward::noway) //检查下
        {
            // if(arr_path[front.x+DOWN][front.y]==Forward::noway) printf("%3d",arr_path[front.x+DOWN][front.y]);
            tem.x = front.x + DOWN, tem.y = front.y;
            arr_path[tem.x][tem.y] = up;
            if (tem.x == from.x && tem.y == from.y)
                flag = true;
            path.push(tem);
            // printf("\n\n\n");
            //for(int i=1;i<R-1;i++){for(int j=1;j<C-1;j++)printf("%d",arr_path[i][j]);printf("\n");}
        }
        if ((isright(front.x, front.y + LEFT) || front.x == from.x&&front.y+LEFT == from.y)&& arr_path[front.x][front.y + LEFT] == Forward::noway) //检查左
        {
            tem.x = front.x, tem.y = front.y + LEFT;
            arr_path[tem.x][tem.y] = Forward::right;
            if (tem.x == from.x && tem.y == from.y)
                flag = true;
            path.push(tem);
            // printf("\n\n\n");
            //for(int i=1;i<R-1;i++){for(int j=1;j<C-1;j++)printf("%d",arr_path[i][j]);printf("\n");}
        }
    }
    return 0;
}
int zombie_class::movezombie(void)
{
    map[zx][zy]=ROAD;
    switch (path[zx][zy])
    {
    case Forward::up:
        zx += UP;
        break;
    case Forward::down:
        zx += DOWN;
        break;
    case Forward::right:
        zy += RIGHT;
        break;
    case Forward::left:
        zy += LEFT;
        break;
    case Forward::noway:
        break;
    }
    map[zx][zy]=ZOMBIE;
    zombie_node.x=zx,zombie_node.y=zy;
    return 0;
}

int zombie_class::flash_path(int tx, int ty)
{
	zombie_node.x = zx, zombie_node.y = zy;
	player.x = tx, player.y = ty;
	bfs(zombie_node, player, path);
	return 0;
}
bool zombie_class::iscd(void)
{
	zombie_clock = clock();
	if ((zombie_clock - zombie_start) >= zombie_cd)
	{
		zombie_start = clock(); //刷新cd
		return false;
	}
	else
		return true;
}

extern int px, py;
extern queue<zombie_class> Zombie;
extern char map[MAXR][MAXC];
int zombie_class::flash_zombie_path(void)
{
	int zombie_num = Zombie.size();
	for (int count = 0; count < zombie_num; count++)
	{
		zombie_class tem = Zombie.front();
		Zombie.pop();
		tem.flash_path(px, py);
		Zombie.push(tem);
	}
	return 0;
}
int zombie_class::flash_zombie_position(void)
{
	int zombie_num = Zombie.size();
	for (int count = 0; count < zombie_num; count++)
	{
		zombie_class tem = Zombie.front();
		Zombie.pop();
		if (!tem.iscd()) tem.movezombie();
		Zombie.push(tem);
	}
	return 0;
}
int zombie_class::Attack_damage = 0;
int zombie_class::zombie_incident_judge(void)
{
	zombie_class::Attack_damage = 0;
	int result=NORMAL;
	int zombie_num = Zombie.size();
	for (int count = 0; count < zombie_num; count++)
	{
		zombie_class tem = Zombie.front();
		Zombie.pop();
		if (tem.zombie_node.x == px && tem.zombie_node.y == py)
		{
			zombie_class::Attack_damage += tem.damage;
			result = HURT;
		}
		Zombie.push(tem);
	}
	return result;
}
int zombie_class::delete_zombie(int x, int y)
{
	int zombie_num = Zombie.size();
	zombie_class front;
	while (zombie_num--)
	{
		front = Zombie.front();
		if (front.zombie_node.x == x && front.zombie_node.y == y)
		{
			map[front.zombie_node.x][front.zombie_node.y] = ROAD;
			Zombie.pop();
			break;
		}
		else
		{
			Zombie.push(front);
			Zombie.pop();
		}
	}
	return 0;
}