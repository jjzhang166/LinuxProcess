/*************************************************************************
	> File Name: 1fork.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月24日 星期四 22时46分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define ERR_EXIT(m)\
    do{\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
int main(int argc, const char *argv[])
{
    fork();
    fork();
    fork();
    printf("hello\n");
    exit(0);
}
