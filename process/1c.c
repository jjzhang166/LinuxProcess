/*************************************************************************
	> File Name: 1c.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 21时13分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, const char *argv[])
{
    while(1)
    {
        fprintf(stdout,"hello-std-out");
        //fflush(stdout);添加这一句和缺少这一句是不同的
        fprintf(stderr,"hello-std-err");
        sleep(1);
    }
    return 0;
}
