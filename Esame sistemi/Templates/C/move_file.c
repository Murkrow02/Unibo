
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 1024

int main(int argc, char *argv[])
{
    char oldPath[MAX] = "";
    char newPath[MAX] = "";

    //Move file
    if(rename(oldPath, newPath) == -1){
        perror("Cannot move file");
        return -1;
    }

    return 0;
}