#ifndef PANDOS_SYSCALL_H
#define PANDOS_SYSCALL_H

#include <types.h>
#include <pandos_types.h>

void syscall_handler();
extern void terminate_process(int pid);
#endif