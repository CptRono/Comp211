How to run task scheduler algorithm in terminal:

Must have these files in the same directory:
    - stack.h
    - graph.h
    - schedule.h

    - adjlistgraph.c
    - schedule.c
    - stack.c

    - .txt file (see morning.txt) with the tasks in the format: task -> dependency

To compile, run:
    cc -Wall -o scheduler adjlistgraph.c schedule.c stack.c