#include <libgen.h>
#define MAX 1024

int main(int argc, char *argv[])
{
    char path[MAX];
    char dirName*;
    char fileName*;
    dirName = dirname(path);
    fileName = basename(path);
    return 0;
}