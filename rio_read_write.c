#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>

#define ERR_EXIT(m)\
    do{\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
#define MAXLINE 1024
#define RIO_BUFFER 8192

typedef struct
{
    int fd_;//要读取的fd
    int left_;//unread bytes in internal buf........
    char *bufptr_;//缓冲区有效数据的其实位置
    char buffer_[RIO_BUFFER];//缓冲区
}rio_t;

void rio_init(rio_t *rp, int fd)
{
    rp->fd_=fd;
    rp->left_=0;
    rp->bufptr_=rp->buffer_;
}
//rio_read应该提供和read相同的功能
ssize_t rio_read(rio_t *rp,char *usrbuf,size_t n)
{
    ssize_t nread;
    //如果缓冲区里面没有数据就应该进行预读取
    //不是每次调用rio_read都会进行预读取
    //
    //如果当前缓冲区中有数据的话，rp->left_肯定大于零
    //下面的while语句就不会执行也不会出现read系统调用
    while(rp->left_<=0)
    {
        nread=read(rp->fd_,rp->buffer_,sizeof(rp->buffer_));
        //出错处理
        if(nread==-1)
        {
            if(errno==EINTR)//是因为中断
                continue;
            return -1;//真真正正出错啦
        }
        else if(nread==0)
            return 0;//遇到EOF的时候
        rp->left_=nread;
        rp->bufptr_=rp->buffer_;//重置缓冲区的指针
    }
    

    //到达这里，buffer中一定存在数据
    int cnt=n;
    //如果缓冲区可提供的字节数小于用户要求的n
    //此时应提供缓冲区剩余的字节数
    if(rp->left_<n)
        cnt=rp->left_;
    memcpy(usrbuf,rp->bufptr_,cnt);//执行真正的数据拷贝
    rp->left_-=cnt;
    rp->bufptr_+=cnt;
    return cnt;
}

ssize_t rio_readn(rio_t *rp, void *usrbuf, size_t n)
{
    size_t nleft=n;
    ssize_t nread;
    char *bufp=usrbuf;
    
    while(nleft>0)
    {
        nread=rio_read(rp,bufp,nleft);
        if(nread==-1)
            return -1; //这里不需要处理EINTR 是因为在rio_read这个函数内部已经考虑
        //了中断处理
        else if(nread==0)//遇到EOF
            break;

        nleft-=nread;
        bufp+=nread;
    }
    return (n-nleft);
}

ssize_t rio_readline(rio_t *rp, char *usrbuf, size_t maxlen)
{
    char *bufp=usrbuf;
    char c;
    int nread;
    int i;

    //最多读取maxlen-1个字节，留一个位置为\0
    for(i=0;i<maxlen-1;++i)
    {
        //这里也是读取一个字节
        //但是rio_read内部采用了buffer机制
        //所以这里的效率并没有降低，因为在调用rio_read只有缓冲区中没有数据的时候
        //才会启动read系统调用
        nread=rio_read(rp,&c,1);
        if(nread==-1)
            return -1;
        else if(nread==0)
        {
            if(i==0)//第一个字符读取遇到EOF
                return 0;
            break;//这里可能已经读取了部分字节
        }
        *bufp++=c;//字符放在用户缓冲区
        if(c=='\n')
            break;  //在未达到maxlen-1的时候遇到换行符
    }
    *bufp='\0';
    return i;//返回成功读取的字节数，不包括最后的\0
}

ssize_t rio_writen(int fd,void *usrbuf,size_t n)
{
    size_t nleft=n;
    size_t nwrite;
    char *bufp=usrbuf;

    while(nleft>0)//也就是说只要缓冲区没填满就一直循环
    {
        //nwrite==0也属于错误
        if((nwrite=write(fd,bufp,nleft))<=0)
        {
            if(errno=EINTR)
                nwrite=0;
            else
                return -1;//也就是说发生错误的时候才会return -1
        }
        nleft-=nwrite;
        bufp+=nwrite;
    }
    return n;//这里不是n-nleft必须是n
}

int main(int argc, const char *argv[])
{
    /*
    rio_t rio;
    rio_init(&rio,STDIN_FILENO);
    int ret;
    char buf[1024]={0};

    while((ret=rio_readline(&rio,buf,1024))>0)
    {
        rio_writen(STDOUT_FILENO,buf,strlen(buf));
    }
    */
    int fd=open("test.txt",O_RDONLY);
    if(fd==-1)
        ERR_EXIT("open");
    rio_t rio;
    rio_init(&rio,fd);
    
    int ret;
    char buf[MAXLINE];
    while((ret=rio_readline(&rio,buf,MAXLINE))>0)
        rio_writen(STDOUT_FILENO,buf,strlen(buf));
    return 0;
}
