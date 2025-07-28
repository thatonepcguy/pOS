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

#include "utils/common.h"
#include "drivers/timer.h"

void initTimer(bool enable, bool intMask) {
    sysRegWrite(CNTP_CTL_EL0, enable|(intMask<<1));
}

void usleep(uint64_t uSec) {
    uint64_t timerFrq = sysRegRead(CNTFRQ_EL0);
    if (timerFrq < 10000000 && uSec < 10) 
        return;
    else if (timerFrq < 1000000) {
        uSec /= (1000000/timerFrq);
    } else if (timerFrq > 1000000) {
        uSec *= (timerFrq/1000000);
    }
    sysRegWrite(CNTP_TVAL_EL0, uSec);
    while(!(sysRegRead(CNTP_CTL_EL0)>>2));
}

