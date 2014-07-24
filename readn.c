/*************************************************************************
	> File Name: readn.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月24日 星期四 20时57分24秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
/*
 * 详细内容见有道笔记0724
 * 这里的readn函数仅仅是起到封装的作用
 * 详见：深入理解计机系统+ UNIX网络编程
 * */
ssize_t readn(int fd,void *ptr,size_t n)
{
    size_t nleft;//还需要读取的字节数
    size_t nread;//用来接收中间的返回值

    nleft=n;
    while(nleft>0)
    {
        if((nread=read(fd,ptr,nleft))<0)
        {
            if(errno=EINTR)
                nread=0;//continue 如果碰到中断，再次读取
            else
                return -1;//出现error的情况
        }
        else if(nread==0)
            break;
        nleft-=nread;
        ptr+=nread;
    }
    return n-nleft;
}
int main(int argc, const char *argv[])
{
    char buf[1024]={0};
    int fd=open("readn.txt",O_RDONLY,0666);
    if(fd==-1)
    {
        perror("open");
        exit(-1);
    }
    //int ret=readn(STDIN_FILENO,buf,1024);
    //
    //通过readn.txt文件进行测试
   int  ret=readn(fd,buf,1024);
    //上面的readn函数要想退出来就必须遇到EOF结束标记
    printf("%s",buf);
    //write(STDOUT_FILENO,buf,strlen(buf));
    return 0;
}
