#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#define   MAX_COUNT  200

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
    pid_t  pid;
    int * x = (int *)malloc(10);

    pid = fork();
    if (pid == 0) {
            *x = 100;
            ChildProcess();
    }
    else {
            *x = 200;
            ParentProcess();
    }
    printf("the address is %p and value is %d\n", x, *x);
}

void  ChildProcess(void)
{
    printf("   *** Child process  ***\n");
}

void  ParentProcess(void)
{
    printf("*** Parent*****\n");
}
