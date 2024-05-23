//Program - 05
//Comparison of various CPU Scheduling Algorithms over different Scheduling Criteria. 
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int id;
    int burstTime;
    int priority;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
} Process;
// Utility function to sort processes by arrival time
int compareArrival(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->arrivalTime - p2->arrivalTime;
}
// Utility function to sort processes by burst time for SJF
int compareBurstTime(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->burstTime - p2->burstTime;
}
// Utility function to sort processes by priority for Priority Scheduling
int comparePriority(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->priority - p2->priority;
}
// Function to calculate waiting time and turnaround time
void calculateMetrics(Process p[], int n)
{
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].turnaroundTime = p[i].burstTime + p[i].waitingTime;
        total_wt += p[i].waitingTime;
        total_tat += p[i].turnaroundTime;
    }
    printf("Average Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);
}
// First Come First Serve Algorithm
void FCFS(Process p[], int n)
{
    printf("FCFS:\n");
    qsort(p, n, sizeof(Process), compareArrival);
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        if (currentTime < p[i].arrivalTime)
            currentTime = p[i].arrivalTime;
        p[i].waitingTime = currentTime - p[i].arrivalTime;
        currentTime += p[i].burstTime;
    }
    calculateMetrics(p, n);
}
// Shortest Job First Algorithm (non-preemptive)
void SJF(Process p[], int n)
{
    printf("SJF:\n");
    qsort(p, n, sizeof(Process), compareArrival);
    int completed = 0, currentTime = 0, minIndex = -1;
    int remaining = n;
    while (completed < n)
    {
        // Find process with shortest burst time among the arrived processes
        int minBurst = 999999;
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrivalTime <= currentTime && p[i].burstTime < minBurst && p[i].waitingTime == 0)
            {
                minBurst = p[i].burstTime;
                minIndex = i;
            }
        }
        if (minIndex == -1)
        {
            currentTime++;
        }
        else
        {
            p[minIndex].waitingTime = currentTime - p[minIndex].arrivalTime;
            currentTime += p[minIndex].burstTime;
            completed++;
            p[minIndex].waitingTime = (p[minIndex].waitingTime < 0) ? 0 : p[minIndex].waitingTime;
            minIndex = -1;
        }
    }
    calculateMetrics(p, n);
}
// Priority Scheduling Algorithm (non-preemptive)
void PriorityScheduling(Process p[], int n)
{
    printf("Priority:\n");
    qsort(p, n, sizeof(Process), comparePriority);
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        if (currentTime < p[i].arrivalTime)
            currentTime = p[i].arrivalTime;
        p[i].waitingTime = currentTime - p[i].arrivalTime;
        currentTime += p[i].burstTime;
    }
    calculateMetrics(p, n);
}
// Round Robin Algorithm
void RoundRobin(Process p[], int n, int quantum)
{
    printf("Round Robin:\n");
    qsort(p, n, sizeof(Process), compareArrival);
    int rem_bt[n];
    for (int i = 0; i < n; i++)
    {
        rem_bt[i] = p[i].burstTime;
    }
    int t = 0;
    while (1)
    {
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = 0;
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t += rem_bt[i];
                    p[i].waitingTime += t - p[i].burstTime - p[i].arrivalTime;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
    calculateMetrics(p, n);
}
int main()
{
    Process processes[] = {{1, 6, 2, 1}, {2, 8, 3, 1}, {3, 7, 1, 2}, {4, 3, 4, 3}};
    int n = sizeof(processes) / sizeof(processes[0]);
    int quantum = 4;
    FCFS(processes, n);
    SJF(processes, n);
    PriorityScheduling(processes, n);
    RoundRobin(processes,    n, quantum);
    return 0;
}