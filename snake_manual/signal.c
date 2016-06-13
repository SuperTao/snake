//进程
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
extern char pos_y,pos_x;
extern char dir_flag;
void set_timer(int ms)
{
    struct itimerval val;
        
    val.it_interval.tv_sec = ms/1000;
    val.it_interval.tv_usec = ms%1000*1000;
    val.it_value.tv_sec = ms/1000;
    val.it_value.tv_usec = ms%1000*1000;
     
    setitimer(ITIMER_REAL, &val, NULL);
}  

void sig_func()
{
	clear_block();
	draw_block();
//	alarm(1);
}
