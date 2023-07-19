#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <libgen.h>
#define MAX 1024

int main(int argc, char *argv[])
{
    if(argc < 2)
        return -1;

    //Path of the symlink
    char* symPath = argv[1];

    //Path of content pointed by symlink
    char filePath[MAX];
    char relSymPath[MAX];

    //Open symlink
    realpath(symPath, filePath);
    int size = readlink(symPath, relSymPath, MAX);
    relSymPath[size] = '\0';
    char* fileName;
    fileName = basename(relSymPath);
    strcat(filePath, "/");
    strcat(filePath, fileName);

    //Get dir paths of sym and real file
    char* symRelDir;
    char* fileDir;
    char* symName;
    symRelDir = dirname(symPath);
    fileDir = dirname(filePath);
    symName = basename(symPath);


    char symDir[MAX];
    realpath(symRelDir, symDir);

    //Move file to sym path
    char newFilePath[MAX];
    strcpy(newFilePath, symDir);
    strcat(newFilePath, "/");
    strcat(newFilePath, fileName);
    printf("Moving %s to %s\n", filePath, newFilePath);
    rename(filePath, newFilePath);

    //Remove symlink
    unlink(symPath);

    //Create symlink where the file was
    char newSymPath[MAX];
    strcpy(newSymPath, dirname(fileDir));
    strcat(newSymPath, "/");
    strcat(newSymPath, symName);
    printf("Sym from %s to %s\n", newFilePath, newSymPath);
    if(symlink(newFilePath, newSymPath) == -1){
        perror("Cannot create symlink");
        return -1;
    }

    //printf("%s\n", "Success");

    return 0;
}