# Team Number: 9

## Team Members
- AZIMBOYEV ISFANDIYOR
- ASRARXANOV ASADBEK
- AXMEDOV FERUZBEK
- BAXTIYOROV BOTIRXO'JA
- AZIZOV ABRORXON

## Team Leader
**Asadbek Asrarxanov**

## Components Distribution

1. **Protocol and Client** — Asadbek Asrarxanov
2. **Scheduler and Policy** — Isfandiyor Azimboyev
3. **Worker and Limits** — Botir Baxtiyorov
4. **Durability and Recovery** — Feruzbek Axmedov
5. **Operations and Report** — Abror Azizov

## Repository Structure

```text
team9/
├── README.md           # Team number, leader, and component ownership
├── Makefile            # Builds ./server, ./worker, ./client; includes make clean
├── .gitignore          # Excludes server, worker, client, and *.o
├── report.pdf          # Final report (maximum 4 pages)
│
├── src/
│   ├── common.h        # TEAM define, limits (MAX_LINE, MAX_OUT), shared types
│   ├── net.h           # Provided by professor
│   ├── shared_mem.h    # Provided by professor
│   ├── thread.h        # Provided by professor
│   ├── shed.h          # Queue and scheduler (2)
│   ├── shed.c          # Scheduler implementation (2)
│   ├── jobs.h          # Job table and job-related declarations (4)
│   ├── jobs.c          # Job table, job_set_state(), serialization (4)
│   ├── client.c        # Four verbs, ID prefix parsing/printing (1)
│   ├── server.c        # Accept loop, per-client handling, SIGTERM (1, 2, 4)
│   └── worker.c        # run_job(), timers, kill(-pid), reaper, SIGTERM (3)
│
│   OPTIONAL, most likely will be skipped
├── tests/
│   ├── check.sh        # Runs the 12 test cases from §5.4 unattended
│   ├── load8.sh        # Runs eight clients simultaneously
│   ├── zombies.sh      # Checks for zombie processes (state Z)
│   └── fds.sh          # Checks file descriptor counts before/after 100 jobs
│
└── docs/
    ├── protocol.md    # One-page protocol specification
    └── trace/         # Logs and traces for the report (policy trace, actual failure)
```
