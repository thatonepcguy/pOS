/*
    * raspix is a custom OS designed to function on the Raspberry Pi 4b.
    * Copyright (C) 2025  Caleb A. Jacka
    *  
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    * 
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <https://www.gnu.org/licenses/>.
    * 
    * If contact with the original author is needed, he is available via email at 
    * calebjacka@gmail.com
*/

#pragma once

#include "utils/common.h"

#define SD_CMDTM_CMD_TYPE_NORMAL          (0b00 << 22)
#define SD_CMDTM_CMD_TYPE_SUSPEND         (0b01 << 22)
#define SD_CMDTM_CMD_TYPE_RESUME          (0b10 << 22)
#define SD_CMDTM_CMD_TYPE_ABORT           (0b11 << 22)

#define SD_CMDTM_CMD_ISDATA               (1U<<21)
#define SD_CMDTM_IXCHK_EN                 (1U<<20)
#define SD_CMDTM_CMD_CRCCHK               (1U<<19)

#define SD_CMDTM_CMD_RSPNS_TYPE_NONE      (0b00<<16)
#define SD_CMDTM_CMD_RSPNS_TYPE_136       (0b01<<16)
#define SD_CMDTM_CMD_RSPNS_TYPE_48        (0b10<<16)
#define SD_CMDTM_CMD_RSPNS_TYPE_48_BUSY   (0b11<<16)

#define SD_CMDTM_TM_MULTI_BLOCK           (1U<<5)
#define SD_CMDTM_TM_DAT_DIR               (1U<<4)

#define SD_CMDTM_TM_AUTO_CMD_EN_NONE      (0b00<<2)
#define SD_CMDTM_TM_AUTO_CMD_EN_CMD12     (0b01<<2)
#define SD_CMDTM_TM_AUTO_CMD_EN_CMD23     (0b10<<2)

#define SD_CMDTM_TM_BLKCNT_EN             (1U<<1)