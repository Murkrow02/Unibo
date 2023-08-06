
//Keep track of active procs
extern int process_count;

//Number of procs which are started but waiting for I/O or timer
extern int soft_block_count;

//Procs which are waiting to be handled by CPU
extern struct list_head ready_queue;

//Process currently using the CPU
extern pcb_t *running_proc;

//Initialize the scheduler
extern void initScheduler(void);

//Call the scheduler
extern void schedule(void);