//
// Created by Marco on 27/11/2021.
//
#include "stdio.h"

typedef struct symbolTable{
    char name[50];
    int address;
    int type; //0 = ROMAddress, 1 = RAMAddress
    struct symbolTable *next;
}SymbolTable;

typedef SymbolTable* symPtr;

FILE* convertSymbols(FILE *inputFile, int instructionLength);