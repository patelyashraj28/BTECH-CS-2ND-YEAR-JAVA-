// Program - 01  (FCFS)
    
#include<stdio.h>
void findWaitingTime(int processes[], int n, int burst_time[], int wait_time[])
{
    wait_time[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wait_time[i] = burst_time[i - 1] + wait_time[i - 1];
    }
}
void findTurnAroundTime(int processes[], int n, int burst_time[], int wait_time[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = burst_time[i] + wait_time[i];
    }
}
void findavgTime(int processes[], int n, int burst_time[])
{
    int wait_time[n], tat[n];
    float total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, burst_time, wait_time);
    findTurnAroundTime(processes, n, burst_time, wait_time, tat);
    printf("Processes Burst time Waiting time Turn around time\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += wait_time[i];
        total_tat += tat[i];
        printf("\t%d \t\t\t%d \t\t\t%d \t\t\t%d\n", i + 1, burst_time[i], wait_time[i], tat[i]);
    }
    printf("Average waiting time = %.2f\n", total_wt / n);
    printf("Average turn around time = %.2f\n", total_tat / n);
}
int main()
{
    int processes[] = {1, 2, 3, 4};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {21, 3, 6, 2};
    findavgTime(processes, n, burst_time);
    return 0;
}