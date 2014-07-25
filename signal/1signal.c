/*************************************************************************
	> File Name: 1signal.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 15时31分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<errno.h>
#include<unistd.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef void(*sighandler_t)(int);
//自己定义的信号处理函数
void handler(int signum)
{
    printf("Ctrl + C\n");
}
int main(int argc, const char *argv[])
{
    sighandler_t old;
    if((old=signal(SIGINT,handler))==SIG_ERR)
        ERR_EXIT("signal");

    if(signal(SIGQUIT,SIG_IGN)==SIG_ERR)//忽略SIGQUIT信号
        ERR_EXIT("signal");

    for(;;)
        pause();//暂停程序，直到接收到信号
    return 0;
}
