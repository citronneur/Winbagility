#ifndef __MMU_H__
#define __MMU_H__

#define PAGE_SIZE 4096


bool WDBG_SearchVirtualMemory(WINBAGILITY_CONTEXT_T *pWinbagilityCtx, 
                                        uint8_t *pPatternData, 
                                        uint32_t PatternSize, 
                                        uint64_t StartVirtualAddress, 
                                        uint64_t EndOffset, 
                                        uint64_t *pFoundVirtualAddress);


#endif //__MMU_H__