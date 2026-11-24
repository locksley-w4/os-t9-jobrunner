### Message formats:
## Client-Server
# 1. SUBMIT
Request: SUBMIT [timeout=%d in seconds] [optional priority=%d, 0 if not provided] -- cmd\n
timeout >= 1
priority 0-9
Response: [jobID=%d]\n

# 2. STATUS
Request: STATUS [jobID=%d]\n
Possible Responses: 
    QUEUED\n
    RUNNING\n
    DONE [exitCode=%d]\n
    KILLED [reason=%s]\n
    CANCELLED\n

# 3. CANCEL
Request: CANCEL [jobID=%d]\n
Possible Response:
    CANCELLED\n
    ALREADY FINISHED\n

# 4. FETCH
Request: FETCH [jobID=%d]\n
Response:
1) if the job has already finished
    READY [int response-length]\n(everything the job printed to STDOUT/STDERR). 
    **Max 64KiB**. Server checks and trims before sending. Prints to user without the length prefix.

2) if not finished yet
    NOTREADY\n
Client sees empty message and prints locally:
STDOUT: (nothing)
STDERR: {TEAM-PREFIX}-{JOB-ID} NOT FINISHED


# 5. Any other unknown command, non existent job id or incorrect team prefix.
Reject on the client immediately if command unknown or incorrect team prefix. Return UNKNOWN from server on non-existent jobID. Print proper messages to user on all cases.

## Client-Server durability
"A client dies half way through a submit. Where does your read loop
handle that?"
-- when client ends connection, both if successfully delivered or failed, server's read returns **0**. In *SUBMIT, STATUS, CANCEL* server compares for the end of message to be '\n'. 
In *FETCH*:
1. Client dies mid-fetch
Ignore SIGPIPE on the server, so it does not crash sending to dead client.
2. Server dies mid-fetch
Client compares size prefix against actual received message size. On mismatch, flags communication as failed and resends the fetch.

## Server-Worker

# 1 HELLO <K>
HELLO <K>   --  worker sends to server, server accepts this new worker
K - Worker runs at most K jobs at once.

# 2 CANCEL <JobID>  
CANCEL <JobID>   --  server tells worker to cancel a job
K - Worker runs at most K jobs at once.

# 3 JOB <id> <timeout> <priority> <command>\n
JOB <id> <timeout> <priority> <command>\n -- server->worker -- worker accepts and executes and reports
timeout >= 1
priority - 0-9, default 0

# 4 REPORT <id> <state> <code> <output length>\n(actual output)
REPORT <id> <status> <output length>\n(actual output) -- worker to server -- sends when a job finishes. Max output length 64KiB.

state = DONE | TIMEOUT | SIGNAL | CANCELLED     code = exit code / signal number / 0

e.g:
- REPORT <id> DONE <code>
- REPORT <id> TIMEOUT 0
- REPORT <id> SIGNAL <n>
- REPORT <id> CANCELLED 0

# 5 BYE
BYE -- worker -> server -- worker is gone, remove it from scheduling, close all its connections.


## Error messages

# Client-Server
Client: SOMETHING invalid
Server: ERR UNKNOWN_COMMAND

Client: STATUS
Server: ERR MISSING_ARGUMENT

Client: SUBMIT abc 15 sleep 10
Server: ERR INVALID_TIMEOUT

Client: STATUS T12-999
Server: ERR JOB_NOT_FOUND

Client: CANCEL T12-1
Server: ERR CANNOT_CANCEL

# Server-Worker
1) Malformed job message - ERR INVALID_JOB
2) Worker cannot accept job	- ERR BUSY
3) Invalid job parameters - ERR INVALID_ARGUMENT
