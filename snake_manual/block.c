#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#define legth 5
int pos[100][2] = {
	{5, 2},{4, 2},{3, 2},{2, 2},{1, 2},{7, 3},{6, 3},{5, 0},{4, 0},{3, 0}
};		//二维数组，保存每个点的坐标值
char ROW = 30, COLUMN = 30;
char ch;
char b_num;     //
char pos_x=1,pos_y=0;
char dir_flag = 'C';  //贪吃蛇运动方向标志位,初始默认 向右 运动
char dir_limit = 'D';		//方向限制，不能直接向相反方向运动
char eat_flag = 0;		//点是否被吃标志
char eat_num = 0;		//所吃点的个数
char point_x, point_y;	//点的坐标（随机）
char start_x = 3, start_y = 1;	//贪吃蛇头所在位置对应数组坐标
char end_x = 1, end_y = 1;		//贪吃蛇尾所在位置对应数组坐标
char gameover = 0;

void point_pos()
{
    int i, flag;
	while(1)
	{
        flag = 0;
    	point_x = random()%COLUMN;	//随机获得点的x轴坐标
		point_y = random()%ROW;		//随机获得点的y轴坐标
        for(i = 0; i < (legth +eat_num); i++)
        {
            if(point_x == pos[i][0] && point_y == pos[i][1])
            {
                flag = 1;
            }
        }
        if(flag == 1) continue;
		if(point_x > 1 && point_y > 1)	//防止点到边框上
		{
			printf("\033[%d;%dH\033[41m ", point_y, point_x);
			break;
		}
		else
			continue;
	}
}

void clear_block()
{
	char x, y;
    for(y = 2; y < ROW ; y++)
    {
        for(x = 2; x < COLUMN; x++)
        {
            printf("\033[%d;%dH", y, x);
            printf("\033[0m ");
        }
    }
	fflush(NULL);
}

void draw_block()
{
	int x, y, i;	
	
	//判断是否吃到点
	if(pos[0][1] == point_y && pos[0][0] == point_x)
	{
		eat_num += 1;
		eat_flag = 1;
		printf("\033[%d;%dH", ROW+1, 1);
		printf("\033[0m");
		printf("\033[32mscore: %d", eat_num);
	}
	if(eat_flag == 1)
	{
		eat_flag = 0;
		point_pos();
	}

	//	更新点坐标
	printf("\033[%d;%dH", point_y, point_x);
	printf("\033[41m ");

	for(y = legth-1 + eat_num; y > 0; y-=1)
	{
		pos[y][0] = pos[y-1][0];		//移动，更新x轴坐标值
		pos[y][1] = pos[y-1][1];		//移动，更新y轴坐标值
	}
	pos[0][0] = pos[0][0] + pos_x;
	pos[0][1] = pos[0][1] + pos_y;

	
	//更新显示,头用色
	printf("\033[%d;%dH", pos[0][1], pos[0][0]);
	printf("\033[0m\033[34m@");
	for(x = 1; x <= (legth-1 + eat_num); x+=1)
	{
       	printf("\033[%d;%dH", pos[x][1], pos[x][0]);
		printf("\033[0m\033[34m*");
	}
	fflush(NULL);
		//蛇碰到外框，game over
		if(pos[0][0]==1 || pos[0][0]==COLUMN || pos[0][1]==1 || pos[0][1]==ROW)
		{
			printf("\033[%d;%dH", ROW+2, 1);
			printf("\033[0m\033[32mgame over\n");
			printf("\033[0m");
			printf("\033[%d;%dH", ROW+3, 1);
			printf("\033[?25h");
			system("stty echo -raw");	
			exit(0);
		}
		//蛇碰到自己，game over
		for(i = 1; i < legth + eat_num; i++)
		{
			if(pos[0][0] == pos[i][0] && pos[0][1] == pos[i][1])
			{
			printf("\033[%d;%dH", ROW+2, 1);
			printf("\033[0m\033[32mgame over\n");
			printf("\033[0m");
			printf("\033[%d;%dH", ROW+3, 1);
			printf("\033[?25h");
			system("stty echo -raw");	
			exit(0);
			}
		}

}
void auto_route()
{
    int record_x, record_y;
    while(1)
    {
        record_x = pos[0][0] - point_x;
        record_y = pos[0][1] - point_y;
        if(record_x > 0)
        {
            pos_x = -1;
            pos_y = 0;
        }
        else if(record_x < 0)
        {
            pos_x = 1;
            pos_y = 0;
        }
        else if(record_x == 0 && record_y > 0)
        {
            pos_y = -1;
            pos_x = 0;
        }
        else if(record_x == 0 && record_y < 0)
        {
            pos_y = 1;
            pos_x = 0;
        }
        if(eat_num == 35)
        {
            	printf("\033[%d;%dH", ROW+2, 1);
			printf("\033[0m\033[32mgame over\n");
			printf("\033[0m");
			printf("\033[%d;%dH", ROW+3, 1);
			printf("\033[?25h");
			system("stty echo -raw");	
			exit(0);

        }
    }
}
void get_dir()
{
	while(1)
	{
    	ch = getchar();
    	if(ch == 'q')
		{
			printf("\033[%d;%dH", ROW + 2, 1);
		    break;
		}
    	if(ch != '\033')
        	continue;
    	if(getchar() != '[')
        	continue;
    	ch = getchar();
		if(ch == 'A' && dir_limit != 'A')
		{
          	pos_y = -1;        //up
			pos_x = 0;
			dir_limit  = 'B';
		}
		else if(ch == 'B' && dir_limit != 'B')
		{
          	pos_y = 1;        //down
			pos_x = 0;
			dir_limit  = 'A';
		}
		else if(ch == 'C' && dir_limit != 'C')
		{
          	pos_x = 1;        //right
			pos_y = 0;
			dir_limit  = 'D';
		}
		else if(ch == 'D' && dir_limit != 'D')
		{
          	pos_x = -1;        //left
			pos_y = 0;
			dir_limit  = 'C';
		}
        draw_block();
	}
}

