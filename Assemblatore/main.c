//
// Created by Marco on 27/11/2021.
//

#include <stdio.h>
#include <string.h>
#include "Headers/Utils.h"
#include "Headers/TranslationTable.h"
#include "Headers/SymbolTable.h"

int main(int argc, char **argv) {

    //Check that file name is submitted
    if(argc < 2){
         printf("%s", "Inserisci il nome del file assembly come argomento");
         return 0;
     }

    //Open input file
    FILE *inputFile;
    inputFile = fopen(argv[1], "r");

    //Check that file exists
    if (inputFile == NULL) {
        printf("%s", "Il file specificato non è stato trovato");
        return 0;
    }

    //Convert symbols to address and create new file without symbols
    FILE* converted = convertSymbols(inputFile, maxInstructionLength);

    //Create file for final translation
    FILE *outputFile;
    translatedFileName = translateFileName(argv[1]);
    outputFile = fopen(translatedFileName, "w");

    //Start translation
    translate(converted, outputFile);

    //Close file streams
    fclose(inputFile);
    fclose(outputFile);
    fclose(converted);

    //Remove tmp files
    removeTempFiles(0);

    return 0;
}



