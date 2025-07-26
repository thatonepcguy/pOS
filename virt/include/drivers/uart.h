/*
    * raspOS is a custom OS designed to function on the Raspberry Pi 5.
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

#define UART0_BASE          0x09000000
#define UART0_DR            (UART0_BASE + 0x000)
#define UART0_FR            (UART0_BASE + 0x018)
#define UART0_IBRD          (UART0_BASE + 0x024)
#define UART0_FBRD          (UART0_BASE + 0x028)
#define UART0_LCR_H         (UART0_BASE + 0x02c)
#define UART0_CR            (UART0_BASE + 0x030)
#define UART0_IMSC          (UART0_BASE + 0x038)
#define UART0_DMACR         (UART0_BASE + 0x048)

#define UART0_LCR_H_SPS     (1U<<7)
#define UART0_LCR_H_WLEN8   (3U<<5)
#define UART0_LCR_H_WLEN7   (2U<<5)
#define UART0_LCR_H_WLEN6   (1U<<5)
#define UART0_LCR_H_WLEN5   (0U<<5)
#define UART0_LCR_H_FEN     (1U<<4)
#define UART0_LCR_H_STP2    (1U<<3)
#define UART0_LCR_H_EPS     (1U<<2)
#define UART0_LCR_H_PEN     (1U<<1)
#define UART0_LCR_H_BRK     (1U<<0)

#define UART0_FR_RXFE       (1U<<4)
#define UART0_FR_TXFF       (1U<<5)
#define UART0_FR_BUSY       (1U<<3)

void txReady(void);
void uartInit(void);
void uartPutc(const char c);
void uartPuts(const char *c);
int uartGetc();