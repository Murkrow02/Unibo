#ifndef PANDOS_SYSCALL_H
#define PANDOS_SYSCALL_H

#include <types.h>
#include <pandos_types.h>

void syscall_handler();
void create_process(state_t *statep, support_t *supportp, struct nsd_t *ns);

#endif