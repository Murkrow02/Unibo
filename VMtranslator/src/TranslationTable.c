//
// Created by murkrow on 1/15/22.
//

#include "Headers/TranslationTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Headers/Utils.h"

//Base asm instructions to put op1 in D and op2 in M
const char getOperands[] = "@SP\n"
                      "A=M-1\n"
                      "A=A-1\n"
                      "D=M\n"
                      "@SP\n"
                      "A=M\n"
                      "A=A-1";

//Base asm instructions to put op1 in D
const char getOperand[] = "@SP\n"
                           "A=M-1\n"
                           "D=M\n";

//Base asm instructions to put the value of register D on the stack (2 slots above)
const char resultOnStack[] = "@SP  \n"
                           "A=M  \n"
                           "A=A-1  \n"
                           "A=A-1  \n"
                           "M=D  \n"
                           "@SP  \n"
                           "M=M-1 ";

//Base asm instructions to replace value indexed by SP with D register value
const char resultOnValue[] = "@SP  \n"
                             "A=M  \n"
                             "A=A-1  \n"
                             "M=D  \n";

//Comparison
const char comparisonOperation[] = "D=0\n"
                                   "@END\n"
                                   "0;JMP\n"
                                   "(IF)\n"
                                  "D=-1\n"
                                  "(END)";

const int maxInstructionLength = 900;

//Receives instruction and string array and returns an index in that array if the instruction starts with any of the strings present
int indexInStringArray(const char instr[], char *arr[]){

    //Detect which operation is decoded
    int codeIndex = -1, found = 0;

    //Search through possible operations
    for (int i = 0; i < 17; ++i) {
        found = 0;

        //Check that each char is equal with that operation
        for (int j = 0; j < strlen(arr[i]); ++j) {
            if(instr[j] == arr[i][j])
                continue;
            else
            {
                found = -1;
                break;
            }
        }

        //Operation found, return operation index
        if(found != -1)
        {
            codeIndex = i;
            break;
        }
    }
}

//Receives clean operation as input and returns index code of that operation if matched, -1 if operation is not valid
//This function also removes operation name from string for later decoding
int instructionType(char instr[]){

    //Array of possible instructions
    char *codes[17] = {
            "add",  //0
            "sub",  //1
            "neg",  //2
            "eq",   //3
            "gt",   //4
            "lt",   //5
            "and",  //6
            "or",   //7
            "not",  //8
            "pop",  //9
            "push", //10
            "label",//11
            "goto", //12
            "if-goto", //13
            "function",//14
            "call", //15
            "return"    //16
    };

    int codeIndex = indexInStringArray(instr, codes);

    //Remove operation and space from instruction string
    removeUntilIndexString(instr, strlen(codes[codeIndex])+1);

    return codeIndex;
}

//Detect which segment the pop/push operation is referring to and the index of that in case of local and argument or the value if constant
void decodePushPop(char instr[], int *segment, char index[]){

    //Array of possible segments
    char *codes[4] = {
            "static",  //0
            "local",  //1
            "argument",  //2
            "constant"   //3
    };

    int codeIndex = indexInStringArray(instr, codes);

    //Remove segment and space from instruction string
    removeUntilIndexString(instr, strlen(codes[codeIndex])+1);

    //Return values
    *(segment) = codeIndex;
    strcpy(index, instr);
}

/*
 Push value from desired segment:
 0: static
 1: local
 2: argument
 3: constant
 */
void translatePush(char instr[], char output[])
{
    int segment; //Segment index (0,1,2,3)
    char index[15]; //Argument index or value if const

    //Detect which segment to use
    decodePushPop(instr, &segment, index);

    //Security checks
    if(segment == -1) //Check if segment is valid
        printError("Il segmento indicato non è valido");
    //Check if index is a number
    if(isNumber(index) == 0)
        printError("L'argomento non è valido");

    //Static
    if(segment == 0) //Prendi da indirizzo di memoria[index]
        sprintf(output, "@%s\nD=M\n", index);
    //Local and argument
    else if(segment == 1 || segment == 2)
        sprintf(output, "@%d\nD=M\n@%s\nA=A+D\nD=M\n", segment, index); //Prendi da indirizzo di local o argument + argomento
    //Constant
    else if(segment == 3) //Prendi direttamente il valore di index
        sprintf(output, "@%s\nD=A\n", index);

    //Create full instruction
    strcat(output, "@SP\nA=M\nM=D\n@SP\nM=M+1");
}

//Init file stream with informations such as setting SP to 256
void initFile(FILE *outputFile){

    char stackInit[] = "@256\n"
                       "D=A\n"
                       "@SP\n"
                       "M=D";

    //Write instruction to file
    fprintf(outputFile, "%s", stackInit);

    //Insert new line
    fprintf(outputFile, "%c", '\n');
}

//Detect which type of instruction is entered and write to the final file translated instruction
void decodeInstruction(char instr[], FILE *outputFile) {

    //Comment
    if (instr[0] == '/' && instr[1] == '/') {
        return;  //Nothing to write
    }

        //Empty line
    else if (strcmp(instr, "") == 0) {
        return;  //Nothing to write
    }

    //Decode instruction type
    int instrType = instructionType(instr);

    //Check if instruction type is valid
    if(instrType == -1)
        printError("Istruzione non valida");

    //Decode instruction
    char translated[maxInstructionLength];
    if(instrType==0) //Add
        sprintf(translated,"%s\nD=D+M\n%s",getOperands,resultOnStack);
    if(instrType==1) //Sub
        sprintf(translated,"%s\nD=D-M\n%s",getOperands,resultOnStack);
    if(instrType==2) //Neg
        sprintf(translated,"%s\nD=!D\nD=D+1\n%s",getOperand,resultOnValue);
    if(instrType==3) //Eq
        sprintf(translated,"%s\nD=D-M\n@IF\nD;JEQ\n%s\n%s",getOperands,comparisonOperation,resultOnStack);
    if(instrType==4) //Gt
        sprintf(translated,"%s\nD=D-M\n@IF\nD;JGT\n%s\n%s",getOperands,comparisonOperation,resultOnStack);
    if(instrType==5) //Lt
        sprintf(translated,"%s\nD=D-M\n@IF\nD;JLT\n%s\n%s",getOperands,comparisonOperation,resultOnStack);
    if(instrType==6) //And
        sprintf(translated,"%s\nD=D&M\n%s",getOperands,resultOnStack);
    if(instrType==7) //Or
        sprintf(translated,"%s\nD=D|M\n%s",getOperands,resultOnStack);
    if(instrType==8) //Not
        sprintf(translated,"%s\nD=!D\n%s",getOperand,resultOnValue);

    //POP

    if(instrType == 10)
        translatePush(instr, translated);

    //Write instruction to file
    fprintf(outputFile, "%s", translated);

    //Insert new line
    fprintf(outputFile, "%c", '\n');
}

//Main function, take an inputFile to read from and write translated instructions to outputFile
void translate(FILE *inputFile, FILE *outputFile) {

    //Init file setting stack pointer to 256
    initFile(outputFile);

    int end = 0;
    currentLine = 1;

    //Current instruction as string
    char currentInstruction[maxInstructionLength];
    strcpy(currentInstruction, "\0");

    //Loop until end of the file
    while (end != 1)
    {
        //Read line from txt
        end = readLine(inputFile, currentInstruction, maxInstructionLength);

        //Check if end of the file
        //if(end == 1)continue;

        //Decode current instruction and save it to output file
        decodeInstruction(currentInstruction, outputFile);

        //Increment current line for debug purposes
        currentLine++;
    }
}

