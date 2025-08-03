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

#define TCR_EL1_MTX1    (1ULL<<61)
#define TCR_EL1_MTX0    (1ULL<<60)
#define TCR_EL1_DS      (1ULL<<59)
#define TCR_EL1_TCMA1   (1ULL<<58)
#define TCR_EL1_TCMA0   (1ULL<<57)
#define TCR_EL1_E0PD1   (1ULL<<56)
#define TCR_EL1_E0PD0   (1ULL<<55)
#define TCR_EL1_NFD1    (1ULL<<54)
#define TCR_EL1_NFD0    (1ULL<<53)
#define TCR_EL1_TBID1   (1ULL<<52)
#define TCR_EL1_TBID0   (1ULL<<51)
#define TCR_EL1_HWU162  (1ULL<<50)
#define TCR_EL1_HWU161  (1ULL<<49)
#define TCR_EL1_HWU160  (1ULL<<48)
#define TCR_EL1_HWU159  (1ULL<<47)
#define TCR_EL1_HWU062  (1ULL<<46)
#define TCR_EL1_HWU061  (1ULL<<45)
#define TCR_EL1_HWU060  (1ULL<<44)
#define TCR_EL1_HWU059  (1ULL<<43)
#define TCR_EL1_HPD1    (1ULL<<42)
#define TCR_EL1_HPD0    (1ULL<<41)
#define TCR_EL1_HD      (1ULL<<40)
#define TCR_EL1_HA      (1ULL<<39)
#define TCR_EL1_TBI1    (1ULL<<38)
#define TCR_EL1_TBI0    (1ULL<<37)
#define TCR_EL1_AS      (1ULL<<36)
#define TCR_EL1_EPD1    (1ULL<<23)
#define TCR_EL1_A1      (1ULL<<22)
#define TCR_EL1_EPD0    (1ULL<<7)

#define IPS_SIZE        (0b010ULL /* 40 BITS */<<32)
#define TG1             (0b10ULL /* 4KB */ <<30)
#define SH1             (0b10ULL<<28)
#define ORGN1           (0b01ULL<<26) // normal cacheable mem
#define IRGN1           (0b01ULL<<24) // normal cacheable mem
#define T1SZ            (25ULL<<16)  // 64-25=39 bits of virtual addr = 3 levels of page table
#define TG0             (0b00ULL /* 4 KB*/ <<14)
#define SH0             (0b10ULL<<28)
#define ORGN0           (0b01ULL<<10) // normal cacheable mem
#define IRGN0           (0b01ULL<<8) // normal cacheable mem
#define T0SZ            (25ULL)   // 64-25=39 bits of virtual addr = 3 levels of page table