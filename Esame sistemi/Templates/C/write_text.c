#include <stdio.h>
#include <stdlib.h>

int main() {
    // Open the file in append mode
    FILE *file = fopen("example.txt", "a");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    // The buffer containing the data to be written
    char buffer[] = "Hello, World!";

    // Write the buffer to the file
    fprintf(file, "%s\n", buffer);

    // Close the file
    fclose(file);

    printf("Data written to the file successfully.\n");

    return 0;
}