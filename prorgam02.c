// Program - 02  (Shoetest Job First)

#include <stdio.h>
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void sortProcessByBurst(int n, int burst[], int process[])
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (burst[j] > burst[j + 1])
            {
                swap(&burst[j], &burst[j + 1]);
                swap(&process[j], &process[j + 1]);
            }
}
void calculateTimes(int processes[], int n, int burst_time[])
{
    int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
    // Sort processes by burst time
    sortProcessByBurst(n, burst_time, processes);
    // Calculate waiting times and turn-around times
    wait_time[0] = 0;
    tat[0] = burst_time[0];
    for (int i = 1; i < n; i++)
    {
        wait_time[i] = wait_time[i - 1] + burst_time[i - 1];
        tat[i] = wait_time[i] + burst_time[i];
    }
    printf("Processes Burst time Waiting time Turn around time\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += wait_time[i];
        total_tat += tat[i];
        printf("\t%d\t\t %d\t\t\t%d\t\t\t\t%d\n", i + 1, burst_time[i], wait_time[i], tat[i]);
    }
    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n);
}
int main()
{
    int processes[] = {1, 2, 3, 4};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {6, 8, 7, 3};
    calculateTimes(processes, n, burst_time);
    return 0;
}