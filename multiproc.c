#include        <stdio.h>
#include        <stdlib.h>
#include        <sys/types.h>
#include        <sys/wait.h>

void counter()
{
int     i;
pid_t   pid;

        pid=getpid();

        for(i=0;i<10;i++){
		sleep(1);
                printf("[%d]%d\n",pid,i);
        }

	return;
}

void main()
{
pid_t   p_pid,pid;

	p_pid=getpid();

        printf("[%d]start\n",p_pid);

        switch(pid=fork()){
                case    0:      /* child */
                        counter();
                        exit(0);
                case    -1:
                        perror("fork");
                        break;
                default:        /* parent */
                        printf("[%d]child pid = %d\n",p_pid,pid);
                        break;
        }

        switch(pid=fork()){
                case    0:      /* child */
                        counter();
                        exit(0);
                case    -1:
                        perror("fork");
                        break;
                default:        /* parent */
                        printf("[%d]child pid = %d\n",p_pid,pid);
                        break;
        }

        pid=wait(0);
        printf("[%d]pid = %d end\n",p_pid,pid);
        pid=wait(0);
        printf("[%d]pid = %d end\n",p_pid,pid);

        printf("[%d]end\n",p_pid);
}
