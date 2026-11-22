#include "gba/gba.h"
#include "gba/flash_internal.h"

static const char AgbLibFlashVersion[] = "FLASH1M_V103";

static const struct FlashSetupInfo *const sSetupInfos[] =
{
    &MX29L010,
    &LE26FV10N1TS,
    &DefaultFlash
};

u16 IdentifyFlash(void)
{
    u16 result;
    u16 flashID;
    const struct FlashSetupInfo *const *flp;

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | WAITCNT_SRAM_8;

    flashID = ReadFlashId();

    flp = sSetupInfos;
    result = 1;

    for (;;)
    {
        if ((*flp)->type.ids.separate.makerId == 0)
            break;

        if (flashID == (*flp)->type.ids.joined)
        {
            result = 0;
            break;
        }

        flp++;
    }

    ProgramFlashByte = (*flp)->programFlashByte;
    ProgramFlashSector = (*flp)->programFlashSector;
    EraseFlashChip = (*flp)->eraseFlashChip;
    EraseFlashSector = (*flp)->eraseFlashSector;
    WaitForFlashWrite = (*flp)->WaitForFlashWrite;
    gFlashMaxTime = (*flp)->maxTime;
    gFlash = &(*flp)->type;

    return result;
}

u16 WaitForFlashWrite_Common(u8 phase, u8 *addr, u8 lastData)
{
    u8 poll;
    u16 result = 0;

    StartFlashTimer(phase);

    while ((poll = PollFlashStatus(addr)) != lastData)
    {
        if (poll & 0x20)
        {
            // The write operation exceeded the flash chip's time limit.

            if (PollFlashStatus(addr) == lastData)
                break;

            FLASH_WRITE(0x5555, 0xF0);
            result = phase | 0xA000u;
            break;
        }

        if (gFlashTimeoutFlag)
        {
            if (PollFlashStatus(addr) == lastData)
                break;

            FLASH_WRITE(0x5555, 0xF0);
            result = phase | 0xC000u;
            break;
        }
    }

    StopFlashTimer();

    return result;
}
