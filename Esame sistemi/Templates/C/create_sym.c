#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 1024

int main(int argc, char *argv[])
{

    //Create symlink at path
    if(symlink("target", "sym") == -1){
        perror("Cannot create symlink");
        return -1;
    }

    return 0;
}