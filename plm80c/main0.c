/****************************************************************************
 *  main0.c: part of the C port of Intel's ISIS-II plm80c             *
 *  The original ISIS-II application is Copyright Intel                     *
 *																			*
 *  Re-engineered to C by Mark Ogden <mark.pm.ogden@btinternet.com> 	    *
 *                                                                          *
 *  It is released for hobbyist use and for academic interest			    *
 *                                                                          *
 ****************************************************************************/

#include "plm.h"
//static byte copyright[] = "[C] 1976, 1977, 1982 INTEL CORP";

jmp_buf exception;

static void FinishLexPass()
{
    if (afterEOF)
        SyntaxError(ERR87);	/* MISSING 'end' , end-OF-FILE ENCOUNTERED */
    WriteLineInfo();
    WrByte(L_EOF);
    RewindTx1();
    TellF(&srcFil, (loc_t *)&srcFileTable[srcFileIdx + 8]);
    Backup((loc_t *)&srcFileTable[srcFileIdx + 8], offLastCh - offCurCh);
    CloseF(&srcFil);
} /* FinishLexPass() */


static void ParseCommandLine()
{
    InitF(&srcFil, "SOURCE", (char *)&srcFileTable[srcFileIdx]);
    OpenF(&srcFil, 1);
    SeekF(&srcFil,  (loc_t *)&srcFileTable[srcFileIdx + 8]);
    offCurCh = offLastCh;
    if (offFirstChM1 != 0)
        while (cmdLineP != 0) {
            ParseControlLine(offFirstChM1 + ByteP(cmdLineP));   // ParseControlLine will move to first char
            offFirstChM1 = 2;   // offset to first char - 1
            cmdLineP = CmdP(cmdLineP)->link;                    // continuation line
        }
    offFirstChM1 = 0;       // 0 if no more cmd line
    curScopeP = (wpointer)curScope;
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
    inChrP = (byte *)"\n" - 1; // GNxtCh will see \n and get a non blank line
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
    blockDepth = 1;
    procChains[1] = 0;
    GNxtCh();               // get the first char
} /* ParseCommandLine() */

static void LexPass()
{
    ParseCommandLine();
    ParseProgram();
} /* LexPass() */


word Start0()
{
    if (setjmp(exception) == 0) {
        state = 20;	/* 9B46 */
        LexPass();
    }
    FinishLexPass();		/* exception goes to here */
    return 1; // Chain(overlay[1]);
}
