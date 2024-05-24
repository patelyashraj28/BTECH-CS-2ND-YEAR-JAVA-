#include <windows.h>
#include <stdio.h>
HANDLE mutexReadCount;
HANDLE mutexResource;
int readCount = 0;
DWORD WINAPI reader(LPVOID Param) {
 int readerId = *((int*)Param);
 WaitForSingleObject(mutexReadCount, INFINITE);
 readCount++;
 if (readCount == 1) {
 WaitForSingleObject(mutexResource, INFINITE);
 }
 ReleaseMutex(mutexReadCount);
 // Reading section
 printf("Reader %d is reading\n", readerId);
 Sleep(1000); // Simulate reading time
 printf("Reader %d finished reading\n", readerId);
 WaitForSingleObject(mutexReadCount, INFINITE);
 readCount--;
 if (readCount == 0) {
 ReleaseMutex(mutexResource);
 }
 ReleaseMutex(mutexReadCount);
 return 0;
}
DWORD WINAPI writer(LPVOID Param) {
 int writerId = *((int*)Param);
 printf("Writer %d is trying to write\n", writerId);
 WaitForSingleObject(mutexResource, INFINITE);
 printf("Writer %d is writing\n", writerId);
 Sleep(2000); // Simulate writing time
 printf("Writer %d finished writing\n", writerId);
 ReleaseMutex(mutexResource);
 return 0;
}
int main() {
 HANDLE hThreads[15];
 int ids[15];
 mutexReadCount = CreateMutex(NULL, FALSE, NULL);
 mutexResource = CreateMutex(NULL, FALSE, NULL);
 for (int i = 0; i < 10; i++) {
 ids[i] = i + 1;
 hThreads[i] = CreateThread(NULL, 0, reader, &ids[i], 0, NULL);
 }
 for (int i = 10; i < 15; i++) {
 ids[i] = i - 9;
 hThreads[i] = CreateThread(NULL, 0, writer, &ids[i], 0, NULL);
 }
 WaitForMultipleObjects(15, hThreads, TRUE, INFINITE);
 for (int i = 0; i < 15; i++) {
 CloseHandle(hThreads[i]);
 }
 CloseHandle(mutexReadCount);
 CloseHandle(mutexResource);
 return 0;
}
