#ifndef __WINDOWSPROFILS_H_
#define __WINDOWSPROFILS_H_

#pragma pack(push)
typedef struct _WINDOWS_PROFIL_T_ {
    char        *pGUID;
    char        *pVersionName;
    uint64_t    KiWaitAlwaysOffset;
    uint64_t    KiWaitNeverOffset;
    uint64_t    KdpDataBlockEncodedOffset;
    uint64_t    KdDebuggerDataBlockOffset;
    uint64_t    KdVersionBlockOffset;
    uint64_t    KiDivideErrorFaultOffset;
    uint64_t    KiTrap00Offset;
    uint64_t    KdpDebuggerDataListHeadOffset;
    bool        bClearKdDebuggerDataBlock;
    bool        bIsX86;
}WINDOWS_PROFIL_T;
#pragma pack(pop)

#endif //__WINDOWSPROFILS_H_