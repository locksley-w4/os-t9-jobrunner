### Team Number: 9

# Team Members:
AZIMBOYEV ISFANDIYOR
ASRARXANOV ASADBEK
AXMEDOV FERUZBEK
BAXTIYOROV BOTIRXO'JA
AZIZOV ABRORXON

# Team Leader: Asadbek Asrarxanov

## Components distribution

1) Protocol and Client -- Asadbek Asrarxanov
2) Scheduler and Policy — Isfandiyor Azimboyev
3) Worker and Limits — Botir Baxtiyorov
4) Durability and recovery — Feruzbek Axmedov
5) Operations and report — Abror Azizov


## Repo structure

team12/
├── README.md            # team number, leader, owner of each component
├── Makefile             # builds ./server ./worker ./client; make clean    (5)
├── .gitignore           # server worker client *.o
├── report.pdf           # added at the end, 4 pages max                    (5)
├── src/
│   ├── common.h         # TEAM define, limits (MAX_LINE, MAX_OUT), shared types
│   ├── net.h            # provided by Professor
│   ├── shared_mem.h     # provided by Professor
│   ├── thread.h         # provided by Professor
│   ├── shed.h           # queue and scheduler                      (2)
│   ├── shed.c           # implementation of shed.h                 (2)
│   ├── jobs.h / jobs.c  # job table, job_set_state() (single state-change function),       serialize (4)
│   ├── client.c         # 4 verbs, id prefix parsing/printing      (1)
│   ├── server.c         # accept loop, per-client handling, SIGTERM    (1,2,4)
│   └── worker.c         # run_job(), timers, kill(-pid), reaper, SIGTERM   (3)
|
├── tests/
│   ├── check.sh         # runs the 12 rows of §5.4 unattended
│   ├── load8.sh         # eight clients at once
│   ├── zombies.sh       # ps check for state Z
│   └── fds.sh           # ls /proc/<pid>/fd | wc -l before/after 100 jobs
└── docs/
    ├── protocol.md      # the one-page protocol
    └── trace/           # logs/traces for the report (policy trace, the real failure)