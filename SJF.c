#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int processid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int completionTime;
    bool isActive;
} Process;

int main() {

    // number of processes
    int N = 5;

    // initialize processes
    Process process[5] = {
        {0, 0, 8, 0, 0, 1},
        {1, 3, 3, 0, 0, 0},
        {2, 4, 5, 0, 0, 0},
        {3, 7, 9, 0, 0, 0},
        {4, 9, 1, 0, 0, 0}
    };
    int currProcess = 0;

    // loop through each execution step
    printf("Schedule:");
    int step = 0;
    int completeProcesses = 0;
    while(completeProcesses < N) {
        // activate on arrival time
        for (int i = 0; i < N; i++) {
            if (process[i].arrivalTime == step) {
                process[i].isActive = 1;
            }
        }

        // get min burst
        int minBurstTime = process[currProcess].burstTime;

        // get rid of step with 0 burst time
        if (process[currProcess].burstTime == 0) {
            process[currProcess].isActive = 0;
            process[currProcess].completionTime = step;
            // keep track of complete processes
            completeProcesses++;
            // reset minBurstTime
            minBurstTime = 100000;
        }

        // set current process based on shortest remaining burst time
        for (int i = 0; i < N; i++) {
            if (process[i].isActive != 0 && process[i].burstTime < minBurstTime) {

                // update waiting and completion time
                process[i].waitingTime = step - process[i].completionTime - process[i].arrivalTime;
                process[currProcess].completionTime = step;

                // update current process
                minBurstTime = process[i].burstTime;
                currProcess = i;
            }
        }

        // print out schedule
        if (completeProcesses < N) {
            printf(" %d", currProcess); 
        }

        // execute step
        // execute one step
        process[currProcess].burstTime--;
        // update to next step
        step++;
    }

    // print out average waiting/turnaround time
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    for (int i = 0; i < N; i++) {
        totalWaitTime += process[i].waitingTime;
        totalTurnaroundTime += process[i].completionTime - process[i].arrivalTime;
    }

    // print out details
    printf("\nAverage Waiting Time: %d", totalWaitTime/N);
    printf("\nAverage Turnaround Time: %d\n", totalTurnaroundTime/N);
}