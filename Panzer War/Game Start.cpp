#include "head.h"
#include "resources.h"
#include "enemy.h"
#include "player.h"
#include "map.h"
//_________________
//  �꺯��
#define CLS system("CLS")

//һЩȫ�ļ������
char map[MAXR][MAXC]; //��ͼ
char map_copy[MAXR][MAXC];//�����ĵ�ͼ
int R, C;             //�����ͼ�����У�ʵ������ʵ�ʵ����и���2
int sx, sy, ex, ey;   //�����ͼ��ʼ����
int px, py;           //������ҵ�����
int z_num = 0;        //���潩ʬ����

//================================
//**************�½�һ�������**********
player_class player;
//================================
//**************�½�һ����ͼ��**********
map_class MAP;
//_________________

queue<zombie_class> Zombie;
//________________________________
//һЩ���ܺ���
int moveplayer(char move); //���ݴ�����moveָ����ĵ�ͼ���ڵ�ͼ�ϸ�����ҵ�����
int main(void)
{
	//=============================
    //************��ʼ��**************
	initial();
    //=============================
    //************��Ϸ����**************
    char move;
    while (1) //���Ƽ�������
    {
        long start, end;
        for (start = clock(), end = clock(); end - start >= 40; end = clock()); //ÿ���Ϊ25֡

		MAP.map_incident_judge();//��ͼ�¼��ж�
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
        //������������������������������������������������������������������������
        //======================================
        //�Լ��̽����жϣ��ƶ����
        if (_kbhit())
        {
            move = _getch();
			if (move == 'w' || move == 's' || move == 'a' || move == 'd')
            {
				if (!player.iswalkcd())
				{
					player.setforward(move);
					player.moveplayer(move);
					zombie_class::flash_zombie_path();//ˢ�½�ʬ��BFS·�� 
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
		MAP.flash_map_elements();//��ʼ�ƶ���ͼ�ϵ�Ԫ�أ���ʬ->�ӵ�
		//zombie_class::flash_zombie_position();//��ʼ�ƶ���ʬ�ڵ�ͼ�ϵ�λ��
		
        if( isplayerwin() )
        {
        	CLS;
        	printf("YOU WIN!");
        	break;
		}
    }
    
    char ch;
    end:printf("(��Q�˳���Ϸ)");
	while((ch=_getch())!='q');
    return 0;
}
