/*************************************************************************
	> File Name: 02forkexec.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 21时58分32秒
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
    if((pid=fork())<0)
        ERR_EXIT("fork");
    else if(pid==0)
        //子进程发生替换
        execlp("ls","ls","-l",NULL);
    else
        sleep(10);
    return 0;
}
