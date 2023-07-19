#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>
#include <unistd.h>
#include <dirent.h>
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

    //Watch in dir until 
    while(1){
        char event[MAX];
        read(in_fd,event,MAX);

        //File was added, read content of directory (assuming only one file is added at once)
        DIR *d = opendir(inputDirPath);
        if(!d)
            perror("Cannot open dir");


        //Dir opened   
        struct dirent *dir;
       if ((dir = readdir(d)) != NULL)
        {
            //Skip . 
            dir = readdir(d);


            char addedFilePath[MAX];
            strcpy(addedFilePath, inputDirPath);

            //Append file name to dir path
            strcat(addedFilePath, "/");
            strcat(addedFilePath, dir->d_name);
            closedir(d);
            
            //Read added file contents
            int ffd = open(addedFilePath, O_RDONLY);
            char fileContents[MAX];
            int readd = read(ffd, fileContents, MAX);
            fileContents[readd] = '\0';

            // Open the file in append mode
            FILE *file = fopen(outputFilePath, "a");
            if (file == NULL)
            {
                perror("Error opening the file");
                return 1;
            }

            // Write header
            char header[MAX] = "Moved ";
            strcat(header, addedFilePath);
            fprintf(file, "%s\n", header);

            // Write the buffer to the file
            fprintf(file, "%s\n", fileContents);

            // Close the file
            fclose(file);
        }else{
            perror("Cannot read dir");
        }
    }

   

    return 0;
}