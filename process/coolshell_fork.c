/*************************************************************************
	> File Name: coolshell_fork.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 20时58分57秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc, const char *argv[])
{
    int i;
    for(i=0;i<2;i++)
    {
        fork();
        printf("-\n");
    }
    return 0;
}
