#include "spi.h"

#define CMD0     (0x40+0)     	/* GO_IDLE_STATE */
#define CMD1     (0x40+1)     	/* SEND_OP_COND */
#define CMD8     (0x40+8)     	/* SEND_IF_COND */
#define CMD9     (0x40+9)     	/* SEND_CSD */
#define CMD10    (0x40+10)    	/* SEND_CID */
#define CMD12    (0x40+12)    	/* STOP_TRANSMISSION */
#define CMD16    (0x40+16)    	/* SET_BLOCKLEN */
#define CMD17    (0x40+17)    	/* READ_SINGLE_BLOCK */
#define CMD18    (0x40+18)    	/* READ_MULTIPLE_BLOCK */
#define CMD23    (0x40+23)    	/* SET_BLOCK_COUNT */
#define CMD24    (0x40+24)    	/* WRITE_BLOCK */
#define CMD25    (0x40+25)    	/* WRITE_MULTIPLE_BLOCK */
#define CMD41    (0x40+41)    	/* SEND_OP_COND (ACMD) */
#define CMD55    (0x40+55)    	/* APP_CMD */
#define CMD58    (0x40+58)    	/* READ_OCR */

bool sd_ready()
{
    for (auto timeout = 16; timeout; --timeout)
    {
        if (spi_read_byte() == 0xff)
        {
            return true;
        }
    }
    return false;
}

uint8_t sd_command(uint8_t cmd, uint32_t arg)
{
    // chipselect_high(SpiDevice::SDcard);
    // chipselect_low(SpiDevice::SDcard);
    if (!sd_ready())
    {
        return 0xff;
    }

    uint8_t crc = 0;
    if(cmd == CMD0)
        crc = 0x95;
	else if(cmd == CMD8)
        crc = 0x87;

    // auto data = bytes{cmd, (uint8_t) (arg >> 24), (uint8_t) (arg >> 16), (uint8_t) (arg >> 8), (uint8_t) arg, crc};
    // const auto crc = crc7(data.data(), data.size() - 1);
    // data.back() = crc;
    spi_write(bytes{cmd, (uint8_t) (arg >> 24), (uint8_t) (arg >> 16), (uint8_t) (arg >> 8), (uint8_t) arg, crc});

    uint8_t r1{};
    auto retries = 16;
    do
    {
        r1 = spi_read_byte();
    } while ((r1 & 0x80) && --retries);
#if 0
    message("SD 0x%.2X CRC 0x%.2X -> 0x%.2X", cmd, crc, r1);
#endif
    return r1;
}

bool sdcard_init()
{
    spi_write(bytes{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff});
    chipselect_low(SpiDevice::SDcard);

    if (sd_command(CMD0, 0) != 1)
    {
        return false;
    }

    if (sd_command(CMD8, 0x1aa) != 1)
    {
        return false;
    }

    const auto cmd8 = spi_read<4>();
    if (cmd8[2] == 0x01 && cmd8[3] == 0xaa)
    {
        auto retries = 4096;
        do
        {
            sd_command(CMD55, 0);
            if (sd_command(CMD41, 0x40000000) == 0)
            {
                return true;
            }
        } while (retries--);
    }

    return false;
}

bool wait_for_start()
{
    uint8_t r{};
    auto retries = 16;
    do
    {
        r = spi_read_byte();
    } while ((r == 0xff) && --retries);

    if (r == 0xfe)
    {
        return true;
    }
    return false;
}

struct __attribute__((packed)) sdcard_cid
{
    uint8_t mid;
    char oid[2];
    char pnm[4];
    uint8_t prv;
    uint32_t psn;
    uint8_t _:4;
    uint16_t date:12;
    uint8_t crc7:7;
    uint8_t __:1;
};

void sdcard_get_cid()
{
    sdcard_cid cid;
    uint8_t cmd10;
    auto timeout = 8;
    do
    {
        cmd10 = sd_command(CMD10, 0);
    } while (cmd10 == 1);

    if (cmd10 == 0)
    {
        if (wait_for_start())
        {
            auto data = spi_read<18>();
            sdcard_cid *c = (sdcard_cid*)data.data();
            message("%x <%.2s> <%.4s> %x %d", c->mid, c->oid, c->pnm, c->psn, c->date);
        }
        else
        {
            message("wait_for_start timeout");
        }
    }
    else
    {
        message("CMD10 NOK: %x", cmd10);
    }
}