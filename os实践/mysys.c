#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void mysys(char *command_a)
{
    char command[64];
    strcpy(command, command_a);
    char* com;
    char* c[4];
    int i = 1;
	com = strtok(command," ");
    c[0] = com;
	while(com) {
		com = strtok(NULL, " ");
        c[i] = com;
        i++;
	}//while
    pid_t pid = vfork();
    if(pid == 0)
        execvp(c[0], c);
    wait();
}//mysys
int main()
{
    printf("--------------------------------------------------\n");
    mysys("echo HELLO WORLD");
    printf("--------------------------------------------------\n");
    mysys("ls /");
    printf("--------------------------------------------------\n");
    return 0;   
}//main