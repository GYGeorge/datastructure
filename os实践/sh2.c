#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
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
    /*重定向的文件 */
    int flag = 0;
    char filedir[64];
    for (i = 0; c[i] != NULL; i++) {
        if (c[i][0] == '>') {
            strcpy(filedir, c[i]);
            flag = 1;
            c[i] = NULL;
        }                       //if
    }                           //for
    for (i = 0; filedir[i] != 0; i++) {
        filedir[i] = filedir[i + 1];
    }                           //for
    pid_t pid = vfork();
    if (strcmp(c[0], "exit") == 0) {
        exit(0);
        return;
    }                           //if
    else if (strcmp(c[0], "cd") == 0) {
        mycd(c[1]);
        return;
    }
    if (pid == 0) {
        if (flag == 1) {
            int fd = open(filedir, O_CREAT | O_RDWR | O_TRUNC, 0666);
            dup2(fd, 1);
            close(fd);
        }
        execvp(c[0], c);
    }
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
