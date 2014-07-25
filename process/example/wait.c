/*************************************************************************
	> File Name: wait.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 22时01分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
int main(int argc, const char *argv[])
{
    pid_t pid;
    if((pid=fork())==-1)
        ERR_EXIT("fork");
    else if(pid==0)
    {
        //子进程成功退出
        exit(EXIT_SUCCESS);
    }
    else
    {
        int ret=wait(NULL);
        printf("child = %d\n",ret);

        while(1);
    }
    return 0;
}
