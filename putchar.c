/*******************************************************************************************************************
 * @brief	UART simulation interface
 * @author	junjun.xu@telink-semi.com (All this owned by Telink-Semiconductor)
 */

#include "putchar.h"
#include "../tl_common.h"


#ifndef		BIT_INTERVAL
#define	BIT_INTERVAL	 (32000000/2000000)
#endif

_attribute_ram_code_ int uart_putc(char byte) {
#if UART_PRINTF_MODE
	u8 j = 0;
	u32 t1 = 0, t2 = 0;
	u32 pcTxReg = (0x800583 + ((DEBUG_INFO_TX_PIN >> 8) << 3));; //register GPIO output
	u8 tmp_bit0 = read_reg8(pcTxReg) & (~(DEBUG_INFO_TX_PIN & 0xff));
	u8 tmp_bit1 = read_reg8(pcTxReg) | (DEBUG_INFO_TX_PIN & 0xff);

	u8 bit[10] = {0};
	bit[0] = tmp_bit0;
	bit[1] = (byte & 0x01) ? tmp_bit1 : tmp_bit0;
	bit[2] = ((byte >> 1) & 0x01) ? tmp_bit1 : tmp_bit0;
	bit[3] = ((byte >> 2) & 0x01) ? tmp_bit1 : tmp_bit0;
	bit[4] = ((byte >> 3) & 0x01) ? tmp_bit1 : tmp_bit0;
	bit[5] = ((byte >> 4) & 0x01) ? tmp_bit1 : tmp_bit0;
	bit[6] = ((byte >> 5) & 0x01) ? tmp_bit1 : tmp_bit0;
	bit[7] = ((byte >> 6) & 0x01) ? tmp_bit1 : tmp_bit0;
	bit[8] = ((byte >> 7) & 0x01) ? tmp_bit1 : tmp_bit0;
	bit[9] = tmp_bit1;
	//u8 r = irq_disable();// enable this may disturb time sequence, but if disable unrecognizable code will show
	t1 = reg_system_tick;
	for(j = 0; j < 10; j++) {
		t2 = t1;

		while(t1 - t2 < BIT_INTERVAL) {
			t1  = reg_system_tick;
		}

		write_reg8(pcTxReg, bit[j]);       //send bit0
	}
	//irq_restore(r);
	return byte;

#else
	return -1;
#endif
}

int putchar(int c) {
#if UART_PRINTF_MODE
	return uart_putc((char)c);
#endif
}
