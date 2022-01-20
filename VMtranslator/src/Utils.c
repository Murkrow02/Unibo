#include "Headers/Utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int currentLine = 1;
int labelLine = 0;
char *translatedFileName;



//Convert decimal n into 15 bit binary array
void decToBinary(int n, int a[])
{
    //Set all values of dest array to 0
    for (int i = 0; i < 15; ++i) {
        a[i] = 0;
    }

    //Convert number to decimal and add ciphres into the array
    int i = 0;
    while (n > 0) {
        a[i] = n % 2;
        n = n / 2;
        i++;
    }

    //Revert array
    int j = 14;
    for(int i = 0; i<j; i++){
        a[i]^=a[j];
        a[j]^=a[i];
        a[i]^=a[j];
        j--;
    }
}

//Convert x.vm to x.hack
char* translateFileName(char inputFileName[])
{
    //Get initial file name
    int inputLength = strlen(inputFileName);

    //Create new string of size inputLength+1
    char *translatedFileName;
    translatedFileName = (char *) malloc(sizeof (char) * inputLength + 1);

    //Copy input string to output string
    strcpy(translatedFileName, inputFileName);

    //Change extension (molto brutto)
    char* lastCharAddress = (translatedFileName + (inputLength * sizeof(char) + 1));
    *(lastCharAddress) = '\0';
    *(lastCharAddress-sizeof(char )) = 'm';
    *(lastCharAddress-(sizeof(char) * 2)) = 's';
    *(lastCharAddress-(sizeof(char) * 3)) = 'a';

    //Save filename for later use
    strcpy(fileName, inputFileName);
    fileName[strlen(inputFileName)-3] = '\0'; //Remove extension

    return translatedFileName;
}

//Remove char at index position
void removeFromString(char s[], int index){
    int size = strlen(s) + 1;
    for(int i = index; i < size - 1; i++)
        s[i] = s[i + 1];
}

//Removes char until n index is reached
void removeUntilIndexString(char s[], int n){

    for (int i = 0; i < n; ++i) {
        removeFromString(s,0);
    }
}

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

//Remove special characters such as '\t'
void cleanInstruction(char s[]){
    char* d = s;
    do {
        while (*d == '\t' || *d == '\n' || *d == '\r') {
            ++d;
        }
    } while (*s++ = *d++);

}

//Terminate program and send message to user
void printError(char msg[]){
    printf("%s%d%c%s","Errore sulla linea: ",currentLine,'\n',msg);
    removeTempFiles(1);
    exit(0);
}

void removeInlineComment(char s[]){
    //Detect in-line comments
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if(s[i] == '/' && s[i+1] == '/'){
            s[i] = '\0'; //End line to comment
            break;
        }
    }
}

//Read line from file and clean from useless characters ("\n","\t" etc.)
int readLine(FILE *inputFile, char output[], int instructionLength) {

    //Read current instruction
    fgets(output, instructionLength, inputFile);

    //Clean instruction from tabs,spaces and newline
    removeInlineComment(output);
    trim(output);
    cleanInstruction(output);

    //Check if reached the end
    if (feof(inputFile)) {

        //Check if first line
        if(currentLine == 1)
            printError("Il file selezionato è vuoto");

        return 1;
    }
    return 0;
}

//Check if dest registers are valid (only A, M and D)
void checkDest(char dest[]){
    int len = strlen(dest);
    for (int i = 0; i < len; ++i) {
        if(dest[i] != 'A' && dest[i] != 'D' && dest[i] != 'M')
            printError("Registro non valido");
    }
}

//Check if x value is present in a string
int charInString(char a[], char x){
    int len = strlen(a);

    for (int i = 0; i < len; ++i) {
        if(a[i] == x)
            return 1;
    }
    return 0;
}

//Convert string to int array
void stringToArray(const char str[], int arr[]) {

    int len = strlen(str);

    for (int i = 0; i < len; ++i) {
        arr[i] = str[i] - '0';
    }
}

//Remove eventually generated tmp files
void removeTempFiles(int error){

    remove("nosym.tmpasm");
    remove("nolabels.tmpasm");
    if(error == 1){
        remove(translatedFileName); //Remove .hack file if translation failed
    }
}

//Convert int number to string
static char *intToStringHelper(char *dest, int i) {
    if (i <= -10) {
        dest = intToStringHelper(dest, i / 10);
    }
    *dest++ = '0' - i%10;
    return dest;
}
char *intToString(char *dest, int i) {
    char *s = dest;
    if (i < 0) {
        *s++ = '-';
    } else {
        i = -i;
    }
    *intToStringHelper(s, i) = '\0';
    return dest;
}

//Convert string to int number
int stringToInt(char *str)
{
    int r;
    int p;

    r = 0;
    p = 1;
    while (('-' == (*str)) || ((*str) == '+'))
    {
        if (*str == '-')
            p = p * -1;
        str++;
    }
    while ((*str >= '0') && (*str <= '9'))
    {
        r = (r * 10) + ((*str) - '0');
        str++;
    }
    return (r * p);
}

//Check that given string is a number
int isNumber(char s[])
{
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
            return 0;
    }
    return 1;
}

//Remove whitespaces from start and end of string
void trim(char *s)
{
    int  i,j;

    for(i=0;s[i]==' '||s[i]=='\t';i++);

    for(j=0;s[i];i++)
    {
        s[j++]=s[i];
    }
    s[j]='\0';
    for(i=0;s[i]!='\0';i++)
    {
        if(s[i]!=' '&& s[i]!='\t')
            j=i;
    }
    s[j+1]='\0';
}
