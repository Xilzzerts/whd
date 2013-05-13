#include "headerc.h"
#include "whd.h"

int main(void)
{
    pid_t pid;
    if((pid = fork()) == 0)
    {
        close(STDOUT_FILENO);
        close(STDIN_FILENO);
        close(STDERR_FILENO);
        fake_main();
    }
    else if(pid > 0)
        exit(0);
    else
        FATAL("MAIN.FORK");

    exit(0);
}
