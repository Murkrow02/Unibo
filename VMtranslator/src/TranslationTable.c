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

//Push the value of D register on top of the stack
const char pushD[] = "@SP\nA=M\nM=D\n@SP\nM=M+1";

const int maxInstructionLength = 900;

char fileName[200];

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
    trim(index);
    if(isNumber( index) == 0)
        printError("L'argomento non è valido");

    //Static
    if(segment == 0)
        sprintf(output, "@%s.%s\nD=M\n", fileName , index);
    //Local and argument
    else if(segment == 1 || segment == 2)
        sprintf(output, "@%d\nD=M\n@%s\nA=A+D\nD=M\n", segment, index); //Prendi da indirizzo di local o argument + argomento
    //Constant
    else if(segment == 3) //Prendi direttamente il valore di index
        sprintf(output, "@%s\nD=A\n", index);

    //Create full instruction
    strcat(output, pushD);
}

/*
 Pop value into desired segment:
 0: static
 1: local
 2: argument
 3: constant
 */
void translatePop(char instr[], char output[])
{
    int segment; //Segment index (0,1,2,3)
    char index[15]; //Argument index or value if const

    //Detect which segment to use
    decodePushPop(instr, &segment, index);

    //Security checks
    if(segment == -1 || segment == 3) //Check if segment is valid
        printError("Il segmento indicato non è valido");
    //Check if index is a number
    if(isNumber(index) == 0)
        printError("L'argomento non è valido");

    //Put value from stack into D register
    char getFromStack[] = "@SP\nA=M-1\nD=M";

    //Static
    if(segment == 0)
        sprintf(output, "%s\n@%s.%s\nM=D\n", getFromStack, fileName, index);
    //Local and argument
    else if(segment == 1 || segment == 2)
    {
        sprintf(output,"%s\n@%d\nA=M\n",getFromStack,segment);

        //Increase pointer offset based on index
        for (int i = 0; i < stringToInt(index); ++i) {
            strcat(output, "A=A+1\n");
        }

        //Put D value into register
        strcat(output, "M=D\n");
    }

    //Create full instruction
    strcat(output, "A=A+1\n@SP\nM=M-1");
}

//Receives instruction as input and outputs the name of the function and how many arguments declared
void extractNameArgs(char instr[], int *argCount, char funcName[]){

    for (int i = 0; i < strlen(instr); ++i) {
        if(instr[i] == ' ')
        {
            //Trunc string and create func name
            strcpy(funcName, instr);
            funcName[i] = '\0';

            //Trunc string and create argCount
            removeUntilIndexString(instr,i+1);
            *argCount = stringToInt(instr);
            break;
        }
    }
}

void translateCall(char instr[], char output[]){

    //Extract name and arguments count
    int argCount = -1;
    char funcName[300];
    extractNameArgs(instr, &argCount, funcName);

    //Check if argCount is found
    if(argCount == -1)
        printError("Il numero di argomenti per la funzione non è valido");


    sprintf(output,"//PUSH RETURN ADDRESS (using line n)\n"
                   "@$%d\n"
                   "D=A\n"
                   "%s\n"
                   "//PUSH LCL\n"
                   "@LCL\n"
                   "D=M\n"
                   "%s\n"
                   "//PUSH ARG\n"
                   "@ARG\n"
                   "D=M\n"
                   "%s\n"
                   "//PUSH THIS\n"
                   "@THIS\n"
                   "D=M\n"
                   "%s\n"
                   "//PUSH THAT\n"
                   "@THAT\n"
                   "D=M\n"
                   "%s\n"
                   "//ARG=S-n-5\n"
                   "@SP\n"
                   "D=M\n"
                   "@5\n"
                   "D=D-A\n"
                   "@%d\n"
                   "D=D-A\n"
                   "@ARG\n"
                   "M=D\n"
                   "//LCL=SP\n"
                   "@SP\n"
                   "D=M\n"
                   "@LCL\n"
                   "M=D\n"
                   "//GOTO F\n"
                   "@%s\n"
                   "0;JMP\n"
                   "//(RETURN ADDRESS)\n"
                   "($%d)", currentLine, pushD, pushD, pushD, pushD, pushD, argCount,funcName,currentLine);

}



void translateFunction(char instr[], char output[]){

    //Extract name and arguments count
    int argCount = -1;
    char funcName[300];
    extractNameArgs(instr, &argCount, funcName);

    //Check if argCount is found
    if(argCount == -1)
        printError("Il numero di argomenti per la funzione non è valido");

    //Insert function tag
    sprintf(output, "(%s)\n",funcName);


    //Alloc space for local
    for (int i = 0; i < argCount; ++i) {
        strcat(output,"@SP\n"
                       "A=M\n"
                       "M=0\n"
                       "@SP\n"
                       "M=M+1\n");
        }
}

void translateReturn(char output[]){
    sprintf(output,"//FRAME = LCL\n"
                   "@LCL\n"
                   "D=M\n"
                   "@FRAME\n"
                   "M=D\n"
                   "//RET = *(FRAME-5)\n"
                   "@5\n"
                   "D=A\n"
                   "@FRAME\n"
                   "A=M-D\n"
                   "D=M\n"
                   "@RET\n"
                   "M=D\n"
                   "\n"
                   "//*ARG=pop()\n"
                   "@ARG\n"
                   "D=M\n"
                   "@R13\n"
                   "M=D\n"
                   "@SP\n"
                   "AM=M-1\n"
                   "D=M\n"
                   "@R13\n"
                   "A=M\n"
                   "M=D\n"
                   "//SP = ARG+1\n"
                   "@ARG\n"
                   "D=M+1\n"
                   "@SP\n"
                   "M=D\n"
                   "//THAT = *(FRAME-1)\n"
                   "@FRAME\n"
                   "D=M\n"
                   "@1\n"
                   "A=D-A\n"
                   "D=M\n"
                   "@THAT\n"
                   "M=D\n"
                   "//THIS = *(FRAME-2)\n"
                   "@FRAME\n"
                   "D=M\n"
                   "@2\n"
                   "A=D-A\n"
                   "D=M\n"
                   "@THIS\n"
                   "M=D\n"
                   "//ARG = *(FRAME-3)\n"
                   "@FRAME\n"
                   "D=M\n"
                   "@3\n"
                   "A=D-A\n"
                   "D=M\n"
                   "@ARG\n"
                   "M=D\n"
                   "//LCL = *(FRAME-4)\n"
                   "@FRAME\n"
                   "D=M\n"
                   "@4\n"
                   "A=D-A\n"
                   "D=M\n"
                   "@LCL\n"
                   "M=D\n"
                   "//goto RET\n"
                   "@RET\n"
                   "A=M\n"
                   "0;JMP");
}

//Init file stream with informations such as setting SP to 256
void initFile(FILE *outputFile){

    char stackInit[] = "@256\n"
                       "D=A\n"
                       "@SP\n"
                       "M=D";

    //Write instruction to file
    fprintf(outputFile, "%s\n", stackInit);
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
        sprintf(translated,"%s\nD=D-M\n@IF%d\nD;JEQ\nD=0\n@END%d\n0;JMP\n(IF%d)\nD=-1\n(END%d)\n%s",getOperands,currentLine,currentLine,currentLine,currentLine,resultOnStack);
    if(instrType==4) //Gt
        sprintf(translated,"%s\nD=D-M\n@IF%d\nD;JGT\nD=0\n@END%d\n0;JMP\n(IF%d)\nD=-1\n(END%d)\n%s",getOperands,currentLine,currentLine,currentLine,currentLine,resultOnStack);
    if(instrType==5) //Lt
        sprintf(translated,"%s\nD=D-M\n@IF%d\nD;JLT\nD=0\n@END%d\n0;JMP\n(IF%d)\nD=-1\n(END%d)\n%s",getOperands,currentLine,currentLine,currentLine,currentLine,resultOnStack);
    if(instrType==6) //And
        sprintf(translated,"%s\nD=D&M\n%s",getOperands,resultOnStack);
    if(instrType==7) //Or
        sprintf(translated,"%s\nD=D|M\n%s",getOperands,resultOnStack);
    if(instrType==8) //Not
        sprintf(translated,"%s\nD=!D\n%s",getOperand,resultOnValue);
    if(instrType == 9) //Pop
        translatePop(instr, translated);
    if(instrType == 10) //Push
        translatePush(instr, translated);
    if(instrType == 11) //Label
        sprintf(translated,"(%s)", instr);
    if(instrType == 12) //Goto
        sprintf(translated, "@%s\n0;JMP", instr);
    if(instrType == 13) //If-Goto
        sprintf(translated,"@SP\nAM=M-1\nD=M\n@%s\nD;JNE",instr);
    if(instrType == 14) //Function
        translateFunction(instr, translated);
    if(instrType == 15) //Call
        translateCall(instr, translated);
    if(instrType == 16) //Return
        translateReturn(translated);


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

        //Comment current instruction
        if(strlen(currentInstruction )>1)
        fprintf(outputFile, "//%s\n", currentInstruction);

        //Decode current instruction and save it to output file
        decodeInstruction(currentInstruction, outputFile);

        //Increment current line for debug purposes
        currentLine++;
    }
}

