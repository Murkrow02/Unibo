//
// Created by Marco on 27/11/2021.
//
#include "stdio.h"

extern int currentLine;
extern int labelLine;
extern char *translatedFileName;

void decToBinary(int n, int a[]);
char* translateFileName(char inputFileName[]);
void removeFromString(char s[], int index);
void removeUntilIndexString(char s[], int n);
void cleanInstruction(char instruction[]);
void printError(char msg[]);
int readLine(FILE *inputFile, char output[], int instructionLength);
char* decodeCInstruction(char instr[],char destC[], char compC[], char jumpC[]);
void checkDest(char dest[]);
int charInString(char a[], char x);
void ensambleCInstruction(int dest[], int comp[], int jump[], char finalInstr[]);
void stringToArray(const char str[], int arr[]) ;
void removeTempFiles(int error);
char *intToString(char *dest, int i);
int stringToInt(char *str);

