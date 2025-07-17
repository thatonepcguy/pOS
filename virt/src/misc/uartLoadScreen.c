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
    kprintf("\x1B[%d;%dH", TERM_HEIGHT/2, TERM_WIDTH/2-2);
    uartPuts("[pOS]");
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