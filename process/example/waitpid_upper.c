/*************************************************************************
	> File Name: waitpid.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 22时06分06秒
 ************************************************************************/

/*
 *waitpid的功能就是在此处是处理子进程退出后回收资源的问题
 *比如说防止僵尸进程的产生
 *
 * */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/types.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
#define N 10
int main(int argc, const char *argv[])
{
    pid_t pid[N];//存储子进程ID
    int i;
    for(i=0;i<N;i++)
    {
        //父进程创建完子进程继续循环
        //子进程直接退出
        pid[i]=fork();
        if(pid[i]==-1)
            ERR_EXIT("fork");
        else if(pid[i]==0)
            exit(100+i);//子进程返回了状态码
    }
    int status;//接收子进程的状态
    pid_t ret;
    i=0;
    while((ret=waitpid(pid[i],&status,0))>0)
    {
        if(WIFEXITED(status))//如果该进程正常退出
            printf("child %d terminated nomally with code :%d\n",pid[i],WEXITSTATUS(status));
        else
            printf("child %d terminated nomally with conde:%d\n",pid[i]);
        ++i;
    }

    /*
     *
     *异步回收子进程
     * */
    //创建10个子进程，waitpid在循环内执行了11次
    //最后一次是失败的
    if(errno!=ECHILD)
        ERR_EXIT("waitpid");
    return 0;
}
