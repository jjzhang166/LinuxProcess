/*************************************************************************
	> File Name: zombie_signal.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 19时28分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
#define N 10

//处理SIGCHLD，防止僵尸进程
void handler(int signum)
{
    //处理函数将if改写为while就可以尽可能多的处理问题
    pid_t pid;
    while((pid=waitpid(-1,NULL,0))>0)
    {
        printf("Handler process child %d\n",pid);
        sleep(2);//故意去阻塞别的sigchld信号
    }

    /*if((pid=waitpid(-1,NULL,0))<0)
         ERR_EXIT("Waitpid");
    printf("Handler process child %d\n",pid);
    sleep(2);//这里之所以sleep(2),就是故意阻塞别的SIGCHLD
    */
    //已达到验证信号量阻塞的问题
}
int main(int argc, const char *argv[])
{
    if(signal(SIGCHLD,handler)==SIG_ERR)
        ERR_EXIT("signal");//这里是父进程注册信号量的的处理函数
    pid_t pid;

    int i;
    for(i=0;i<N;++i)
    {
        if((pid=fork())<0)
            ERR_EXIT("fork");
        else if(pid==0)
        {
            //子进程打印完信息后就退出:退出码：EXIT_SUCCESS
            printf("Hello from child %d\n",getpid());
            sleep(2);
            exit(EXIT_SUCCESS);
        }
    }
    
    int n;
    char buf[1024];
    //父进程采用read函数调用阻塞到这里
    if((n=read(STDIN_FILENO,buf,1000))<0)
        ERR_EXIT("read error");

    printf("Parent process input\n");

    while(1)
        ;
    return 0;
}

