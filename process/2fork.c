/*************************************************************************
	> File Name: 2fork.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月24日 星期四 23时44分36秒
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
       // printf("- \n");
        printf("- ");
    }
    return 0;
}
