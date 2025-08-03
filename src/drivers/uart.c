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

#include "drivers/uart.h"
#include "drivers/gpio.h"
#include "utils/common.h"
#include "drivers/mmio.h"

void txReady(void) {
    while ((mmioRead(UART0_FR) & UART0_FR_TXFF) != 0);
}

void uartPutc(const char c) {
    // wait for tx
    txReady();
    mmioWrite(UART0_DR, c);
}

void uartPuts(const char *c) {
    while (*c != '\0') {
        uartPutc(*c);
        c++;
    }
}

int uartGetc() {
    if ((mmioRead(UART0_FR)&UART0_FR_RXFE))
        return -1;

    return mmioRead(UART0_DR) & 0xFF;
}

void uartInit(void) {
    uint32_t read = mmioRead(GPFSEL1);
	read &= ~(7<<12);                   
	read |= 4<<12;                      // set alt0 for gpio14
	read &= ~(7<<15);                   
	read |= 4<<15;                      // set alt0 for gpio 15
	mmioWrite(GPFSEL1, read);

    
    // Disable UART
    mmioWrite(UART0_CR, 0x0U);

    mmioWrite(UART0_IBRD, 1250); // 2400 baud
    mmioWrite(UART0_FBRD, 0); 
    
    read = mmioRead(UART0_LCR_H);
    read &= ~(UART0_LCR_H_WLEN8 | UART0_LCR_H_FEN);
    read |= UART0_LCR_H_WLEN8 | UART0_LCR_H_FEN;
    mmioWrite(UART0_LCR_H, read);

    // mask interrups
    mmioWrite(UART0_IMSC, 0x7ff);

    // disable dma
    mmioWrite(UART0_DMACR, 0x0);

    mmioWrite(UART0_CR, 0x301U);

}