#include "common.h"

// TODO(Isfandiyor) -- full implementation of job queue and dispatcher that chooses workers
// implement requested interfaces and add whatever you need

// adds job to queue, get job details from jobs table
void shed_enqueue(int job_id);

// returns pair of next job to be run and on which worker, NULL if no such
WorkerJobPair shed_next();

// adds a new worker and set capacity
void shed_worker_add(int worker_id, int capacity);

// decrement available slots. 
void shed_worker_job_started(int worker_id);

// increment available slots.
void shed_worker_job_finished(int worker_id);

// removes the worker
void shed_worker_remove(int worker_id);