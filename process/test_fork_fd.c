/*************************************************************************
	> File Name: test_fork_fd.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 14时24分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#define ERR_EXIT(m)\
    do{\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
int main(int argc, const char *argv[])
{
    int fd=open("test.txt",O_RDONLY);
    if(fd==-1)
        ERR_EXIT("open");

    pid_t pid;
    if((pid=fork())<0)
        ERR_EXIT("fork");
    else if(pid==0)
    {
        char buf[10]={0};
        read(fd,buf,3);
        printf("in child buf =%s\n",buf);
        close(fd);//这里关闭fd,使得计算器减少1
    }
    else
    {
        sleep(3);//先让子进程执行;
        char buf[10]={0};
        read(fd,buf,3);
        printf("in parent buf =%d\n",buf);
        close(fd);
    }
    return 0;
}
