#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#define FILENAME_LEN 32
#define MAX_ARGC 16
#define MAX_COMMAND 10
typedef struct command {
    int argc;
    char *argv[MAX_ARGC];
    char input[FILENAME_LEN];   //重定向输入
    char output[FILENAME_LEN];  //重定向输出
} shellcommand;
int commandcount;
shellcommand commandExternal[MAX_COMMAND];
int split(char str[], char delim[], char *target[MAX_ARGC])
{
    char copy[64];
    strcpy(copy, str);
    char *temp;
    temp = strtok(str, delim);
    target[0] = temp;
    int i = 1;
    while (temp) {
        temp = strtok(NULL, delim);
        target[i] = temp;
        i++;
    }                           //while
    return 1;
}

void command_dump(shellcommand c)
{
    printf("argc = %d\n", c.argc);
    int i;
    for (i = 0; c.argv[i] != NULL; i++) {
        printf("argv[%d] = %s\n", i, c.argv[i]);
    }                           //for
    if (strcmp(c.output, "\0"))
        printf("outputfile:%s\n", c.output);
    if (strcmp(c.input, "\0"))
        printf("inputfile:%s\n", c.input);
}

void init(shellcommand * c)
{
    c->argc = 0;
    int i;
    for (i = 0; c->argv[i]; i++) {
        memset(c->argv[i], 0, sizeof(c->argv[i]));
    }
    memset(c->input, 0, sizeof(c->input));
    memset(c->output, 0, sizeof(c->output));
}

void calculate(shellcommand * c)
{
    int i = 0;
    c->argc = 0;
    while (c->argv[i]) {
        c->argc++;
        i++;
    }                           //while
    char outdir[FILENAME_LEN];
    char indir[FILENAME_LEN];
    int po_out, po_in;
    int flag_out = 0, flag_in = 0;
    for (i = 0; i < c->argc; i++) {
        if (c->argv[i][0] == '>') {
            strcpy(outdir, c->argv[i]);
            flag_out = 1;
            po_out = i;
        } else if (c->argv[i][0] == '<') {
            strcpy(indir, c->argv[i]);
            flag_in = 1;
            po_in = i;
        }
    }
    if (flag_out == 1) {
        for (i = po_out; i < c->argc; i++)
            c->argv[i] = c->argv[i + 1];
        for (i = 0; outdir[i] != 0; i++)
            outdir[i] = outdir[i + 1];
        strcpy(c->output, outdir);
        c->argc--;
    }
    if (flag_in == 1) {
        for (i = po_in; i < c->argc; i++)
            c->argv[i] = c->argv[i + 1];
        for (i = 0; indir[i] != 0; i++)
            indir[i] = indir[i + 1];
        strcpy(c->input, indir);
        c->argc--;
    }


}

void parsepipecommand(char line[])
{
    char *pipecom[MAX_ARGC];
    split(line, "|", pipecom);
    commandcount = 0;
    int i = 0;
    while (pipecom[i]) {
        split(pipecom[i], " ", commandExternal[i].argv);
        calculate(&commandExternal[i]);
        commandcount++;
        i++;
    }                           //while
}                               //parsepipecommand

void exec_simple(shellcommand c)
{

    if (strcmp(c.output, "\0")) {
        int fd_out = open(c.output, O_CREAT | O_RDWR | O_TRUNC, 0666);
        dup2(fd_out, 1);
        close(fd_out);
    }
    if (strcmp(c.input, "\0")) {
        int fd_in = open(c.input, O_RDONLY);
        if (fd_in < 0) {
            printf("open error\n");
            exit(0);
        }
        dup2(fd_in, 0);
        close(fd_in);
    }
    execvp(c.argv[0], c.argv);
}

void exec_pipe(int childcount)
{
    if (childcount == 0)
        return;
    int fd_array[2];
    int pid;
    pipe(fd_array);
    pid = fork();
    if (pid == 0) {
        dup2(fd_array[0], 0);
        close(fd_array[0]);
        close(fd_array[1]);
        exec_simple(commandExternal[childcount - 1]);
    }
    dup2(fd_array[1], 1);
    close(fd_array[0]);
    close(fd_array[1]);
    exec_pipe(childcount - 1);
}                               //exec_pipe

void mysys(char line[])
{
    parsepipecommand(line);
    if (strcmp(commandExternal[0].argv[0], "exit") == 0) {
        exit(0);
        return;
    }                           //if
    else if (strcmp(commandExternal[0].argv[0], "cd") == 0) {
        chdir(commandExternal[0].argv[1]);
        return;
    }
    int pid = fork();
    if (pid == 0) {
        exec_pipe(commandcount);
    }
    wait(NULL);
}

int main()
{
    for (;;) {
        int i;
        for (i = 0; i < MAX_COMMAND; i++)
            init(&commandExternal[i]);
        printf("$ ");
        char c[64];
        fgets(c, sizeof(c), stdin);
        for (i = 0; i < sizeof(c); i++) {
            if (c[i] == '\n')
                c[i] = c[i + 1];
        }
        mysys(c);
    }
}
