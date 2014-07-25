/*************************************************************************
	> File Name: fork.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 01时30分02秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, const char *argv[])
{
    pid_t pid;
    char *message;
    int n;
    pid=fork();
    if(pid<0)
    {
        perror("fork failed");
        exit(-1);
    }
    if(pid==0)
    {
        message="This is the child\n";
        n=3;
    }
    else
    {
        wait(0);//阻塞等待子进程返回
        message="This is the parent\n";
        n=1;
    }

    for(;n>0;n--)
    {
        printf(message);
        sleep(30);
    }
    return 0;
}
