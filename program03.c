// Program -03  Priority CPU Scheduling Algorithm (Non-Preemptive)
#include <stdio.h>
typedef struct
{
    int id;
    int burstTime;
    int priority;
} Process;
void sortProcessesByPriority(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority > processes[j + 1].priority)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
void findWaitingTime(Process processes[], int n, int waitTime[])
{
    waitTime[0] = 0;
    for (int i = 1; i < n; i++)
    {
        waitTime[i] = processes[i - 1].burstTime + waitTime[i - 1];
    }
}
void findTurnAroundTime(Process processes[], int n, int waitTime[], int turnAroundTime[])
{
    for (int i = 0; i < n; i++)
    {
        turnAroundTime[i] = processes[i].burstTime + waitTime[i];
    }
}
void findAvgTime(Process processes[], int n)
{
    int waitTime[n], turnAroundTime[n], total_wt = 0, total_tat = 0;
    sortProcessesByPriority(processes, n);
    findWaitingTime(processes, n, waitTime);
    findTurnAroundTime(processes, n, waitTime, turnAroundTime);
    printf("Processes Burst time Priority Waiting time Turn around time\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += waitTime[i];
        total_tat += turnAroundTime[i];
        printf("\t%d\t\t\t%d\t\t\t%d\t\t %d\t\t\t%d\n", processes[i].id, processes[i].burstTime,
               processes[i].priority, waitTime[i], turnAroundTime[i]);
    }
    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn around time = %.2f\n", (float)total_tat / n);
}
int main()
{
    Process processes[] = {{1, 10, 2}, {2, 5, 0}, {3, 8, 1}};
    int n = sizeof(processes) / sizeof(processes[0]);
    findAvgTime(processes, n);
    return 0;
}