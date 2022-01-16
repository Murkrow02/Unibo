#include <stdio.h>
#include <string.h>
#include "Headers/Utils.h"
#include "Headers/TranslationTable.h"

int main(int argc, char **argv) {


    //Check that file name is submitted
    /*if (argc < 2) {
        printf("%s", "Inserisci il nome del file vm come argomento");
        return 0;
    }*/

    //Open input file
    char fileName[] = "test.vm";
    FILE *inputFile;
    //inputFile = fopen(argv[1], "r");
    inputFile = fopen(fileName, "r");

    //Check that file exists
    if (inputFile == NULL) {
        printf("%s", "Il file specificato non è stato trovato");
        return 0;
    }

    //Create file for final translation
    FILE *outputFile;
    translatedFileName = translateFileName(fileName);
   // translatedFileName = translateFileName(argv[1]);
    outputFile = fopen(translatedFileName, "w");

    translate(inputFile,outputFile);


}