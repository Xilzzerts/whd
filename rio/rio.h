#ifndef _RIO_H_
#define _RIO_H_

#define MAXLEN 8192

typedef struct
{
    int  rio_fd;
    int  rio_cnt;
    char *rio_bufptr;
    char rio_buf[MAXLEN];
}rio_t;

ssize_t rio_readn(int fd, void *buf, size_t n);
ssize_t rio_writen(int fd, void *buf, size_t n);

void rio_readinitb(rio_t *rp, int fd);
ssize_t rio_readlineb(rio_t *rp, void *buf, size_t n);
ssize_t rio_readnb(rio_t *rp, void *buf, size_t n);

#endif
