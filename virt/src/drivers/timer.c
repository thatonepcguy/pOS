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

