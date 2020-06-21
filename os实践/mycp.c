#include<sys/stat.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#define SIZE 2048
int main(int argc, char** argv)
{
    int fr = open(argv[1], O_RDONLY);
    int fw = open(argv[2], O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
    char buf[SIZE];
    int n;
    while((n = read(fr, buf, SIZE)) > 0){
        if( write(fw, buf, n) == -1){printf("write error");}
    }//while
    close(fr);
    close(fw);

}
