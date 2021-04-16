#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int MAXCHILDREN = 4;

void sig_handler_killChildren(int signum)
{
   printf("This is where I will kill my children"); 
}

void sig_handler_child(int signum)
{
   printf("You've killed me"); 
}

void sig_handler(int signum)
{
    printf("You quit");
}

void show_Everything(int ArrayToShow[])
{
    for (int j = 0; j <= MAXCHILDREN; j++)
    {
        printf("%d\n", ArrayToShow[j]);
        return 0;
    }
}

int main()
{
    signal (SIGINT, sig_handler);
    signal (SIGINT, sig_handler_killChildren);
    pid_t pid;
    if (pid == 0)
    {
        signal (SIGUSR1,sig_handler_child);

    } else {
        
        int childrenAR[MAXCHILDREN];
        int currChildren = 0;
        for (int i = 0; i<= MAXCHILDREN; i++)
        {
        
            pid = fork();
            if(pid < 0)
            {
                printf("Fork Failed\n");
                exit(1);
            } else if (pid >= 1)
            {
                childrenAR[i] = pid;
                currChildren++;
            }
            raise(SIGINT);
        }
        show_Everything(childrenAR);
    }
}

