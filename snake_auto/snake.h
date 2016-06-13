
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define ROW 	30
#define COLUMN	30
#define legth 5

void sig_func();
void change_dir();
void point_pos();
void auto_route();
void set_timer(int);



#endif //_SNAKE_H_
