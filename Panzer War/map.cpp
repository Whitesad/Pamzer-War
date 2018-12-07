#include "map.h"
#include "player.h"
#include "enemy.h"
int map_class::bfs(Node from, Node to, Forward arr_path[MAXR][MAXC])
{
    static queue<Node> path; //一个实际上是给bfs用的队列
    while (!path.empty())
        path.pop(); //先清空队列
    path.push(to);
    Node front, tem;
    while (!path.empty())
    {
        front = path.front();
        path.pop();
        if (isright(front.x + UP, front.y)) //检查上
        {
            tem.x = front.x + UP, tem.y = front.y;
            arr_path[tem.x + UP][tem.y] = down;
            if (tem.x + UP == to.x && tem.y == to.y)
                return 0;
            path.push(tem);
        }
        if (isright(front.x, front.y + RIGHT)) //检查右
        {
            tem.x = front.x, tem.y = front.y + RIGHT;
            arr_path[tem.x][tem.y + RIGHT] = Forward::left;
            if (tem.x == to.x && tem.y + RIGHT == to.y)
                return 0;
            path.push(tem);
        }
        if (isright(front.x + DOWN, front.y)) //检查下
        {
            tem.x = front.x + DOWN, tem.y = front.y;
            arr_path[tem.x + DOWN][tem.y] = up;
            if (tem.x + DOWN == to.x && tem.y == to.y)
                return 0;
            path.push(tem);
        }
        if (isright(front.x, front.y + LEFT)) //检查左
        {
            tem.x = front.x, tem.y = front.y + LEFT;
            arr_path[tem.x][tem.y + LEFT] = Forward::right;
            if (tem.x == to.x && tem.y + LEFT == to.y)
                return 0;
            path.push(tem);
        }
    }
    return 0;
}
extern player_class player;
int map_class::flash_map_elements(void)
{
	zombie_class::flash_zombie_position();//在地图上刷新僵尸的位置
	player.flash_bullet_position();//在地图上刷新子弹的位置
	return 0;
}
extern player_class player;
extern queue<zombie_class> Zombie;
int map_class::map_incident_judge(void)
{
	if (zombie_class::zombie_incident_judge() == HURT)
		player.get_hurt(zombie_class::Attack_damage);
	//player_class::bullet_class::bullet_incident_judge();

	return 0;
}
extern char map[MAXR][MAXC];
extern char map_copy[MAXR][MAXC];
extern int R, C;
extern int px, py;
int map_class::print_map(void)
{
	static Forward tem_forward = Forward::down;
	for (int i = 1; i < R - 1; i++)
	{
		for (int j = 1; j < C - 1; j++)
		{
			if (map[i][j] != map_copy[i][j]) {
				gotoxy(2 * (j - 1), i - 1);
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
					if (player.player_forward == Forward::down) printf("┯");
					else if (player.player_forward == Forward::up) printf("┷");
					else if (player.player_forward == Forward::left) printf("┥");
					else if (player.player_forward == Forward::right) printf("├");
					break;
				case ZOMBIE:
					printf("●");
					break;
				case BULLET:
					printf("¤");
					break;
				}
			}
		}
	}
	if (player.player_forward != tem_forward)
	{
		gotoxy(2 * (py - 1),px-1 );
		if (player.player_forward == Forward::down) printf("┯");
		else if (player.player_forward == Forward::up) printf("┷");
		else if (player.player_forward == Forward::left) printf("┥");
		else if (player.player_forward == Forward::right) printf("├");
		tem_forward = player.player_forward;
	}
	gotoxy(0, 0);
	memcpy(map_copy, map, sizeof(map));
	return 0;
}