#include "linker.h"
#include "gcl.h"
#include "mts_new.h"

GCL_CommandChain*  dword_800AB3B8 = 0; //sdata

void GCL_80020B68(void);
void sub_80021264(void);
void GCL_AddBasicBuiltInCommands_8002040C(void);
void GCL_LoadData_80020064(unsigned char*);

void GV_SetFileHandler_80015418(char, void*);


int SECTION(".sbss") gGcl_main_or_demo_800AB990;

int SECTION(".sbss") dword_800AB994;

int SECTION(".sbss") dword_800AB998;

int GCL_FileHandler_8001FC88(unsigned char* pFileData, int hashedName)
{
    if (hashedName == gGcl_main_or_demo_800AB990)
    {
        GCL_LoadData_80020064(pFileData);
    }
    return 1;
}


void GCL_SetMainOrDemo_8001FCB0(int bMain)
{
    gGcl_main_or_demo_800AB990 = (bMain == 1) ? 0x6A242 : 0x6EA54;
}

void GCL_StartDaemon_8001FCDC(void)
{
    GCL_80020B68();
    sub_80021264();
    GCL_AddBasicBuiltInCommands_8002040C();
    GV_SetFileHandler_80015418('g', GCL_FileHandler_8001FC88);
    GCL_SetMainOrDemo_8001FCB0(0);
}

void GCL_Null_8001FD24(void)
{

}

int GCL_InitCommandTable_8001FD2C(GCL_CommandChain* pChain)
{
    // Set the new chains next to the existing chain
    pChain->pNext = dword_800AB3B8;

    // Update the existing chain to be the new chain
    dword_800AB3B8 = pChain;
    
    return 0;
}

extern const char aCommandNotFoun[];

GCL_CommandTableEntry* GCL_FindCommand_8001FD40(int hashedName)
{
    GCL_CommandTableEntry* pTableIter;
    int commandCount;
    GCL_CommandChain* pChainIter;
  
    for (pChainIter = dword_800AB3B8 ; pChainIter ; pChainIter = pChainIter->pNext)
    {
        pTableIter = pChainIter->pTable;
        for (commandCount = pChainIter->commandTableSize; 0 < commandCount; commandCount--)
        {
            if (pTableIter->hashCode == hashedName)
            {
                return pTableIter;
            }
            pTableIter++;
        }
    }
    mts_printf_8008BBA0(aCommandNotFoun);
    return 0;
}

void GCL_Push_80020934(unsigned char*);
void GCL_80020690(unsigned char*);
void GCL_Pop_80020950(void);

#define GCL_ReadShort(p) ( p[1] ) | ( p[0] << 8 )
#define GCL_AdvanceShort(p) p += sizeof(short)

#define GCL_ReadByte(p) p[0]
#define GCL_AdvanceByte(p) p += sizeof(unsigned char)

int GCL_8001FDB0(unsigned char* pScript)
{
    int commandRet;

    GCL_CommandTableEntry* pFoundCommand = GCL_FindCommand_8001FD40(GCL_ReadShort(pScript));
    GCL_AdvanceShort(pScript);
    
    GCL_Push_80020934(pScript + GCL_ReadByte(pScript));
    GCL_AdvanceByte(pScript);

    GCL_80020690(pScript); // save command return address?

    commandRet = pFoundCommand->function(pScript);

    GCL_Pop_80020950();

    return commandRet;
}
