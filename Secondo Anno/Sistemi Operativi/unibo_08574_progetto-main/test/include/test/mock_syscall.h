/**
 * \file mock_syscall.h
 * \brief A mock of the BIOS SYSCALL procedure.
 *
 * \author Luca Tagliavini
 * \date 9-04-2022
 */

#ifndef PANDOS_TEST_MOCK_SYSCALL_H
#define PANDOS_TEST_MOCK_SYSCALL_H

#include "os/syscall.h"

unsigned int SYSCALL(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
    active_process->p_s.reg_a0 = a0;
    active_process->p_s.reg_a1 = a1;
    active_process->p_s.reg_a2 = a2;
    active_process->p_s.reg_a3 = a3;
    syscall_handler();
    return active_process->p_s.reg_v0;
}

#endif /* PANDOS_TEST_MOCK_SYSCALL_H */
