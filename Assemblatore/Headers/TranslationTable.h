//
// Created by Marco on 27/11/2021.
//
#include "stdio.h"

extern const int maxInstructionLength;

typedef struct translationTable {
    struct translationTable *next;
    char plain[4];
    char bin[8];
} TranslationTable;

typedef TranslationTable* trnsPtr;

void translate(FILE *inputFile, FILE *outputFile);