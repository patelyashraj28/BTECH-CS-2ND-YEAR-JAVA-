// Program - 04 Round Robin CPU Scheduling Algorithm
#include <stdio.h>
typedef struct
{
    int id;
    int burstTime;
} Process;
void findWaitingTime(Process processes[], int n, int quantum)
{
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = processes[i].burstTime;
    int t = 0; // Current time
    while (1)
    {
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = 0; // There is a pending process

                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t += rem_bt[i];
                    processes[i].burstTime = t; // Store waiting time
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
}
void findTurnAroundTime(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
        processes[i].burstTime += processes[i].burstTime;
}
void findAvgTime(Process processes[], int n, int quantum)
{
    findWaitingTime(processes, n, quantum);
    findTurnAroundTime(processes, n);
    int total_wt = 0, total_tat = 0;
    printf("Processes Burst time Waiting time Turn around time\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += processes[i].burstTime;
        total_tat += processes[i].burstTime + processes[i].burstTime;
        printf("\t%d\t\t%d\t\t\t%d\t\t\t%d\n", i + 1, processes[i].burstTime, processes[i].burstTime,
               processes[i].burstTime + processes[i].burstTime);
    }
    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn around time = %.2f\n", (float)total_tat / n);
}
int main()
{
    Process processes[] = {{1, 24}, {2, 3}, {3, 3}};
    int n = sizeof(processes) / sizeof(processes[0]);
    int quantum = 4;
    findAvgTime(processes, n, quantum);
    return 0;
}