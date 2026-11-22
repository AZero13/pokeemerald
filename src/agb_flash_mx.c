#include "gba/gba.h"
#include "gba/flash_internal.h"

const u16 mxMaxTime[][3] =
{
    { 10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK },
    { 10, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK },
    { 2000, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK },
    { 2000, 65469, TIMER_ENABLE | TIMER_INTR_ENABLE | TIMER_256CLK },
};

const struct FlashSetupInfo MX29L010 =
{
    ProgramFlashByte_MX,
    ProgramFlashSector_MX,
    EraseFlashChip_MX,
    EraseFlashSector_MX,
    WaitForFlashWrite_Common,
    mxMaxTime,
    {
        131072, // ROM size
        {
            4096, // sector size
              12, // bit shift to multiply by sector size (4096 == 1 << 12)
              32, // number of sectors
               0  // appears to be unused
        },
        { 3, 1 }, // wait state setup data
        { { 0xC2, 0x09 } } // ID
    }
};

const struct FlashSetupInfo DefaultFlash =
{
    ProgramFlashByte_MX,
    ProgramFlashSector_MX,
    EraseFlashChip_MX,
    EraseFlashSector_MX,
    WaitForFlashWrite_Common,
    mxMaxTime,
    {
        131072, // ROM size
        {
            4096, // sector size
              12, // bit shift to multiply by sector size (4096 == 1 << 12)
              32, // number of sectors
               0  // appears to be unused
        },
        { 3, 1 }, // wait state setup data
        { { 0x00, 0x00 } } // ID of 0
    }
};

u16 EraseFlashChip_MX(void)
{
    u16 readFuncBuff[0x20];
    u16 result;

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | gFlash->wait[0];

    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0x80);
    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0x10);

    SetReadFlash1(readFuncBuff);

    result = WaitForFlashWrite(3, FLASH_BASE, 0xFF);

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | WAITCNT_SRAM_8;

    return result;
}

u16 EraseFlashSector_MX(u16 sectorNum)
{
    UNUSED u32 i;
    u8 *adr;
    u16 readFuncBuff[0x20];
    u16 result;
    u16 retry;

    if (sectorNum >= gFlash->sector.count)
        return 0x80FF;

    SwitchFlashBank(sectorNum / SECTORS_PER_BANK);
    sectorNum %= SECTORS_PER_BANK;

    retry = 0;

try_erase:
    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | gFlash->wait[0];

    adr = FLASH_BASE + (sectorNum << gFlash->sector.shift);

    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0x80);
    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    *adr = 0x30;

    SetReadFlash1(readFuncBuff);

    result = WaitForFlashWrite(2, adr, 0xFF);

    if ((result & 0xA000) && retry <= 3)
    {
        retry++;
        goto try_erase;
    }

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | WAITCNT_SRAM_8;

    return result;
}

u16 ProgramFlashByte_MX(u16 sectorNum, u32 offset, u8 data)
{
    u8 *dst;
    u16 readFuncBuff[0x20];

    if (offset >= gFlash->sector.size)
        return 0x8000;

    SwitchFlashBank(sectorNum / SECTORS_PER_BANK);
    sectorNum %= SECTORS_PER_BANK;

    dst = FLASH_BASE + (sectorNum << gFlash->sector.shift) + offset;

    SetReadFlash1(readFuncBuff);

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | gFlash->wait[0];

    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0xA0);
    *dst = data;

    return WaitForFlashWrite(1, dst, data);
}

static u16 ProgramByte(u8 *src, u8 *dest)
{
    FLASH_WRITE(0x5555, 0xAA);
    FLASH_WRITE(0x2AAA, 0x55);
    FLASH_WRITE(0x5555, 0xA0);
    *dest = *src;

    return WaitForFlashWrite(1, dest, *src);
}

u16 ProgramFlashSector_MX(u16 sectorNum, u8 *src)
{
    u8 *tgt;
    u16 result;
    u16 readFuncBuff[0x20];

    if (sectorNum >= gFlash->sector.count)
        return 0x80FF;

    result = EraseFlashSector_MX(sectorNum);

    if (result != 0)
        return result;

    SwitchFlashBank(sectorNum / SECTORS_PER_BANK);
    sectorNum %= SECTORS_PER_BANK;

    SetReadFlash1(readFuncBuff);

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | gFlash->wait[0];

    gFlashNumRemainingBytes = gFlash->sector.size;
    tgt = FLASH_BASE + (sectorNum << gFlash->sector.shift);

    while (gFlashNumRemainingBytes > 0)
    {
        result = ProgramByte(src, tgt);

        if (result != 0)
            break;

        gFlashNumRemainingBytes--;
        src++;
        tgt++;
    }

    return result;
}
