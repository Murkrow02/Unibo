//
// Created by Marco on 27/11/2021.
//

#include "stdlib.h"
#include "string.h"
#include "Headers/Utils.h"
#include "Headers/TranslationTable.h"

const int maxInstructionLength = 150;

//Input: plain text instruction, output: binary translated instruction
void translateInstruction(const trnsPtr head, const char plain[], char translated[]) {

    //Initially set empty string
    strcpy(translated, "\0");

    trnsPtr current = head;
    int found = 0;

    //Search specified value in list
    while (current != NULL && found != 1) {
        if (strcmp(plain, current->plain) == 0) {
            strcpy(translated, current->bin); //Found
            found = 1;
        } else
            current = current->next; //Not found
    }
}

//Add translation map to the list
trnsPtr pushInstruction(trnsPtr head, const char plain[], const char bin[]) {

    //Init list if head NULL
    if (head == NULL) {
        //Create new element
        head = (trnsPtr) malloc(sizeof(TranslationTable));
        strcpy(head->plain, plain);
        strcpy(head->bin, bin);
        head->next = NULL;
    }
        //Push element in list
    else {
        trnsPtr current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        //Create new element
        current->next = (trnsPtr) malloc(sizeof(TranslationTable));
        current->next->next = NULL;
        strcpy(current->next->plain, plain);
        strcpy(current->next->bin, bin);
    }

    return head;
}

//Translate register's names to 0 1 bits
void translateDest(char instr[], int dest[])
{
    //Initially set bits to 0
    dest[0] = 0;dest[1] = 0;dest[2] = 0;

    //No dest, return all 0
    if(strlen(instr)==0)
        return;

    //Enable desired bits
    if(charInString(instr, 'M'))
        dest[2] = 1;
    if(charInString(instr, 'D'))
        dest[1] = 1;
    if(charInString(instr, 'A'))
        dest[0] = 1;
}

//Input: plain text comp instruction, output: binary translated comp instruction
void translateComp(char instr[], int comp[]) {

    //Fill list with possible comps
    trnsPtr head = NULL;
    head = pushInstruction(head, "0", "0101010");
    head = pushInstruction(head, "1", "0111111");
    head = pushInstruction(head, "-1", "0111010");
    head = pushInstruction(head, "D", "0001100");
    head = pushInstruction(head, "A", "0110000");
    head = pushInstruction(head, "!D", "0001101");
    head = pushInstruction(head, "!A", "0110001");
    head = pushInstruction(head, "-D", "0001111");
    head = pushInstruction(head, "-A", "0110011");
    head = pushInstruction(head, "D+1", "0011111");
    head = pushInstruction(head, "A+1", "0110111");
    head = pushInstruction(head, "D-1", "0001110");
    head = pushInstruction(head, "A-1", "0110010");
    head = pushInstruction(head, "D+A", "0000010");
    head = pushInstruction(head, "D-A", "0010011");
    head = pushInstruction(head, "A-D", "0000111");
    head = pushInstruction(head, "D&A", "0000000");
    head = pushInstruction(head, "D|A", "0010101");
    head = pushInstruction(head, "M", "1110000");
    head = pushInstruction(head, "!M", "1110001");
    head = pushInstruction(head, "-M", "1110011");
    head = pushInstruction(head, "M+1", "1110111");
    head = pushInstruction(head, "M-1", "1110010");
    head = pushInstruction(head, "D+M", "1000010");
    head = pushInstruction(head, "D-M", "1010011");
    head = pushInstruction(head, "M-D", "1000111");
    head = pushInstruction(head, "D&M", "1000000");
    head = pushInstruction(head, "D|M", "1010101");

    //Translate instruction
    char translatedComp[8];
    translateInstruction(head, instr, translatedComp);

    //Check if translation is found
    if (strcmp(translatedComp, "\0") == 0) {
        //No translation found
        printError("Istruzione non valida (comp not found in ISA)");
    } else {
        stringToArray(translatedComp, comp);
    }

}

//Input: plain text jump instruction, output: binary translated jump instruction
void translateJump(char instr[], int jump[]) {

    //Check if no jump
    if (strcmp(instr, "\0") == 0) {
        jump[0] = 0;
        jump[1] = 0;
        jump[2] = 0; //No jump
        return;
    }

    //Fill list with possible jumps
    trnsPtr head = NULL;
    head = pushInstruction(head, "JGT", "001");
    head = pushInstruction(head, "JEQ", "010");
    head = pushInstruction(head, "JGE", "011");
    head = pushInstruction(head, "JLT", "100");
    head = pushInstruction(head, "JNE", "101");
    head = pushInstruction(head, "JLE", "110");
    head = pushInstruction(head, "JMP", "111");

    //Translate instruction
    char translatedComp[8];
    translateInstruction(head, instr, translatedComp);

    //Check if translation is found
    if (strcmp(translatedComp, "\0") == 0) {
        //No translation found
        printError("Istruzione non valida (jump not found in ISA)");
    } else {
        stringToArray(translatedComp, jump);
    }
}

//Final function, ensembles dest, comp and jump together in one C-Instruction
void ensambleCInstruction(int dest[], int comp[], int jump[], char finalInstr[]) {

    //Initial C bits
    finalInstr[0] = '1';
    finalInstr[1] = '1';
    finalInstr[2] = '1';

    //Comp
    finalInstr[3] = comp[0] + '0';
    finalInstr[4] = comp[1] + '0';
    finalInstr[5] = comp[2] + '0';
    finalInstr[6] = comp[3] + '0';
    finalInstr[7] = comp[4] + '0';
    finalInstr[8] = comp[5] + '0';
    finalInstr[9] = comp[6] + '0';

    //Dest
    finalInstr[10] = dest[0] + '0';
    finalInstr[11] = dest[1] + '0';
    finalInstr[12] = dest[2] + '0';

    //Jump
    finalInstr[13] = jump[0] + '0';
    finalInstr[14] = jump[1] + '0';
    finalInstr[15] = jump[2] + '0';

    //Close string
    finalInstr[16] = '\0';
}

//Decodes instruction into separate sub-instructions
char* decodeCInstruction(char instr[], char destC[], char compC[], char jumpC[]){

    //Get string length
    int len = strlen(instr);

    //Decode destination
    int foundDest = 0;
    int destSize = 0;
    for (int i = 0; i < len; ++i) {

        //Found '=', dest is ready
        if(instr[i] == '=')
        {
            foundDest = 1;
            break;
        }
        else
            destSize++;
    }

    //More than 3 dest parameters, terminate program
    if(destSize>3 && foundDest == 1)
    {
        printError("Salvataggio su piu di 3 registri non consentito");
        exit(0);
    }
    else if(destSize != 0 && foundDest == 1)  //1,2 or 3 dest
    {
        //Create new string and insert dest
        for (int i = 0; i < destSize; ++i) {
            destC[i] = instr[i];
        }

        //Close string
        destC[destSize] = '\0';

        //Remove dest from original instruction
        removeUntilIndexString(instr, destSize+1);
    }else //No dest
    {
        destC[0] = '\0';
    }

    int expectJump = 0;

    //Decode comp
    int compSize = 0;
    int len2 = strlen(instr);
    for (int i = 0; i < len2; ++i) {

        //Found ';', comp is ready
        if(instr[i] == ';'){
            expectJump = 1; //Decode Jump later
            break;
        }
        else
            compSize++;
    }

    //More than 3 comp parameters, terminate program
    if(compSize>3)
    {
        printError("Istruzione non valida (comp>3)");
    }
    else if(compSize != 0)  //1,2 or 3 dest
    {
        //Create new string and insert dest
        for (int i = 0; i < compSize; ++i) {
            compC[i] = instr[i];
        }

        //Close string
        compC[compSize] = '\0';

        //Remove dest from original instruction
        removeUntilIndexString(instr, compSize+1);
    }else //Comp size == 0
    {
        printError("Istruzione non valida (comp is null)");
    }

    //Decode Jump only if ';' is found
    if(expectJump == 1){

        int jumpSize = 0;
        int len3 = strlen(instr);
        for (int i = 0; i < len3; ++i) {
            jumpSize++;
        }

        //Check if jump is valid (length = 3)
        if(jumpSize != 3){
            printError("Istruzione non valida (jump not recognized)");
        }else{
            strncpy(jumpC, instr,3);
            jumpC[3] = '\0';
        }
    }else{
        strcpy(jumpC, "\0");
    }
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
        //A-Instruction
    else if (instr[0] == '@') {


        //Decode number from instruction
        char aNumber[maxInstructionLength];
        strncpy(aNumber, instr + 1, maxInstructionLength);

        //Convert string to int number
        int value = stringToInt(aNumber);

        //Convert decimal value to binary
        int binaryValue[15];
        decToBinary(value, binaryValue);

        //Create A-Instruction from binary value
        char aInstr[17];

        //Set first bit to 0
        aInstr[0] = '0';

        //Start from second bit
        int stringIndex = 1;

        //Convert int array to char array
        for (int j = 0; j < 16; j++) {
            //Convert number to char
            char newChar = binaryValue[j] + '0';

            //Save char in return string
            aInstr[stringIndex] = newChar;
            stringIndex++;
        }

        //Close string with null char
        aInstr[16] = '\0';

        fprintf(outputFile, "%s", aInstr);
    }
        //C-Instruction
    else {

        //Init decoded instructions
        char destC[4], compC[4], jumpC[4];

        //Init translated instructions
        int dest[3], comp[7], jump[3];

        //Decode instructions
        decodeCInstruction(instr, destC, compC, jumpC);

        //Check if decoded destination is valid
        checkDest(destC);

        //Translate instructions
        translateDest(destC, dest);
        translateComp(compC, comp);
        translateJump(jumpC, jump);

        //Ensemble instructions
        char cInstr[17];
        ensambleCInstruction(dest, comp, jump, cInstr);

        //Write instruction to file
        fprintf(outputFile, "%s", cInstr);
    }

    //Insert new line
    fprintf(outputFile, "%c", '\n');
}

//Main function, take an inputFile(without symbols) to read from and write translated instructions to outputFile
void translate(FILE *inputFile, FILE *outputFile) {

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
        if(end == 1)continue;

        //Decode current instruction and save it to output file
        decodeInstruction(currentInstruction, outputFile);

        //Increment current line for debug purposes
        currentLine++;
    }
}