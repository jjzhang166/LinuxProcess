/*************************************************************************
	> File Name: 5fork.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 00时43分24秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
int main(int argc, const char *argv[])
{
    int i;
    fork();
    printf("input a number:\n");
    scanf("%d",&i);
    printf("i=%d",i);
    return 0;
}
