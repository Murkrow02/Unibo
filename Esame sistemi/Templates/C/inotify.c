#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>
#include <unistd.h>
#define MAX 1024

int main(int argc, char *argv[])
{

    //Return if not enough arguments
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return 1;
    }
    

    //Get dir path
    char inputDirPath[MAX];
    strcpy(inputDirPath, argv[1]);

    //Get ouput file path
    char outputFilePath[MAX];
    strcpy(outputFilePath, argv[2]);

    //Open output file
    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        return -1;
    }

    //Create inotify to watch whenever a file is puth inside inputDirPath
    int in_fd = inotify_init();
    int wd = inotify_add_watch(in_fd, inputDirPath,  IN_MOVED_TO );

    char event[MAX];
    read(in_fd,event,MAX);
    printf(event);

    return 0;
}