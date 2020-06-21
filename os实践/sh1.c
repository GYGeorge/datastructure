#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void mycd(char *path)
{
    chdir(path);
}                               //mycd

void mysys(char *command_a)
{
    char command[64];
    strcpy(command, command_a);
    char *com;
    char *c[32];
    int i = 1;
    com = strtok(command, " ");
    c[0] = com;
    while (com) {
        com = strtok(NULL, " ");
        c[i] = com;
        i++;
    }                           //while
    pid_t pid = vfork();
    if (strcmp(c[0], "exit") == 0) {
        exit(0);
        return;
    }                           //if
    else if (strcmp(c[0], "cd") == 0) {
        mycd(c[1]);
        return;
    }
    if (pid == 0)
        execvp(c[0], c);
    wait(NULL);
}                               //mysys

int main()
{
    for (;;) {
        // mysys("pwd");
        printf("$ ");
        char c[64];
        fgets(c, sizeof(c), stdin);
        int i;
        for (i = 0; i < sizeof(c); i++) {
            if (c[i] == '\n')
                c[i] = c[i + 1];
        }
        mysys(c);
    }
}
