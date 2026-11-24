#include "common.h"

// TODO(Feruzbek) -- full implementation of job table and state management
// implement requested interfaces and add whatever you need

typedef enum
{
    QUEUED,
    RUNNING,
    DONE,
    TIMEOUT,
    SIGNAL,
    CANCELLED
} JobState;

typedef struct
{
    int id;
    char command[MAX_LINE];
    int timeout;
    int priority;
    char output[MAX_OUTPUT];
    JobState state;
    int exit_code;
} Job;

// creates a new job, assigns a globally unique ID, and stores its details
// returns the assigned job ID, or -1 on failure
int jobs_create(const char *command, int timeout, int priority);

// returns a pointer to the job with the given ID, NULL if not found
Job *jobs_find(int job_id);

// updates the job state through one centralized function
void jobs_set_state(int job_id, JobState state);

// stores the result of a completed job (exit code, output, etc.)
void jobs_set_result(int job_id, JobState state, int code,
                     const char *output, int output_len);

// checks whether a job exists
int jobs_exists(int job_id);

// returns the current state of a job
JobState jobs_get_state(int job_id);

// returns job's priority, -1 on error/nonexisting job
int get_job_priority(int job_id);