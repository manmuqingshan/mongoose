/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FLASH_CONFIG__
#define __FLASH_CONFIG__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_common.h"

/*! @name Driver version */
/*@{*/
/*! @brief FLASH_CONFIG driver version 2.0.0. */
#define FSL_FLASH_CONFIG_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*******************************************************************************
 * Definition
 ******************************************************************************/

/* FLEXSPI memory config block related defintions */
#define FC_BLOCK_TAG     (0x42464346)
#define FC_BLOCK_VERSION (0x00000000)

#define FC_CMD_SDR        0x01
#define FC_CMD_DDR        0x21
#define FC_RADDR_SDR      0x02
#define FC_RADDR_DDR      0x22
#define FC_CADDR_SDR      0x03
#define FC_CADDR_DDR      0x23
#define FC_MODE1_SDR      0x04
#define FC_MODE1_DDR      0x24
#define FC_MODE2_SDR      0x05
#define FC_MODE2_DDR      0x25
#define FC_MODE4_SDR      0x06
#define FC_MODE4_DDR      0x26
#define FC_MODE8_SDR      0x07
#define FC_MODE8_DDR      0x27
#define FC_WRITE_SDR      0x08
#define FC_WRITE_DDR      0x28
#define FC_READ_SDR       0x09
#define FC_READ_DDR       0x29
#define FC_LEARN_SDR      0x0A
#define FC_LEARN_DDR      0x2A
#define FC_DATSZ_SDR      0x0B
#define FC_DATSZ_DDR      0x2B
#define FC_DUMMY_SDR      0x0C
#define FC_DUMMY_DDR      0x2C
#define FC_DUMMY_RWDS_SDR 0x0D
#define FC_DUMMY_RWDS_DDR 0x2D
#define FC_JMP_ON_CS      0x1F
#define FC_STOP_EXE       0

#define FC_FLEXSPI_1PAD 0
#define FC_FLEXSPI_2PAD 1
#define FC_FLEXSPI_4PAD 2
#define FC_FLEXSPI_8PAD 3

#define FC_FLEXSPI_LUT_SEQ(cmd0, pad0, op0, cmd1, pad1, op1)                                                           \
    (FLEXSPI_LUT_OPERAND0(op0) | FLEXSPI_LUT_NUM_PADS0(pad0) | FLEXSPI_LUT_OPCODE0(cmd0) | FLEXSPI_LUT_OPERAND1(op1) | \
     FLEXSPI_LUT_NUM_PADS1(pad1) | FLEXSPI_LUT_OPCODE1(cmd1))

/* !@brief Data pad used in Read command */
enum
{
    kSerialFlash_1Pads = 1,
    kSerialFlash_2Pads = 2,
    kSerialFlash_4Pads = 4,
    kSerialFlash_8Pads = 8,
};

/* !@brief FLEXSPI clock configuration - In High speed boot mode mode */
enum
{
    kFlexSpiSerialClk_30MHz  = 1,
    kFlexSpiSerialClk_50MHz  = 2,
    kFlexSpiSerialClk_60MHz  = 3,
    kFlexSpiSerialClk_80MHz  = 4,
    kFlexSpiSerialClk_100MHz = 5,
    kFlexSpiSerialClk_120MHz = 6,
    kFlexSpiSerialClk_133MHz = 7,
    kFlexSpiSerialClk_166MHz = 8,
    kFlexSpiSerialClk_200MHz = 9,
};

/* !@brief FLEXSPI clock configuration - In Normal boot SDR mode */
enum
{
    kFlexSpiSerialClk_SDR_24MHz = 1,
    kFlexSpiSerialClk_SDR_48MHz = 2,
};

/* !@brief FLEXSPI clock configuration - In Normal boot DDR mode */
enum
{
    kFlexSpiSerialClk_DDR_48MHz = 1,
};

/* !@brief Misc feature bit definitions */
enum
{
    kFlexSpiMiscOffset_DiffClkEnable         = 0, /* !< Bit for Differential clock enable */
    kFlexSpiMiscOffset_WordAddressableEnable = 3, /* !< Bit for Word Addressable enable */
    kFlexSpiMiscOffset_SafeConfigFreqEnable  = 4, /* !< Bit for Safe Configuration Frequency enable */
    kFlexSpiMiscOffset_DdrModeEnable         = 6, /* !< Bit for DDR clock confiuration indication. */
};

/* !@brief Flash Configuration Command Type */
enum
{
    kDeviceConfigCmdType_Generic,    /* !< Generic command, for example: configure dummy cycles, drive strength, etc */
    kDeviceConfigCmdType_QuadEnable, /* !< Quad Enable command */
    kDeviceConfigCmdType_Spi2Xpi,    /* !< Switch from SPI to DPI/QPI/OPI mode */
    kDeviceConfigCmdType_Xpi2Spi,    /* !< Switch from DPI/QPI/OPI to SPI mode */
    kDeviceConfigCmdType_Spi2NoCmd,  /* !< Switch to 0-4-4/0-8-8 mode */
    kDeviceConfigCmdType_Reset,      /* !< Reset device command */
};

typedef struct _fc_flexspi_dll_time
{
    uint8_t time_100ps;  /* !< Data valid time, in terms of 100ps */
    uint8_t delay_cells; /* !< Data valid time, in terms of delay cells */
} fc_flexspi_dll_time_t;

/* !@brief FlexSPI LUT Sequence structure */
typedef struct _fc_flexspi_lut_seq
{
    uint8_t seqNum; /* !< Sequence Number, valid number: 1-16 */
    uint8_t seqId;  /* !< Sequence Index, valid number: 0-15 */
    uint16_t reserved;
} fc_flexspi_lut_seq_t;

/* !@brief FlexSPI Memory Configuration Block */
typedef struct _fc_flexspi_mem_config
{
    uint32_t tag;       /* !< [0x000-0x003] Tag, fixed value 0x42464346UL */
    uint32_t version;   /* !< [0x004-0x007] Version,[31:24] -'V', [23:16] - Major, [15:8] - Minor, [7:0] - bugfix */
    uint32_t reserved0; /* !< [0x008-0x00b] Reserved for future use */
    uint8_t readSampleClkSrc;    /* !< [0x00c-0x00c] Read Sample Clock Source, valid value: 0/1/3 */
    uint8_t csHoldTime;          /* !< [0x00d-0x00d] CS hold time, default value: 3 */
    uint8_t csSetupTime;         /* !< [0x00e-0x00e] CS setup time, default value: 3 */
    uint8_t columnAddressWidth;  /* !< [0x00f-0x00f] Column Address with, for HyperBus protocol, it is fixed to 3, For
       Serial NAND, need to refer to datasheet */
    uint8_t deviceModeCfgEnable; /* !< [0x010-0x010] Device Mode Configure enable flag, 1 - Enable, 0 - Disable */
    uint8_t deviceModeType; /* !< [0x011-0x011] Specify the configuration command type:Quad Enable, DPI/QPI/OPI switch,
     Generic configuration, etc. */
    uint16_t waitTimeCfgCommands; /* !< [0x012-0x013] Wait time for all configuration commands, unit: 100us, Used for
     DPI/QPI/OPI switch or reset command */
    fc_flexspi_lut_seq_t deviceModeSeq; /* !< [0x014-0x017] Device mode sequence info, [7:0] - LUT sequence id, [15:8] -
     LUt sequence number, [31:16] Reserved */
    uint32_t deviceModeArg;             /* !< [0x018-0x01b] Argument/Parameter for device configuration */
    uint8_t configCmdEnable;            /* !< [0x01c-0x01c] Configure command Enable Flag, 1 - Enable, 0 - Disable */
    uint8_t configModeType[3];          /* !< [0x01d-0x01f] Configure Mode Type, similar as deviceModeTpe */
    fc_flexspi_lut_seq_t configCmdSeqs[3]; /* !< [0x020-0x02b] Sequence info for Device Configuration command, similar
                                           as deviceModeSeq */
    uint32_t reserved1;                    /* !< [0x02c-0x02f] Reserved for future use */
    uint32_t configCmdArgs[3];             /* !< [0x030-0x03b] Arguments/Parameters for device Configuration commands */
    uint32_t reserved2;                    /* !< [0x03c-0x03f] Reserved for future use */
    uint32_t controllerMiscOption; /* !< [0x040-0x043] Controller Misc Options, see Misc feature bit definitions for
      more details */
    uint8_t deviceType;            /* !< [0x044-0x044] Device Type:  See Flash Type Definition for more details */
    uint8_t sflashPadType; /* !< [0x045-0x045] Serial Flash Pad Type: 1 - Single, 2 - Dual, 4 - Quad, 8 - Octal */
    uint8_t serialClkFreq; /* !< [0x046-0x046] Serial Flash Frequencey, device specific definitions, See System Boot
     Chapter for more details */
    uint8_t lutCustomSeqEnable; /* !< [0x047-0x047] LUT customization Enable, it is required if the program/erase cannot
     be done using 1 LUT sequence, currently, only applicable to HyperFLASH */
    uint32_t reserved3[2];      /* !< [0x048-0x04f] Reserved for future use */
    uint32_t sflashA1Size;      /* !< [0x050-0x053] Size of Flash connected to A1 */
    uint32_t sflashA2Size;      /* !< [0x054-0x057] Size of Flash connected to A2 */
    uint32_t sflashB1Size;      /* !< [0x058-0x05b] Size of Flash connected to B1 */
    uint32_t sflashB2Size;      /* !< [0x05c-0x05f] Size of Flash connected to B2 */
    uint32_t csPadSettingOverride;          /* !< [0x060-0x063] CS pad setting override value */
    uint32_t sclkPadSettingOverride;        /* !< [0x064-0x067] SCK pad setting override value */
    uint32_t dataPadSettingOverride;        /* !< [0x068-0x06b] data pad setting override value */
    uint32_t dqsPadSettingOverride;         /* !< [0x06c-0x06f] DQS pad setting override value */
    uint32_t timeoutInMs;                   /* !< [0x070-0x073] Timeout threshold for read status command */
    uint32_t commandInterval;               /* !< [0x074-0x077] CS deselect interval between two commands */
    fc_flexspi_dll_time_t dataValidTime[2]; /* !< [0x078-0x07b] CLK edge to data valid time for PORT A and PORT B */
    uint16_t busyOffset;                    /* !< [0x07c-0x07d] Busy offset, valid value: 0-31 */
    uint16_t busyBitPolarity; /* !< [0x07e-0x07f] Busy flag polarity, 0 - busy flag is 1 when flash device is busy, 1 -
     busy flag is 0 when flash device is busy */
    uint32_t lookupTable[64]; /* !< [0x080-0x17f] Lookup table holds Flash command sequences */
    fc_flexspi_lut_seq_t lutCustomSeq[12]; /* !< [0x180-0x1af] Customizable LUT Sequences */
    uint32_t reserved4[4];                 /* !< [0x1b0-0x1bf] Reserved for future use */
} fc_flexspi_mem_config_t;
/*
 *  Serial NOR configuration block
 */
typedef struct _fc_flexspi_nor_config
{
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
    uint8_t padding[0x400];            /* !< Padding for MDK and IAR */
#endif
    fc_flexspi_mem_config_t memConfig; /* !< Common memory configuration info via FlexSPI */
    uint32_t pageSize;                 /* !< Page size of Serial NOR */
    uint32_t sectorSize;               /* !< Sector size of Serial NOR */
    uint8_t ipcmdSerialClkFreq;        /* !< Clock frequency for IP command */
    uint8_t isUniformBlockSize;        /* !< Sector/Block size is the same */
    uint8_t isDataOrderSwapped;        /* !< Data order (D0, D1, D2, D3) is swapped (D1,D0, D3, D2) */
    uint8_t reserved0[1];              /* !< Reserved for future use */
    uint8_t serialNorType;             /* !< Serial NOR Flash type: 0/1/2/3 */
    uint8_t needExitNoCmdMode;         /* !< Need to exit NoCmd mode before other IP command */
    uint8_t halfClkForNonReadCmd;      /* !< Half the Serial Clock for non-read command: true/false */
    uint8_t needRestoreNoCmdMode;      /* !< Need to Restore NoCmd mode after IP commmand execution */
    uint32_t blockSize;                /* !< Block size */
    uint32_t flashStateCtx;            /* !< Flash State Context */
    uint32_t reserve2[10];             /* !< Reserved for future use */
    uint32_t fcb_fill[0x280];          /* !< Fill */
} fc_flexspi_nor_config_t;
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#endif /* __FLASH_CONFIG__ */
