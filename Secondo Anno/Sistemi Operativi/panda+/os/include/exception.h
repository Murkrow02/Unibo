#ifndef PANDOS_EXCEPTION_H_INCLUDED
#define PANDOS_EXCEPTION_H_INCLUDED

#include <pandos_types.h>
#include "utils.h"
#include <umps3/umps/arch.h>
#include <umps3/umps/cp0.h>

//Copy of the exception cause register
#define DECODED_EXCEPTION_CAUSE CAUSE_GET_EXCCODE(CPU_STATE->cause)


void exception_hanlder();
void testRefillHandler();


#endif 