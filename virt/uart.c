#include "uart.h"
#include "common.h"
#include "mmio.h"

void txReady(void) {
    while ((mmioRead(UART0_FR)&UART0_FR_BUSY) != 0);
}

void uartPutc(const char c) {
    // wait for tx
    txReady();
    mmioWrite(UART0_DR, c);
}

void uartPuts(const char *c) {
    while (*c != '\0') {
        txReady();
        mmioWrite(UART0_DR, *c);
        c++;
    }
}

int uartGetc() {
    if ((mmioRead(UART0_FR)&UART0_FR_RXFE))
        return -1;

    return mmioRead(UART0_DR) & 0xFF;
}

void uartInit(void) {
    uint32_t read;
    
    // Disable UART
    mmioWrite(UART0_CR, 0x0U);
    dsb();

    txReady();

    mmioWrite(UART0_IBRD, 0x1AU); // 115200 baud
    mmioWrite(UART0_FBRD, 0x3U); 
    
    read = mmioRead(UART0_LCR_H);
    read &= ~(UART0_LCR_H_WLEN8 | UART0_LCR_H_FEN);
    read |= UART0_LCR_H_WLEN8;
    dsb();
    mmioWrite(UART0_LCR_H, read);

    // mask interrups
    mmioWrite(UART0_IMSC, 0x7ff);

    // disable dma
    mmioWrite(UART0_DMACR, 0x0);

    mmioWrite(UART0_CR, 0x301U);
    uartPutc('\r');

}