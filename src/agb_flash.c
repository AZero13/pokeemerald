#include "gba/gba.h"
#include "gba/flash_internal.h"

static u8 sTimerNum;
static u16 sTimerCount;
static vu16 *sTimerReg;
static u16 sSavedIme;

COMMON_DATA u8 gFlashTimeoutFlag = 0;
COMMON_DATA u8 (*PollFlashStatus)(u8 *) = NULL;
COMMON_DATA u16 (*WaitForFlashWrite)(u8 phase, u8 *addr, u8 lastData) = NULL;
COMMON_DATA u16 (*ProgramFlashSector)(u16 sectorNum, u8 *src) = NULL;
COMMON_DATA const struct FlashType *gFlash = NULL;
COMMON_DATA u16 (*ProgramFlashByte)(u16 sectorNum, u32 offset, u8 data) = NULL;
COMMON_DATA u16 gFlashNumRemainingBytes = 0;
COMMON_DATA u16 (*EraseFlashChip)() = NULL;
COMMON_DATA u16 (*EraseFlashSector)(u16 sectorNum) = 0;
COMMON_DATA const u16 (*gFlashMaxTime)[3] = NULL;

void SetReadFlash1(u16 *dest);

void SwitchFlashBank(u8 bankNum)
{
    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0xB0);
    FLASH_WRITE(0x0000, bankNum);
}

u16 ReadFlashId(void)
{
    u16 flashID;
    u16 readFlash1Buff[0x20];
    u8 (*readFlash1)(u8 *);
    vu16 i;

    SetReadFlash1(readFlash1Buff);
    readFlash1 = (u8 (*)(u8 *))((u8 *)readFlash1Buff + 1);

    // Enter ID mode.
    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0x90);
    for (i = 20000; i != 0; i--)
        ;

    flashID = readFlash1(FLASH_BASE + 1) << 8;
    flashID |= readFlash1(FLASH_BASE);

    // Leave ID mode.
    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0xF0);

    FLASH_WRITE(0x5555, 0xF0);
    for (i = 20000; i != 0; i--)
        ;

    return flashID;
}

void FlashTimerIntr(void)
{
    if (sTimerCount != 0 && --sTimerCount == 0)
        gFlashTimeoutFlag = 1;
}

u16 SetFlashTimerIntr(u8 timerNum, void (**intrFunc)(void))
{
    if (timerNum > 3)
        return 1;

    sTimerNum = timerNum;
    sTimerReg = &REG_TMCNT_L(sTimerNum);
    *intrFunc = FlashTimerIntr;
    return 0;
}

void StartFlashTimer(u8 phase)
{
    const u16 *maxTime = (const u16 *)(gFlashMaxTime + phase);
    sSavedIme = REG_IME;
    REG_IME = 0;
    sTimerReg[1] = 0;
    REG_IE |= (INTR_FLAG_TIMER0 << sTimerNum);
    gFlashTimeoutFlag = 0;
    sTimerCount = *maxTime++;
    *sTimerReg++ = *maxTime++;
    *sTimerReg-- = *maxTime++;
    REG_IF = (INTR_FLAG_TIMER0 << sTimerNum);
    REG_IME = 1;
}

void StopFlashTimer(void)
{
    REG_IME = 0;
    *sTimerReg++ = 0;
    *sTimerReg-- = 0;
    REG_IE &= ~(INTR_FLAG_TIMER0 << sTimerNum);
    REG_IME = sSavedIme;
}

u8 ReadFlash1(u8 *addr)
{
    return *addr;
}

void SetReadFlash1(u16 *dest)
{
    u16 i;
    u16 *src;

    PollFlashStatus = (u8 (*)(u8 *))((u8*)dest + 1);

    src = (u16 *)ReadFlash1;
    src = (u16 *)((u32)src ^ 1);

    i = ((u32)SetReadFlash1 - (u32)ReadFlash1) >> 1;

    while (i != 0)
    {
        *dest++ = *src++;
        i--;
    }
}

// This routine is copied to RAM, so the modern build explicitly uses byte accesses.
void ReadFlash_Core(vu8 *src, u8 *dest, u32 size)
{
    while (size-- != 0)
    {
        *dest++ = *src++;
    }
}

void ReadFlash(u16 sectorNum, u32 offset, u8 *dest, u32 size)
{
    u8 *src;
    u16 i;
    u16 readFlash_Core_Work[0x40];
    u16 *psrc;
    u16 *pdst;
    void (*readFlash_p)(vu8 *, u8 *, u32);

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | WAITCNT_SRAM_8;

    if (gFlash->romSize == FLASH_ROM_SIZE_1M)
    {
        SwitchFlashBank(sectorNum / SECTORS_PER_BANK);
        sectorNum %= SECTORS_PER_BANK;
    }

    psrc = (u16 *)ReadFlash_Core;
    psrc = (u16 *)((u32)psrc ^ 1);
    pdst = readFlash_Core_Work;

    i = ((u32)ReadFlash - (u32)ReadFlash_Core) >> 1;

    while (i != 0)
    {
        *pdst++ = *psrc++;
        i--;
    }

    readFlash_p = (void (*)(vu8 *, u8 *, u32))((u8 *)readFlash_Core_Work + 1);

    src = FLASH_BASE + (sectorNum << gFlash->sector.shift) + offset;

    readFlash_p(src, dest, size);
}

u32 VerifyFlashSector_Core(u8 *src, vu8 *tgt, u32 size)
{
    while (size-- != 0)
    {
        if (*tgt++ != *src++)
            return (u32)tgt - 1;
    }

    return 0;
}

u32 VerifyFlashSector(u16 sectorNum, u8 *src)
{
    u8 *tgt;
    u16 i;
    u16 verifyFlashSector_Core_Work[0x80];
    u16 *psrc;
    u16 *pdst;
    u16 size;
    u32 (*verifyFlash_p)(u8 *, vu8 *, u32);
    u32 result;

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | WAITCNT_SRAM_8;

    if (gFlash->romSize == FLASH_ROM_SIZE_1M)
    {
        SwitchFlashBank(sectorNum / SECTORS_PER_BANK);
        sectorNum %= SECTORS_PER_BANK;
    }

    psrc = (u16 *)VerifyFlashSector_Core;
    psrc = (u16 *)((u32)psrc ^ 1);
    pdst = verifyFlashSector_Core_Work;

    i = ((u32)VerifyFlashSector - (u32)VerifyFlashSector_Core) >> 1;

    while (i != 0)
    {
        *pdst++ = *psrc++;
        i--;
    }

    verifyFlash_p = (u32 (*)(u8 *, vu8 *, u32))((u8 *)verifyFlashSector_Core_Work + 1);

    tgt = FLASH_BASE + (sectorNum << gFlash->sector.shift);
    size = gFlash->sector.size;

    result = verifyFlash_p(src, tgt, size);
    return result;
}

u32 VerifyFlashSectorNBytes(u16 sectorNum, u8 *src, u32 n)
{
    u8 *tgt;
    u16 i;
    u16 verifyFlashSector_Core_Work[0x80];
    u16 *psrc;
    u16 *pdst;
    u32 (*verifyFlash_p)(u8 *, vu8 *, u32);
    u32 result;

    if (gFlash->romSize == FLASH_ROM_SIZE_1M)
    {
        SwitchFlashBank(sectorNum / SECTORS_PER_BANK);
        sectorNum %= SECTORS_PER_BANK;
    }

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | WAITCNT_SRAM_8;

    psrc = (u16 *)VerifyFlashSector_Core;
    psrc = (u16 *)((u32)psrc ^ 1);
    pdst = verifyFlashSector_Core_Work;

    i = ((u32)VerifyFlashSector - (u32)VerifyFlashSector_Core) >> 1;

    while (i != 0)
    {
        *pdst++ = *psrc++;
        i--;
    }

    verifyFlash_p = (u32 (*)(u8 *, vu8 *, u32))((u8 *)verifyFlashSector_Core_Work + 1);

    tgt = FLASH_BASE + (sectorNum << gFlash->sector.shift);

    result = verifyFlash_p(src, tgt, n);
    return result;
}

u32 ProgramFlashSectorAndVerify(u16 sectorNum, u8 *src)
{
    u8 retry;
    u32 result;

    for (retry = 0; retry < 3; retry++)
    {
        result = ProgramFlashSector(sectorNum, src);
        if (result != 0)
            continue;

        result = VerifyFlashSector(sectorNum, src);
        if (result == 0)
            break;
    }

    return result;
}

u32 ProgramFlashSectorAndVerifyNBytes(u16 sectorNum, u8 *src, u32 n)
{
    u8 retry;
    u32 result;

    for (retry = 0; retry < 3; retry++)
    {
        result = ProgramFlashSector(sectorNum, src);
        if (result != 0)
            continue;

        result = VerifyFlashSectorNBytes(sectorNum, src, n);
        if (result == 0)
            break;
    }

    return result;
}
