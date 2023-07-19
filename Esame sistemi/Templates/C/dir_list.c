#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#define MAX 1024

int main(int argc, char *argv[])
{

    //Open dir entry
    DIR *d = opendir("PATH_HERE");
    if (!d)
        perror("Cannot open dir");

    // Dir opened
    struct dirent *dir;
    if ((dir = readdir(d)) == NULL){
        perror("Cannot read dir");
        return -1;
    }

    // Skip "." entry
    dir = readdir(d);

    //Get file name
    char fname[] = dir->d_name;
    
}