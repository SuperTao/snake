
#include "snake.h"
extern char eat_num;
//extern char ROW, COLUMN;
int main(int argc, char *argv[])
{
    frame();

	printf("\033[%d;%dH", ROW+1, 1);
	printf("\033[0m");
	printf("\033[32mscore: %d", eat_num);

   	srandom(time(NULL)); //随机获得点的坐标,种子

	point_pos();
	signal(SIGALRM, sig_func);
    set_timer(110);
	//alarm(1);		//定时 1 秒
    system("stty -echo raw");
    printf("\033[?25l");     //隐藏光标   
	get_dir();
   // auto_route();
    system("stty echo -raw");
	printf("\033[0m");		//清除设置
    printf("\033[?25h");     //显示光标
   
   return 0;
}
