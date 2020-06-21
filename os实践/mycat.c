#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#define SIZE 64
int main(int argc, char** argv)
{
    int fd = open(argv[1],O_RDONLY);
    char buf[SIZE];
    int n;
    while((n = read(fd, buf, SIZE)) > 0){
        write(STDOUT_FILENO, buf, n);
    }

}