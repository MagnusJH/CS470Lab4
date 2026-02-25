#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int isActive;
} Process;

int main() {
    // number of processes
    int N = 5;
    // time quantum
    int Q = 3;

    // initialize processes
    Process process[5] = {
        {0, 0, 8, 0, 1},
        {1, 2, 3, 0, 0},
        {2, 4, 5, 0, 0},
        {3, 5, 9, 0, 0},
        {4, 6, 1, 0, 0}
    };
    int currProcess = 0;

    // keep track of origianl bursts for later 
    int originalBursts[5];
    for (int i = 0; i < N; i++) {
        originalBursts[i] = process[i].burstTime;
    }

    // get total number of steps
    int totalSteps = 0;
    for (int i = 0; i < N; i++) {
        totalSteps += process[i].burstTime;
    }

    // loop through each execution step
    printf("Schedule:");
    int step = 0;
    int qStep = 0;
    int completeProcesses = 0;
    while(completeProcesses < N) {
        // activate on arrival
        for (int i = 0; i < N; i++) {
            if (process[i].arrivalTime == step) {
                process[i].isActive = 1;
            }
        }

        // move to next process if round is over
        if (qStep == Q || process[currProcess].burstTime == 0) {
            // get rid of step with 0 burst time
            if (process[currProcess].burstTime == 0) {
                process[currProcess].isActive = 0;
                process[currProcess].completionTime = step;
                // keep track of complete processes
                completeProcesses++;
            }

            if (completeProcesses < N) {
                // move to next process
                if (currProcess == N-1) {
                    currProcess = 0;
                } else {
                   currProcess++;
                }

                // loop until you find a process that is active
                while (!process[currProcess].isActive) {
                    if (currProcess == N-1) {
                        currProcess = 0;
                    } else {
                        currProcess++;
                    }
                }
            }

            // reset Q
            qStep = 0;
        }

        // print out schedule
        if (completeProcesses < N) {
            printf(" %d", currProcess); 
        }

        // execute step
        process[currProcess].burstTime--;
        step++;
        qStep++;
    }

    // calculate turnaround and waiting times
    int totalTurnaroundTime = 0;
    int totalWaitTime = 0;
    for (int i = 0; i < N; i++) {
        totalTurnaroundTime += process[i].completionTime - process[i].arrivalTime;
        totalWaitTime += process[i].completionTime - process[i].arrivalTime - originalBursts[i];
    }

    // print out details
    printf("\nAverage Waiting Time: %d", totalWaitTime/N);
    printf("\nAverage Turnaround Time: %d\n", totalTurnaroundTime/N);
}