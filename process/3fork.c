/*************************************************************************
	> File Name: 3fork.c
	> Author: xuxiaoqiang
	> Mail:353271054@qq.com 
	> Created Time: 2014年07月25日 星期五 00时24分05秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc, const char *argv[])
{
    int i;
    for(i=0;i<2;i++)
    {
    sleep(10);//让程序停留十秒，这样我们可以用pstree查看一下进程树：
        fork();
        //注意：下面的printf有"\n"
        printf("ppid=%d, pid=%d ,i=%d \n",getppid(),getpid(),i);
    }
    return 0;
}
