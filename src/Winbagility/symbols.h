#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

typedef struct PDB_PARSER_T_ {
	HANDLE      hProcess;
	uint64_t    Base;
	void*       pBuffer;
}PDB_PARSER_T;


bool PdbOpenPdb(PDB_PARSER_T *pPdbParserHandle, const char *pPDBPath);
bool PdbGetSymbolsRVA(PDB_PARSER_T  *pPdbParserHandle, const char *pSymbolName, uint64_t *pRVA);
bool PdbClose(PDB_PARSER_T  *pPdbParserHandle);

#endif //__SYMBOLS_H__