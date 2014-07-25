/*************************************************************************
	> File Name: 01fork.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 21时47分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
int main(int argc, const char *argv[])
{
    printf("enter main....\n");
    
    //使用command 中的代码替换当前镜像
    execlp("ls","ls","-l",NULL);

    printf("leave main.....\n");
    return 0;
}
