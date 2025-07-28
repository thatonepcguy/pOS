/*
    * raspix is a custom OS designed to function on the Raspberry Pi 5.
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

#define SCTLR_EL1_TIDCP         (1ULL<<63)
#define SCTLR_EL1_SPINTMASK     (1ULL<<62)
#define SCTLR_EL1_NMI           (1ULL<<61)
#define SCTLR_EL1_EnTP2         (1ULL<<60)
#define SCTLR_EL1_TCSO          (1ULL<<59)
#define SCTLR_EL1_TCSO0         (1ULL<<58)
#define SCTLR_EL1_EPAN          (1ULL<<57)
#define SCTLR_EL1_EnALS         (1ULL<<56)
#define SCTLR_EL1_EnAS0         (1ULL<<55)
#define SCTLR_EL1_EnASR         (1ULL<<54)
#define SCTLR_EL1_TME           (1ULL<<53)
#define SCTLR_EL1_TME0          (1ULL<<52)
#define SCTLR_EL1_TMT           (1ULL<<51)
#define SCTLR_EL1_TMT0          (1ULL<<50)
#define SCTLR_EL1_TWEDEn        (1ULL<<45)
#define SCTLR_EL1_DSSBS         (1ULL<<44)
#define SCTLR_EL1_ATA           (1ULL<<43)
#define SCTLR_EL1_ATA0          (1ULL<<42)
#define SCTLR_EL1_ITFSB         (1ULL<<37)
#define SCTLR_EL1_BT1           (1ULL<<36)
#define SCTLR_EL1_BT0           (1ULL<<35)
#define SCTLR_EL1_EnFPM         (1ULL<<34)
#define SCTLR_EL1_MSCEn         (1ULL<<33)
#define SCTLR_EL1_CMOW          (1ULL<<32)
#define SCTLR_EL1_EnIA          (1ULL<<31)
#define SCTLR_EL1_EnIB          (1ULL<<30)
#define SCTLR_EL1_LSMAOE        (1ULL<29)
#define SCTLR_EL1_nTLSMD        (1ULL<<28)
#define SCTLR_EL1_EnDA          (1ULL<<27)
#define SCTLR_EL1_UCI           (1ULL<<26)
#define SCTLR_EL1_EE            (1ULL<<25)
#define SCTLR_EL1_E0E           (1ULL<<24)
#define SCTLR_EL1_SPAN          (1ULL<<23)
#define SCTLR_EL1_EIS           (1ULL<<22)
#define SCTLR_EL1_IESB          (1ULL<<21)
#define SCTLR_EL1_TSCXT         (1ULL<<20)
#define SCTLR_EL1_WXN           (1ULL<<19)
#define SCTLR_EL1_nTWE          (1ULL<<18)
#define SCTLR_EL1_nTWI          (1ULL<<16)
#define SCTLR_EL1_UCT           (1ULL<<15)
#define SCTLR_EL1_DZE           (1ULL<<14)
#define SCTLR_EL1_EnDB          (1ULL<<13)
#define SCTLR_EL1_I             (1ULL<<12)
#define SCTLR_EL1_EOS           (1ULL<<11)
#define SCTLR_EL1_EnRCTX        (1ULL<<10)
#define SCTLR_EL1_UMA           (1ULL<<9)
#define SCTLR_EL1_SED           (1ULL<<8)
#define SCTLR_EL1_ITD           (1ULL<<7)
#define SCTLR_EL1_nAA           (1ULL<<6)
#define SCTLR_EL1_CP15BEN       (1ULL<<5)
#define SCTLR_EL1_SA0           (1ULL<<4)
#define SCTLR_EL1_SA            (1ULL<<3)
#define SCTLR_EL1_C             (1ULL<<2)
#define SCTLR_EL1_A             (1ULL<<1)
#define SCTLR_EL1_M             (1ULL<<0)

#define SCTLR_EL1_TWEDEL        (0ULL<<46) // trap delay
#define SCTLR_EL1_TCF           (0b01ULL<<40) // sync exception
#define SCTLR_EL1_TCF0          (0b01ULL<<38) // sync exception)