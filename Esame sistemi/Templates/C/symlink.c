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
    //Path of the symlink
    char symPath[MAX];

    //Path of content pointed by symlink
    char resolvedPath[MAX];

    //Open symlink
    realpath(symPath, resolvedPath);
    
}