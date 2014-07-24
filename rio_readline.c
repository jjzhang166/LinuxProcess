#include<stdio.h>

#define RIO_BUFFER 8292
typedef struct
{
    int fd_;
    int left_;
    char *bufptr_;
    char buffer_[RIO_BUFFER];
}rio_t;
