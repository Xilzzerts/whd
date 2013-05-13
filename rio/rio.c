#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "rio.h"

ssize_t rio_readn(int fd, void *buf, size_t n)
{
    ssize_t nread;
    size_t  nleft = n;
    char    *bp = (char *)buf;

    while(nleft > 0)
    {
        if((nread = read(fd, bp, nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        bp    += nread;
    }
    return (n - nleft);
}

ssize_t rio_writen(int fd, void *buf, size_t n)
{
    ssize_t nwritten;
    size_t  nleft = n;
    char    *bp = (char *)buf;

    while(nleft > 0)
    {
        if((nwritten = write(fd, bp, nleft)) <= 0)
        {
            if(errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        bp    += nwritten;
    }
    return n;
}

void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

static ssize_t rio_read(rio_t *rp, void *buf, size_t n)
{
    ssize_t cnt;
    while(rp->rio_cnt <= 0)
    {
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        if(rp->rio_cnt < 0)
        {
            if(errno != EINTR)
                return -1;
        }
        else if(rp->rio_cnt == 0)
            return 0;
        else
            rp->rio_bufptr = rp->rio_buf;
    }

    cnt = n;
    if(rp->rio_cnt < n)
        cnt = rp->rio_cnt;
    memcpy(buf, rp->rio_bufptr, cnt);
    rp->rio_cnt -= cnt;
    rp->rio_bufptr += cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *buf, size_t n)
{
    size_t i, ret;
    char c;
    char *bp = (char *)buf;
    for(i = 1; i < n; ++i)
    {
        if((ret = rio_read(rp, &c, 1)) == 1)
        {
            *bp++ = c;
            if(c == '\n')
                break;
        }
        else if(ret == 0)
        {
            if(i == 1)
                return 0;
            else break;
        }
        else
            return -1;
    }
    *bp = '\0';
    return i;
}

ssize_t rio_readnb(rio_t *rp, void *buf, size_t n)
{
    ssize_t nread;
    size_t  nleft = n;
    char    *bp = (char *)buf;

    while(nleft > 0)
    {
        if((nread = rio_read(rp, bp ,nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        bp    += nread;
    }
    return (n - nleft);
}

