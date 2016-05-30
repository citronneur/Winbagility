#ifndef __UTILS_H__
#define __UTILS_H__

#include <intrin.h>
#include <Windows.h>
#include <stdint.h>

int roundup16(int value);
void dumpHexData(char *tmp, int len);
void printHexData(char *tmp, int len);

BOOL CreateNamedPipe(HANDLE *hPipe, char *pipeName);
BOOL OpenNamedPipe(HANDLE *hPipe, char *pipeName);
bool GetPipe(HANDLE hPipe, uint8_t* data, uint64_t size);
uint8_t Get8Pipe(HANDLE hPipe);
uint16_t Get16Pipe(HANDLE hPipe);
uint32_t Get32Pipe(HANDLE hPipe);
uint64_t Get64Pipe(HANDLE hPipe);
DWORD PutPipe(HANDLE hPipe, uint8_t *data, uint64_t size);
DWORD Put8Pipe(HANDLE hPipe, uint8_t data);
DWORD Put32Pipe(HANDLE hPipe, uint8_t data);
DWORD Put64Pipe(HANDLE hPipe, uint64_t data);

inline void ttas_spinlock_lock(volatile bool *lock){
	uint16_t test_counter = 0;
	while (true){
		if (*lock == 0){
			test_counter = 0;
			if (_InterlockedCompareExchange8((volatile char*)lock, 1, 0) == 0){
				MemoryBarrier();
				return;
			}
		}
		else{
			if ((test_counter & 0xFFFF) == 0xFFFF){
				Sleep(0);
			}
			else{
				test_counter++;
			}
		}
	}
}

inline void ttas_spinlock_unlock(volatile bool *lock){
	*lock = 0;
	MemoryBarrier();
	return;
}

inline uint64_t _rol64(uint64_t v, uint64_t s){
	return (v << s) | (v >> (64 - s));
}

#endif //__UTILS_H__