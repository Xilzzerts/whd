#ifndef WHD_H
#define WHD_H

#include "rio/rio.h"
#define WORKER 2

void fake_main(void);
void start_worker(int);
void process(int, int, char *, char *, char *, char *, char *,char *, char *);
void ERR(int, int);
void call_403(int);
void parse_uri(char *, char *, char *);
void get_filetype(char *, char *);
void process_rstheader(rio_t *);
int  get_fileinfo(char *);
int setnonblocking(int);
#endif
