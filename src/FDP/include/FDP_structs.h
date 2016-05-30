#ifndef FDP_STRUCTS_H__
#define FDP_STRUCTS_H__

//#include <stdint.h>
//#include <stdbool.h>

enum
{
    FDPCMD_INIT,
    FDPCMD_PHYSICAL_VIRTUAL,
    FDPCMD_READ_PHYSICAL,
    FDPCMD_READ_REGISTER,
    FDPCMD_READ_MSR,
    FDPCMD_WRITE_MSR,
    FDPCMD_GET_MEMORYSIZE,
    FDPCMD_PAUSE_VM,
    FDPCMD_RESUME_VM,
    FDPCMD_SEARCH_PHYSICAL_MEMORY,
    FDPCMD_SEARCH_VIRTUAL_MEMORY,
    FDPCMD_UNSET_BP,
    FDPCMD_SET_BP,
    FDPCMD_VIRTUAL_PHYSICAL,
    FDPCMD_WRITE_PHYSICAL,
    FDPCMD_WRITE_VIRTUAL,
    FDPCMD_GET_STATE,
    FDPCMD_READ_VIRTUAL,
    FDPCMD_WRITE_REGISTER,
    FDPCMD_GET_FXSTATE,
    FDPCMD_SET_FXSTATE,
    FDPCMD_SINGLE_STEP,
    FDPCMD_GET_CPU_COUNT,
    FDPCMD_GET_CPU_STATE,
    FDPCMD_GET_CURRENT_CPU,
    FDPCMD_SWITCH_CPU,
    FDPCMD_REBOOT,
    FDPCMD_SAVE,
    FDPCMD_RESTORE,
    FDPCMD_INJECT_INTERRUPT,
    FDPCMD_TEST
};

typedef struct _FDP_UnsetBreakpoint_req
{
    uint8_t cmdType;
    uint8_t breakPointId;
} FDP_UnsetBreakpoint_req;

typedef struct _FDP_SetBreakpoint_req
{
    uint8_t cmdType;
    uint8_t breakPointId;
    uint64_t breakAddress;
} FDP_SetBreakpoint_req;

#pragma pack(push, 1)
#pragma warning( disable : 4200 )

#define _1M    1024*1024
#define FDP_MAX_DATA_SIZE   10*_1M

typedef _declspec(align(1)) struct FDP_SHM_CANAL_
{
    volatile bool lock; //Per channel lock
    volatile bool bDataPresent; //is data present
    volatile bool bStatus;
    volatile uint32_t dataSize;
    volatile uint8_t data[FDP_MAX_DATA_SIZE];
} FDP_SHM_CANAL;

typedef _declspec(align(1)) struct FDP_SHM_SHARED_
{
    volatile bool lock; //General lock for the whole FDP_SHM_SHARED
    volatile bool stateChangedLock;
    volatile bool stateChanged;
    FDP_SHM_CANAL ClientToServer;
    FDP_SHM_CANAL ServerToClient;
} FDP_SHM_SHARED;

typedef _declspec(align(1)) struct FDP_SHM_
{
    FDP_SHM_SHARED *pSharedFDPSHM;              //Shared part of the FDP SHM
    uint8_t InputBuffer[FDP_MAX_DATA_SIZE];     //Used as temporary input buffer
    uint8_t OutputBuffer[FDP_MAX_DATA_SIZE];    //Used as temporary output buffer

    FDP_SERVER_INTERFACE_T    *pFdpServer;
} FDP_SHM;

#define FDP_SHM_SHARED_SIZE sizeof(FDP_SHM_SHARED)


typedef struct FDP_SIMPLE_PKT_REQ_
{
    uint8_t Type;
} FDP_SIMPLE_PKT_REQ;

typedef struct FDP_READ_PHYSICAL_MEMORY_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    uint64_t PhysicalAddress;
    uint32_t ReadSize;
} FDP_READ_PHYSICAL_MEMORY_PKT_REQ;

typedef struct FDP_READ_VIRTUAL_MEMORY_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    uint64_t VirtualAddress;
    uint32_t ReadSize;
} FDP_READ_VIRTUAL_MEMORY_PKT_REQ;

typedef struct FDP_WRITE_PHYSICAL_MEMORY_PKT_REQ_
{
    uint8_t Type;
    uint64_t PhysicalAddress;
    uint32_t WriteSize;
    uint8_t Data[];
} FDP_WRITE_PHYSICAL_MEMORY_PKT_REQ;

typedef struct FDP_WRITE_VIRTUAL_MEMORY_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    uint64_t VirtualAddress;
    uint32_t WriteSize;
    uint8_t Data[];
} FDP_WRITE_VIRTUAL_MEMORY_PKT_REQ;

typedef struct FDP_SEARCH_PHYSICAL_MEMORY_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    uint32_t PatternSize;
    uint64_t StartOffset;
    uint8_t PatternData[];
} FDP_SEARCH_PHYSICAL_MEMORY_PKT_REQ;

typedef struct FDP_SEARCH_VIRTUAL_MEMORY_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    uint32_t PatternSize;
    uint64_t StartOffset;
    uint8_t PatternData[];
} FDP_SEARCH_VIRTUAL_MEMORY_PKT_REQ;

typedef struct FDP_READ_REGISTER_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    FDP_Register RegisterId;
} FDP_READ_REGISTER_PKT_REQ;

typedef struct FDP_READ_MSR_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    uint64_t MsrId;
} FDP_READ_MSR_PKT_REQ;

typedef struct FDP_WRITE_MSR_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    uint64_t MsrId;
    uint64_t MsrValue;
} FDP_WRITE_MSR_PKT_REQ;

typedef struct FDP_WRITE_REGISTER_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    FDP_Register RegisterId;
    uint64_t RegisterValue;
} FDP_WRITE_REGISTER_PKT_REQ;

typedef struct FDP_VIRTUAL_PHYSICAL_PKT_REQ
{
    uint8_t Type;
    uint32_t CpuId;
    uint64_t VirtualAddress;
} FDP_VIRTUAL_PHYSICAL_PKT_REQ;

typedef struct FDP_GET_STATE_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
} FDP_GET_STATE_PKT_REQ;

typedef struct FDP_SINGLE_STEP_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
} FDP_SINGLE_STEP_PKT_REQ;

typedef struct FDP_GET_CPU_STATE_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
} FDP_GET_CPU_STATE_PKT_REQ;

typedef struct FDP_UNSET_BREAKPOINT_PKT_REQ
{
    uint8_t Type;
    uint8_t BreakpointId;
} FDP_CLEAR_BREAKPOINT_PKT_REQ;

/*typedef struct FDP_SWITCH_CPU_PKT_REQ_
{
uint8_t Type;
uint32_t CPUIndex;
} FDP_SWITCH_CPU_PKT_REQ;*/

typedef struct FDP_SET_BREAKPOINT_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    FDP_BreakpointType BreakpointType;
    uint8_t BreakpointId;
    FDP_Access BreakpointAccessType;
    FDP_AddressType BreakpointAddressType;
    uint64_t BreakpointAddress;
    uint64_t BreakpointLength;
} FDP_SET_BREAKPOINT_PKT_REQ;

typedef struct FDP_INJECT_INTERRUPT_PKT_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    uint32_t InterruptionCode;
    uint32_t ErrorCode;
    uint64_t Cr2Value;
} FDP_INJECT_INTERRUPT_PKT_REQ;

typedef struct FDP_SET_FX_STATE_REQ_
{
    uint8_t Type;
    uint32_t CpuId;
    FDP_XSAVE_FORMAT64_T FxState64;
}FDP_SET_FX_STATE_REQ;
#pragma pack(pop)

#endif
