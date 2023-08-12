#ifndef PANDOS_SYSCALL_H
#define PANDOS_SYSCALL_H
#include <types.h>
#include <pandos_types_h>

extern void create_process(state_t *statep, support_t *supportp, struct nsd_t *ns);

#endif