#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>


#include "FDP.h"
#include "WindowsProfils.h"
#include "kdserver.h"
#include "mmu.h"
#include "utils.h"


bool WDBG_SearchVirtualMemory(WINBAGILITY_CONTEXT_T *pWinbagilityCtx, uint8_t *pPatternData, uint32_t PatternSize, uint64_t StartVirtualAddress, uint64_t EndOffset, uint64_t *pFoundVirtualAddress)
{
    uint64_t curOffset = 0;
    uint8_t TempBuffer[PAGE_SIZE];
    uint64_t leftToLook = EndOffset - curOffset;
    while (leftToLook){
        if (pWinbagilityCtx->pfnReadVirtualMemory(pWinbagilityCtx->pUserHandle, 0, TempBuffer, PAGE_SIZE, StartVirtualAddress + curOffset)){
            for (int i = 0; i < MIN(PAGE_SIZE - PatternSize, leftToLook); i++){
                if (memcmp(TempBuffer + i, pPatternData, PatternSize) == 0){
                    *pFoundVirtualAddress = StartVirtualAddress + curOffset + i;
                    return true;
                }
            }
        }
        curOffset = curOffset + MIN(leftToLook, PAGE_SIZE - PatternSize);
        leftToLook = EndOffset - curOffset;
    }
    *pFoundVirtualAddress = 0;
    return false;
}