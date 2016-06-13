
#include <stdio.h> 

extern char ROW, COLUMN;
void frame()
{
    int x,y;
	printf("\033[2J");
    printf("\033[1;1H");//坐标    
    for(x = 0; x < ROW; x+=1)
    {

        for(y = 0; y < COLUMN; y+=1)
        {
            if((x == 0) || (x == ROW-1) || (y ==0) || (y == COLUMN-1) )
                printf("\033[45m "); //蓝    
            else 
            {
                printf("\033[0m ");    
            }
        }
        printf("\n");
    }
    printf("\033[0m");    
    printf("\n");
}
