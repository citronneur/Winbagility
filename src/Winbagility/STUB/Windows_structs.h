typedef struct _KTRAP_FRAME                    // 64 elements, 0x190 bytes (sizeof)
{
    /*0x000*/     UINT64       P1Home;
    /*0x008*/     UINT64       P2Home;
    /*0x010*/     UINT64       P3Home;
    /*0x018*/     UINT64       P4Home;
    /*0x020*/     UINT64       P5;
    /*0x028*/     CHAR         PreviousMode;
    /*0x029*/     UINT8        PreviousIrql;
    /*0x02A*/     UINT8        FaultIndicator;
    /*0x02B*/     UINT8        ExceptionActive;
    /*0x02C*/     ULONG32      MxCsr;
    /*0x030*/     UINT64       Rax;
    /*0x038*/     UINT64       Rcx;
    /*0x040*/     UINT64       Rdx;
    /*0x048*/     UINT64       R8;
    /*0x050*/     UINT64       R9;
    /*0x058*/     UINT64       R10;
    /*0x060*/     UINT64       R11;
    union                                      // 2 elements, 0x8 bytes (sizeof)
    {
        /*0x068*/         UINT64       GsBase;
        /*0x068*/         UINT64       GsSwap;
    };
    /*0x070*/     struct _M128A Xmm0;                        // 2 elements, 0x10 bytes (sizeof)
    /*0x080*/     struct _M128A Xmm1;                        // 2 elements, 0x10 bytes (sizeof)
    /*0x090*/     struct _M128A Xmm2;                        // 2 elements, 0x10 bytes (sizeof)
    /*0x0A0*/     struct _M128A Xmm3;                        // 2 elements, 0x10 bytes (sizeof)
    /*0x0B0*/     struct _M128A Xmm4;                        // 2 elements, 0x10 bytes (sizeof)
    /*0x0C0*/     struct _M128A Xmm5;                        // 2 elements, 0x10 bytes (sizeof)
    union                                      // 3 elements, 0x8 bytes (sizeof)
    {
        /*0x0D0*/         UINT64       FaultAddress;
        /*0x0D0*/         UINT64       ContextRecord;
        /*0x0D0*/         UINT64       TimeStampCKCL;
    };
    /*0x0D8*/     UINT64       Dr0;
    /*0x0E0*/     UINT64       Dr1;
    /*0x0E8*/     UINT64       Dr2;
    /*0x0F0*/     UINT64       Dr3;
    /*0x0F8*/     UINT64       Dr6;
    /*0x100*/     UINT64       Dr7;
    union                                      // 2 elements, 0x28 bytes (sizeof)
    {
        struct                                 // 5 elements, 0x28 bytes (sizeof)
        {
            /*0x108*/             UINT64       DebugControl;
            /*0x110*/             UINT64       LastBranchToRip;
            /*0x118*/             UINT64       LastBranchFromRip;
            /*0x120*/             UINT64       LastExceptionToRip;
            /*0x128*/             UINT64       LastExceptionFromRip;
        };
        struct                                 // 2 elements, 0x28 bytes (sizeof)
        {
            /*0x108*/             UINT64       LastBranchControl;
            /*0x110*/             ULONG32      LastBranchMSR;
            /*0x114*/             UINT8        _PADDING0_[0x1C];
        };
    };
    /*0x130*/     UINT16       SegDs;
    /*0x132*/     UINT16       SegEs;
    /*0x134*/     UINT16       SegFs;
    /*0x136*/     UINT16       SegGs;
    /*0x138*/     UINT64       TrapFrame;
    /*0x140*/     UINT64       Rbx;
    /*0x148*/     UINT64       Rdi;
    /*0x150*/     UINT64       Rsi;
    /*0x158*/     UINT64       Rbp;
    union                                      // 3 elements, 0x8 bytes (sizeof)
    {
        /*0x160*/         UINT64       ErrorCode;
        /*0x160*/         UINT64       ExceptionFrame;
        /*0x160*/         UINT64       TimeStampKlog;
    };
    /*0x168*/     UINT64       Rip;
    /*0x170*/     UINT16       SegCs;
    /*0x172*/     UINT8        Fill0;
    /*0x173*/     UINT8        Logging;
    /*0x174*/     UINT16       Fill1[2];
    /*0x178*/     ULONG32      EFlags;
    /*0x17C*/     ULONG32      Fill2;
    /*0x180*/     UINT64       Rsp;
    /*0x188*/     UINT16       SegSs;
    /*0x18A*/     UINT16       Fill3;
    /*0x18C*/     LONG32       CodePatchCycle;
}KTRAP_FRAME, *PKTRAP_FRAME;