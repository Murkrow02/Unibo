//
// Created by Marco on 27/11/2021.
//

#include "Headers/SymbolTable.h"
#include "stdlib.h"
#include "Headers/Utils.h"
#include "string.h"
#include "stdio.h"

const int maxLabelSize = 50;

//Add symbol map to the list
symPtr pushSymbol(symPtr head, int address, char name[], int type){

    //Init list if head NULL
    if (head == NULL) {

        //Create new element
        head = (symPtr) malloc(sizeof(SymbolTable));
        strcpy(head->name, name);
        head->address = address;
        head->type = type;
        head->next = NULL;
    }
        //Push element in list
    else {

        symPtr current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        //Create new element
        current->next = (symPtr) malloc(sizeof(SymbolTable));
        strcpy(current->next->name, name);
        current->next->address = address;
        current->next->type = type;
        current->next->next = NULL;
    }

    return head;
}

//Check if requested symbol is already in list, -1 if not found, address if found
int checkInList(symPtr head, char name[]){

    //Check if list is empty
    if(head == NULL)
        return -1;

    //Search element in list
    symPtr currentElement = head;
    int found = 0;
    while (currentElement != NULL && found == 0){

        if(strcmp(currentElement->name, name) == 0)
            found = 1; //Matching element found
        else
        currentElement = currentElement->next;
    }

    if(found == 1)
        return currentElement->address;
    else
    return -1;
}

//Check if requested address is already used, if not return address, otherwise recursively find next available address
int nextAvailableAddress(symPtr head, int address)
{
    //Check if list is empty
    if(head == NULL)
        return -1;

    //Search element in list
    symPtr currentElement = head;
    int found = 0;
    while (currentElement != NULL && found == 0){

        if(currentElement->address == address && currentElement->type == 1)
            found = 1; //Matching element found
        else
            currentElement = currentElement->next;
    }

    //Recursive find new address
    if(found == 0)
        return address;
    else
        return nextAvailableAddress(head, address+1);
}

//Add default symbols to list, such as SCREEN, KBD etc.
symPtr fillDefaultSymbols(symPtr head){

    //Add the first 16 default registers (R0,R1...R15)
    for (int i = 0; i < 16; ++i) {
        char name[4];
        char index[3];
        intToString(index,i);
        strcpy(name,"R");
        strcat(name,index);
        head = pushSymbol(head, i, name, 1);
    }

    //Other symbols
    head = pushSymbol(head, 16384, "SCREEN",1);
    head = pushSymbol(head, 24576, "KBD",1);
    head = pushSymbol(head, 0, "SP",1);
    head = pushSymbol(head, 1, "LCL",1);
    head = pushSymbol(head, 2, "ARG",1);
    head = pushSymbol(head, 3, "THIS",1);
    head = pushSymbol(head, 4, "THAT",1);

    return head;
}

//Check if the label contains only valid characters
void checkValidLabel(char instr[]){

    int len = strlen(instr);
    int startUpper = 'A';
    int endUpper = 'Z';
    int startLower = 'a';
    int endLower = 'z';
    int startNumber = '0';
    int endNumber = '9';
    int dash = '_';
    int dot = '.';
    int dollar = '$';

    //Check if first letter is number
    if(instr[0] >= startNumber && instr[0] <= endNumber)
        printError("Il primo carattere di un etichetta non può essere un numero");

    //Check that other characters are valid
    for (int i = 0; i < len; ++i) {
        if((instr[i] >= startUpper && instr[i] <= endUpper) || (instr[i] >=startLower && instr[i] <= endLower) || (instr[i] >= startNumber && instr[i] <= endNumber) || instr[i] == dash || instr[i] == dot || instr[i] == dollar)
            continue;
        else
            printError("Etichetta non valida");
    }
}

//Check if current instruction is a label, 0 = no, 1 = yes, if yes then push a ROM address in symbols list
int labelFound(symPtr head, char instr[]){

    int len = strlen(instr);

    //Check if text is between parenthesis
    if(instr[0] == '(' && instr[len-1] == ')')
    {
        //Remove parenthesis
        removeFromString(instr,len-1);
        removeFromString(instr, 0);

        //Check that contains only valid characters
        checkValidLabel(instr);

        //Add new symbol in list and generate new address
        pushSymbol(head,labelLine, instr,0);

        return 1;
    }
    else{
        return 0;
    }
}

//Search for labels through the file and remove them
void searchLabels(symPtr head, FILE *inputFile, FILE *outputFile, int instructionLength)
{
    int end = 0;
    currentLine = 1;
    labelLine = 0;

    //Current instruction as string
    char currentInstruction[instructionLength];
    strcpy(currentInstruction, "\0");

    //Loop until end of the file
    while (end != 1)
    {
        //Read line from txt
        end = readLine(inputFile, currentInstruction, instructionLength);

        //Check if end of the file
        if(end == 1)continue;

        //Check if instruction is a label
        int labelFound_ = labelFound(head, currentInstruction);
        if(labelFound_ == 0){

            //No label, just copy the whole line
            fprintf(outputFile, "%s", currentInstruction);

            //Insert new line
            fprintf(outputFile, "%c", '\n');

            //Track line count to insert ROM addresses if instruction is valid
            if(currentInstruction[0] != '/' && strcmp(currentInstruction, "") != 0)
            labelLine++;

        }//If label is found do nothing, no line has to be printed

        //Increment current line for debug purposes
        currentLine++;
    }
}

//Generate new symbol address checking the first available
int createNewSymbol(symPtr head){

    int lastAvailable = 16383; //Last available address

    symPtr currentElement = head;
    symPtr prevElement = NULL;
    while (currentElement->next != NULL){

        //End cycle if current element reached screen memory address
        if(currentElement->address > lastAvailable)
            break;
        else{
            prevElement = currentElement;
            currentElement = currentElement->next;
        }
    }

    //Generate new address incrementing last used memory address
    int newAddress = nextAvailableAddress(head, prevElement->address+1);

    //Check if new address exceeds memory capacity
    if(newAddress > lastAvailable)
        printError("Spazi di memoria disponibili terminati");

    return newAddress;
}

//Detects if current instruction is a symbol and returns an address to that symbol, returns -1 if not a symbol
int findSymbol(symPtr head, char instr[]){

    //Check if instruction is a symbol (ignore also if A-Instruction is an address)
    if(instr[0] != '@' || (instr[0] == '@' && (instr[1] >= '0' && instr[1] <= '9')))
        return -1;

    //Remove @ from instruction
    removeFromString(instr, 0);

    //Check if symbol is already registered
    int symbolAddress = checkInList(head, instr);

    //Create new symbol if symbol not already registered
    if(symbolAddress == -1)
    {
        symbolAddress = createNewSymbol(head);
        pushSymbol(head,symbolAddress,instr,1);
    }

    return symbolAddress;
}

//Replace symbols (@abc) with addresses (@123)
symPtr replaceSymbols(symPtr head, FILE* inputFile, FILE* outputFile, int instructionLength){

    int end = 0;
    currentLine = 1;

    //Current instruction as string
    char currentInstruction[instructionLength];
    strcpy(currentInstruction, "\0");

    //Loop until end of the file
    while (end != 1)
    {
        //Read line from txt
        end = readLine(inputFile, currentInstruction, instructionLength);

        //Check if end of the file
        if(end == 1)continue;

        //Check if instruction is a symbol
        int symbolAddress = findSymbol(head, currentInstruction);
        if(symbolAddress != -1) //Symbol found
        {
            //Create symbol string @123
            char finalInstr[instructionLength];
            intToString(finalInstr,symbolAddress);
            fprintf(outputFile, "@%s", finalInstr);
        }
        else //Print full instruction if symbol is not found
        {
            fprintf(outputFile, "%s", currentInstruction);
        }

        //Increment current line for debug purposes
        currentLine++;

        //Insert new line in file
        fprintf(outputFile, "%c", '\n');
    }
}

//Take input file with symbols and return a new file with only addresses
FILE* convertSymbols(FILE *inputFile, int instructionLength){

    //Create first temp file (same program without labels)
    FILE *withoutLabels;
    withoutLabels = fopen("nolabels.tmpasm", "w");

    //Fill symbols list with default symbols
    symPtr head = NULL;
    head = fillDefaultSymbols(head);

    //Search labels and create new file without them
    searchLabels(head, inputFile, withoutLabels, instructionLength);
    //Close write mode to save new file
    fclose(withoutLabels);

    //Create last temp file (addresses instead of symbols)
    FILE *withoutSymbols;
    withoutSymbols = fopen("nosym.tmpasm","w");

    //Reopen saved file without labels in read mode
    withoutLabels = fopen("nolabels.tmpasm", "r");

    //Replace symbols with addresses
    head = replaceSymbols(head, withoutLabels, withoutSymbols, instructionLength);
    //Close write mode to save new file
    fclose(withoutSymbols);

    //Reopen temp file in read mode
    withoutSymbols = fopen("nosym.tmpasm","r");
    //Return final file
    return withoutSymbols;
}