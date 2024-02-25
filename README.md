# OS scheduling stategies

This project is about programming 4 OS scheduling's algorithms: FCFS, RR, SJF, SRTN as a Lab01 project at my class

## Table of Contents
- [Work](#work)
- [Installation](#Installation)
- [Usage](#usage)
- [License](#license)

## Work
Please write a program to perform process scheduling according to the following requirements: 
- The programming language is of your choice.
- It can be run on the Windows operating system.
- It can be executed via the command line using the following syntax: <file_name>.exe <INPUT_FILE> <OUTPUT_FILE> 
  -  _For example_: 
    main.exe input.txt output.txt
- The input and output files are both saved in text format (*.txt).
- Syntax of the <INPUT_FILE>:
  - The first line: an integer from 1 to 4 representing the scheduling algorithm
    | # | Scheduling algorithm |
    |----------|----------|
    | 1   | FCFS (First Come First Serve) |
    | 2 | RR (Round Robin) |
    | 3  | SJF (Shortest Job First) |
    | 4 | SRTN (Shortest Remaining Time Next) |
  -  In case of the Round Robin scheduling algorithm, the second line is a positive integer representing the time quantum.
  -  The next line: a positive integer N representing the number of processes to be scheduled, up to maximum of 4 processes.
  -  The following N lines: each line describes the scheduling information of a process with the syntax:
  
        `<Arrival time in Ready Queue>` [`<CPU Burst Time>` `<Resource Usage Time>`]
  -  It is known that:
      -  In the scheduling table, each process can use CPU and R multiple times, but up to a maximum of 3 times for each (CPU/R)
      -  In the scheduling table, a process may complete earlier than other processes. This means that the number of CPU and R usages for each process is different.
      -  The system only has one resource R. The scheduling algorithm on resource R is always FCFS.
      -  Give pripority to new processes in case of conflict in the entrance of Ready Queue.
 
  For example:
  
    -  FCFS/SJF/SRTN
        ```
        1 
        3 
        0 5 3 4 
        1 4 
        2 3 3
        ```
        
        | # | Arrival Time | CPU | R | CPU |
        |---|:------------:|:---:|:-:|:---:|
        | 1 | 0            | 5   | 3 | 4   |
        | 2 | 1            | 4   |   |     |
        | 3 | 2            | 3   | 3 |     |
    -  Round Robin
        ```
        2 
        3 
        4 
        0 5 3 4 
        2 4 
        5 3 3 
        3 6 2 3 8 1  
        ```
        
        | # | Arrival Time | CPU | R | CPU | R | CPU |
        |---|:-------------:|:---:|---|:---:|---|:---:|
        | 1 | 0             | 5   | 3 | 4   |   |     |
        | 2 | 2             | 4   |   |     |   |     |
        | 3 | 5             | 3   | 3 |     |   |     |
        | 4 | 3             | 6   | 2 | 3   | 8 | 1   |
-  Syntax of the <OUTPUT_FILE>:
    -  The first line: an integer sequence separated by a single whitespace, represents the Gantt chart of the process scheduling on the CPU. Note that the numbers 1, 2, 3, 4 represent processes P1, P2, P3, P4; and a hyphen ( _ ) denotes the time slot during which no process is using the CPU.
    -  The second line: has a similar structure to the first line, but it represents the scheduling on the resource R.
    -  The third line: an integer sequence separated by a single whitespace, represents the turn-around time of all processes.
    -  The fourth line: an integer sequence separated by a single whitespace, represents the waiting time of all processes.

    For example:
      -  Input:
          ```
          1 
          3 
          0 5 3 4 
          1 4 
          2 3 3 
          ```
     -  Output:
          ```
          1 1 1 1 1 2 2 2 2 3 3 3 1 1 1 1 
          _ _ _ _ _ 1 1 1 _ _ _ _ 3 3 3 
          16 8 13 
          4 4 7 
          ```
          
        because:
        | second | 0 - 1 | 1 - 2 | 2 - 3 | 3 - 4 | 4 - 5 | 5 - 6 | 6 - 7 | 7 - 8 | 8 - 9 | 9 - 10 | 10 - 11 | 11 - 12 | 12 - 13 | 13 - 14 | 14 - 15 | 15 - 16 |
        | ------ | ------ | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ------ | ------- | ------- | ------- | ------- | ------- | ------- |
        | CPU    | P1     | P1    | P1    | P1    | P1    | P2    | P2    | P2    | P2    | P3     | P3      | P3      | P1      | P1      | P1      | P1      |
        | R      |        |       |       |       |       | P1    | P1    | P1    |       |        |         |         | P3      | P3      | P3      |         |

        |    | Turn-around Time | Waiting Time |
        | -- | ---------------- | ------------ |
        | P1 | 16               | 4            |
        | P2 | 8                | 4            |
        | P3 | 13               | 7            |
## Installation

Download all the .cpp files here, build them into one excutable file (.exe).

## Usage

Execute the .exe file built from [Installation](#Installation) through the command prompt with corresponding input and output files (.txt) like the instructions in [Work](#Work) have described.

## License

GNU General Public License v3.0

Copyright (c) 2024 m0nters

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
