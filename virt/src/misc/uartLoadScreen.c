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
#include "utils/kprintf.h"
#include "misc/uartLoadScreen.h"
#include "drivers/timer.h"
#include "drivers/uart.h"

void displayBootScreen() {
    initTimer(1, 1);
    usleep(2000000);
    kprintf("\x1B[3J");
    kprintf("\x1B[?25l");

    int topRow = 1;
    int bottomRow = 0;

    char shades[4][4] = {"▓", "▒", "░", "\xE2\x80\x83"};
    char loading[6][4] = {"⠋", "⠇", "⠦", "⠴", "⠸", "⠙"};
    
    for (int i = 1; i <= TERM_HEIGHT/2; i++) {
        usleep(100000);
        kprintf("\x1B[%dH", topRow);
        for (int k = 1; k <= TERM_WIDTH; k++) {
            uartPuts("█");
        }
        kprintf("\x1B[%dH", TERM_HEIGHT-bottomRow);
        for (int k = 1; k <= TERM_WIDTH; k++) {
            uartPuts("█");
        }
        if (i != TERM_HEIGHT/2) {
            topRow++;
            bottomRow++;
        }
    }
    for (int j = 0; j<4; j++) {
        usleep(300000);
        for (int i = 1; i <= TERM_HEIGHT; i++) {
            kprintf("\x1B[%dH", i);
            for (int k = 1; k <= TERM_WIDTH; k++) {
                uartPuts(shades[j]);
            }
        }
    }
    kprintf("\x1B[%d;%dH", TERM_HEIGHT/2, TERM_WIDTH/2-4);
    uartPuts("[raspix]");
    int loadIdx = 0;
    for (int i = 0; i < LOAD_TIME; i++) {
        usleep(100000);
        kprintf("\x1B[%d;%dH", TERM_HEIGHT/2+5, TERM_WIDTH/2);
        uartPuts(loading[loadIdx]);
        loadIdx++;
        if (loadIdx > 5)
            loadIdx = 0;
    }

    uartPuts("\x1B[1H\x1B[J");
    uartPuts(" > ");
     kprintf("\x1B[?25h");
}