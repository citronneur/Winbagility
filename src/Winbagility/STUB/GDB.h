
#include "FDP.h"

typedef struct GDB_TYPE_T_{
    SOCKET        Sock;
    bool        bInContinue;
    uint64_t    HardwareBreakpoint[4];
    uint64_t    Kpcr;
    uint64_t    Idtrb;
    uint64_t    Gdtrb;
    bool        bIsX86;
}GDB_TYPE_T;


GDB_TYPE_T* GDB_Open(char *pHostPort);
bool GDB_Init(GDB_TYPE_T* pGDB);
bool GDB_ReadRegister(GDB_TYPE_T* pGDB, uint32_t CpuId, FDP_Register RegisterId, uint64_t *pRegisterValue);
bool GDB_WriteRegister(GDB_TYPE_T* pGDB, uint32_t CpuId, FDP_Register RegisterId, uint64_t RegisterValue);
bool GDB_WriteRegisterDummy(GDB_TYPE_T* pGDB, uint32_t CpuId, FDP_Register RegisterId, uint64_t RegisterValue);
bool GDB_SingleStep(GDB_TYPE_T* pGDB);
bool GDB_ReadVirtualMemory(GDB_TYPE_T* pGDB, uint32_t CpuId, uint8_t *pDstBuffer, uint16_t ReadLength, uint64_t VirtualAddress);
bool GDB_WriteVirtualMemory(GDB_TYPE_T* pGDB, uint32_t CpuId, uint8_t *pSrcBuffer, uint16_t WriteLength, uint64_t VirtualAddress);
bool GDB_ReadMsr(GDB_TYPE_T* pGDB, uint32_t CpuId, uint32_t MsrId, uint64_t *pMsrValue);
bool GDB_ReadCr3(GDB_TYPE_T* pGDB, uint32_t CpuId, uint64_t *pCr3Value);
bool GDB_GetPhysicalMemorySize(GDB_TYPE_T* pGDB, uint64_t *pPhysicalMemorySize);
bool GDB_Pause(GDB_TYPE_T* pGDB);
bool GDB_UnsetBreakpoint(GDB_TYPE_T* pGDB, int iBreakpointId);
bool GDB_GetFxState64(GDB_TYPE_T* pGDB, uint32_t CpuId, void *pFxState64);
bool GDB_SetFxState64(GDB_TYPE_T* pGDB, uint32_t CpuId, void *pFxState64);
bool GDB_Test(GDB_TYPE_T* pGDB);
bool GDB_ReadPhysicalMemory(GDB_TYPE_T* pGDB, void *pDstBuffer, uint32_t ReadSize, uint64_t PhysicalAddress);
bool GDB_Resume(GDB_TYPE_T *pGDB);
bool GDB_GetCpuState(GDB_TYPE_T *pGDB, uint32_t CpuId, FDP_State *pDebuggeeState);
int  GDB_SetBreakpoint(GDB_TYPE_T *pGDB, uint32_t CpuId, FDP_BreakpointType BreakpointType, uint8_t BreakpointId, FDP_Access BreakpointAccessType, FDP_AddressType BreakpointAddressType, uint64_t BreakpointAddress, uint64_t BreakpointLength);
bool GDB_GetStateChanged(GDB_TYPE_T *pGDB);