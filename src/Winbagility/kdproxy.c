#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/Types.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "FDP.h"
#include "utils.h"
#include "kd.h"


HANDLE proxyDBGPipe; //Windbg->Proxy
HANDLE proxyVMPipe; //Proxy->VM
bool bProxyRunning;
HANDLE ghMutex;


//Aka VM->Windbg
DWORD WINAPI DebuggeeToWinDbg(LPVOID lpParam)
{
	KD_PACKET_T* pKdPkt = (KD_PACKET_T*)malloc(65 * 1024);
	if (pKdPkt != NULL){
		while (bProxyRunning == true){
			KdPacketType result = ReadKDPipe(proxyVMPipe, pKdPkt);
			if (result != KdNoPacket){
				DWORD numBytesWritten = WriteKDPipe(proxyDBGPipe, pKdPkt);
				WaitForSingleObject(ghMutex, INFINITE);
				printf("[VM->Windbg] Write to Windbg : %d\n", numBytesWritten);
				ParseKDPkt(pKdPkt);
				ReleaseMutex(ghMutex);
			}
		}
		free(pKdPkt);
	}
	return 0;
}

//Aka Windbg->VM
DWORD WINAPI WindDbgToDebuggee(LPVOID lpParam)
{
	KD_PACKET_T* pKdPkt = (KD_PACKET_T*)malloc(65 * 1024);
	int result;
	while (bProxyRunning == true){
		DWORD numBytesRead = 0;
		DWORD numBytesWritten = 0;
		result = ReadKDPipe(proxyDBGPipe, pKdPkt);
		if (result != KdNoPacket){
			if (result == KdBreakinPacket){ //TODO: return fast-break !
				char endOfData = 0x62; //Define fast-break !
				printf("[BREAK]\n");
				WriteFile(proxyVMPipe, &endOfData, 1, &numBytesWritten, NULL);
				FlushFileBuffers(proxyVMPipe);
			}
			else{
				numBytesWritten = WriteKDPipe(proxyVMPipe, pKdPkt);
				WaitForSingleObject(ghMutex, INFINITE);
				printf("[Windbg->VM] Write to VM : %d\n", numBytesWritten);
				ParseKDPkt(pKdPkt);
				ReleaseMutex(ghMutex);
			}
		}
	}
	return 0;
}



bool startKDProxy()
{
	HANDLE hDebuggeeToWinDbg;
	HANDLE hWinDbgToDebuggee;

	printf("Start KD Proxy...\n");
	if (OpenNamedPipe(&proxyVMPipe, "\\\\.\\pipe\\server") == false){
		printf("Failed to OpenNamedPipe\n");
		return false;
	}

	if (CreateConnectNamedPipe(&proxyDBGPipe, "\\\\.\\pipe\\client") == false){
		printf("Failed to CreateConnectNamedPipe\n");
		return false;
	}
	
	//Wait synchronisation
	Sleep(100);

	bProxyRunning = true;

	hDebuggeeToWinDbg = CreateThread(NULL, 0, DebuggeeToWinDbg, NULL, 0, NULL);
	if (hDebuggeeToWinDbg == INVALID_HANDLE_VALUE){
		printf("Failed to CreateThread (DebuggeeToWinDbg)\n");
		return false;
	}
	hWinDbgToDebuggee = CreateThread(NULL, 0, WindDbgToDebuggee, NULL, 0, NULL);
	if (hWinDbgToDebuggee == INVALID_HANDLE_VALUE){
		printf("Failed to CreateThread (WindDbgToDebuggee)\n");
		return false;
	}

	printf("Press a key to stop proxy.\n");
	getchar();

	bProxyRunning = false;
	WaitForSingleObject(hWinDbgToDebuggee, INFINITE);
	WaitForSingleObject(hDebuggeeToWinDbg, INFINITE);

	return true;

}