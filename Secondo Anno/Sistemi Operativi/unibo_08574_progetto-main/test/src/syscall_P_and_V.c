/**
 * \file syscall_yield.c
 * \brief Tests around the PASSEREN and VERHOGEN system call.
 *
 * \author Alessandro Frau
 * \date 12-04-2022
 */

#include "test/mock_init.h"
#include "test/mock_iodev.h"
#include "test/mock_syscall.h"
#include "test/test.h"

int main()
{
    mock_init();
    active_process = spawn_process(false);
    /*
    it("correctly P the current process on a semaphore")
    {
        assert(active_process->p_pid != -1);

        SYSCALL(PASSEREN, (size_t)&semaphores[0], 0, 0);
        assert(softblock_count == 1);
        assert(semaphores[0] == 0);
        assert(active_process->p_sem_add == &semaphores[0]);
        assert(process_count == 1);
    }
    it("correctly V the current process on its semaphore")
    {
        SYSCALL(VERHOGEN, (size_t)&semaphores[0], 0, 0);
        assert(softblock_count == 0);
        assert(semaphores[0] == 0);
        assert(active_process->p_sem_add == NULL);
        assert(process_count == 1);
    }
    it("correctly P and V on every semaphore")
    {
        for (size_t i = 0; i < MOCK_SEMAPHORES_LEN; ++i) {
            SYSCALL(PASSEREN, (size_t)&semaphores[i], 0, 0);
            assert(softblock_count == 1);
            assert(semaphores[i] == 0);
            assert(active_process->p_sem_add == &semaphores[i]);
            assert(process_count == 1);
            SYSCALL(VERHOGEN, (size_t)&semaphores[i], 0, 0);
            assert(softblock_count == 0);
            assert(semaphores[i] == 0);
            assert(active_process->p_sem_add == NULL);
            assert(process_count == 1);
        }
    }
    ensure("P does not break with a missing semaddr")
    {
        // Missing semaddr
        SYSCALL(PASSEREN, 0, 0, 0);
        assert(process_count == 0);
    }
    ensure("V does not break with a missing semaddr")
    {
        active_process = spawn_process(false);
        // Missing semaddr
        SYSCALL(VERHOGEN, 0, 0, 0);
        assert(process_count == 0);
    }
    */
    return 0;
}
