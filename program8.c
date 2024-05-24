#include <windows.h>
#include <stdio.h>
#define NUM_PHILOSOPHERS 5
HANDLE forks[NUM_PHILOSOPHERS];
HANDLE philosophers[NUM_PHILOSOPHERS];
DWORD WINAPI philosopher(LPVOID Param);
void take_forks(int philosopher, int left, int right);
void put_forks(int philosopher, int left, int right);
DWORD WINAPI philosopher(LPVOID Param) {
 int id = *(int*)Param;
 int left_fork = id;
 int right_fork = (id + 1) % NUM_PHILOSOPHERS;
 // Reverse order for the last philosopher to avoid deadlock
 if (id == NUM_PHILOSOPHERS - 1) {
 left_fork = right_fork;
 right_fork = id;
 }
 while (1) {
 printf("Philosopher %d is thinking.\n", id);
 Sleep(1000); // Simulate thinking
 take_forks(id, left_fork, right_fork);
 printf("Philosopher %d is eating.\n", id);
 Sleep(1000); // Simulate eating
 put_forks(id, left_fork, right_fork);
 }
 return 0;
}
void take_forks(int philosopher, int left, int right) {
 WaitForSingleObject(forks[left], INFINITE);
 printf("Philosopher %d took the left fork %d.\n", philosopher, left);
 WaitForSingleObject(forks[right], INFINITE);
 printf("Philosopher %d took the right fork %d.\n", philosopher, right);
}
void put_forks(int philosopher, int left, int right) {
 ReleaseMutex(forks[left]);
 ReleaseMutex(forks[right]);
 printf("Philosopher %d put down both forks %d and %d.\n", philosopher, left, right);
}
int main() {
 int ids[NUM_PHILOSOPHERS];
 DWORD ThreadId;
 for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
 forks[i] = CreateMutex(NULL, FALSE, NULL);
 }
 for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
 ids[i] = i;
 philosophers[i] = CreateThread(NULL, 0, philosopher, &ids[i], 0, &ThreadId);
 }
 WaitForMultipleObjects(NUM_PHILOSOPHERS, philosophers, TRUE, INFINITE);
 for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
 CloseHandle(philosophers[i]);
 CloseHandle(forks[i]);
 }
 return 0;
}
