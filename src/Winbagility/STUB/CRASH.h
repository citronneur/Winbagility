

typedef struct CRASH_TYPE_T_
{
    HANDLE      hFile;
    uint64_t    uFileSize;
    uint8_t*    pFileData;
    uint64_t    Cr3Value;
    uint64_t    LSTARValue;
    uint64_t    v_KPCR;
    uint64_t    GDTRB;
    uint64_t    IDTRB;
    KTRAP_FRAME TrapFrame;
}CRASH_TYPE_T;


CRASH_TYPE_T* CRASH_Open(char *pFileName);
bool CRASH_Init(CRASH_TYPE_T *pUserHandle);
bool CRASH_GetPhysicalMemorySize(CRASH_TYPE_T *pUserHandle, uint64_t *pPhysicalMemorySize);
bool CRASH_ReadRegister(CRASH_TYPE_T *pUserHandle, uint32_t CpuId, uint16_t RegisterId, uint64_t *pRegisterValue);
bool CRASH_ReadMsr(CRASH_TYPE_T *pUserHandle, uint32_t CpuId, uint32_t MsrId, uint64_t *pMSRValue);
bool CRASH_ReadPhysicalMemory(CRASH_TYPE_T* pUserHandle, uint8_t *pDstBuffer, uint32_t ReadSize, uint64_t PhysicalAddress);
bool CRASH_ReadVirtualMemory(CRASH_TYPE_T* pUserHandle,
    uint32_t CpuId,
    uint8_t *pDstBuffer,
    uint32_t ReadSize,
    uint64_t VirtualAddress);
bool CRASH_Pause(CRASH_TYPE_T *pUserHandle);
bool CRASH_Resume(CRASH_TYPE_T *pUserHandle);
bool CRASH_SingleStep(CRASH_TYPE_T *pUserHandle, uint32_t CpuId);
bool CRASH_Pause(CRASH_TYPE_T *pUserHandle);
bool CRASH_WriteRegister(CRASH_TYPE_T *, uint32_t CpuId, uint16_t RegisterId, uint64_t RegisterValue);
bool CRASH_UnsetBreakpoint(CRASH_TYPE_T *, uint8_t BreakPointId);
bool CRASH_GetFxState64(CRASH_TYPE_T *pUserHandle, uint32_t CpuId, void *pFxState64);
bool CRASH_SetFxState64(CRASH_TYPE_T *pUserHandle, uint32_t CpuId, void *pFxState64);
bool CRASH_WriteRegister(CRASH_TYPE_T *, uint32_t CpuId, uint16_t RegisterId, uint64_t RegisterValue);
bool CRASH_SingleStep(CRASH_TYPE_T *, uint32_t CpuId);
bool CRASH_WritePhysicalMemory(CRASH_TYPE_T* pUserHandle, uint8_t *pSrcBuffer, uint32_t WriteSize, uint64_t PhysicalAddress);
bool CRASH_WriteVirtuallMemory(CRASH_TYPE_T* pUserHandle, uint32_t CpuId, uint8_t *pSrcBuffer, uint32_t WriteSize, uint64_t VirtualAddr);
int  CRASH_SetBreakpoint(CRASH_TYPE_T* pUserHandle, uint32_t CpuId, FDP_BreakpointType BreakpointType, uint8_t BreakpointId, FDP_Access BreakpointAccessType, FDP_AddressType BreakpointAddressType, uint64_t BreakpointAddress, uint64_t BreakpointLength);

bool CRASH_GetCpuState(CRASH_TYPE_T* pUserHandle, uint32_t CpuId, uint16_t *pState);