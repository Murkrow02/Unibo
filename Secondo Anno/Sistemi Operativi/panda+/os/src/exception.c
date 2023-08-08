#include "exception.h"

//Copy of the exception cause register
int exception_cause;

void exception_hanlder(){
    addokbuf("Exception handler called \n");
    return;
}

void testRefillHandler(){
    addokbuf("TLB refill handler called \n");
    return;
}
