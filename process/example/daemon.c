/*************************************************************************
	> File Name: daemon.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 22时36分39秒
 ************************************************************************/

/*
 * 守护进程的编写流程
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
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
    else if(pid>0)
        exit(EXIT_SUCCESS);//确保出现孤儿进程

    setsid();//创建一个新的会话，脱离shell的会话期
    chdir("/");//更改工作目录
    umask(0);

    /*
    int i;
    for(=0;i<3;i++)
        close(i);
    open("/dev/null");//打开0
    dup(0);//1
    dup(0);//2
    */

    // /dev/null 
    // 如果stdin重定向到/dev/null,那么一旦尝试read,立刻返回EOF
    // 如果是stdout,stderr,输出全部被抛弃
    int fd=open("/dev/null",O_WRONLY);
    if(fd==-1)
        ERR_EXIT("OPEN");
    dup2(fd,STDIN_FILENO);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);
    close(fd);
    while(1);
    return 0;
}
/*
 * 1、后台运行，为避免挂起控制终端将Dameon放入后台执行，方法是
 * 在进程中调用fork使得父进程终止，让Daemon在子进程中后台执行
 * 2、脱离控制终端，登录会话和进程组
 * */
