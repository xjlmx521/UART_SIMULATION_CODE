#include <stdarg.h>
#include "mesh_general.h"
#include "mesh_messaging.h"
#include "log.h"

#define			HEX_OUTPUT			16
#define			DECIMAL_OUTPUT		10
#define			OCTAL_OUTPUT		8

#define HexToAscii(hex) (uint8_t)( ((hex) & 0x0F) + ((((hex) & 0x0F) <= 9) ? '0' : ('A'-10)) )

uint32_t mesh_log_mask = MESH_LOG_APPLICATION;//MESH_LOG_TRANSPORT;//0xffffffff;// 0xfffffff0;

#define PTR_MASK			0x1ff
static uint8_t printf_buffer[512];
static uint16_t	printf_w_ptr = 0;
static uint16_t	printf_r_ptr = 0;

static const char prefix[] = "layer&level:	";
static const char infix[] = "	";
static const char changeLine[]="\r\n";
static int puts(char *s){
	while((*s != '\0')){
		printf_buffer[printf_w_ptr++ & PTR_MASK] = *s++;
	}
}

static int putchar(char c){
	printf_buffer[printf_w_ptr++ & PTR_MASK] = c;
}

static void puti(int num, int base){
	char re[]="0123456789ABCDEF";

	char buf[50];

	char *addr = &buf[49];

	*addr = '\0';

	do{
		*--addr = re[num%base];
		num/=base;
	}while(num!=0);

	puts(addr);
}


void log_send(uint16_t flag, mesh_log_level_e level, char *str,...){
	char span;
	long j;
	char *s;
	puts((char *)prefix);
	//Add flag info
	puti(flag,DECIMAL_OUTPUT);
	puts((char *)infix);
	//Add level info
	puti(level,DECIMAL_OUTPUT);
	puts((char *)infix);
	//char *msg;
	va_list arg_ptr;
	va_start(arg_ptr, str);

	while((span = *(str++))){
		if(span != '%'){
			putchar(span);
		}else{
			span = *(str++);
			if(span == 'c'){
				j = va_arg(arg_ptr,int);//get value of char
				putchar(j);
			}else if(span == 'd'){
				j = va_arg(arg_ptr,int);//get value of char
				if(j<0){
					putchar('-');
					j = -j;
				}
				puti(j,DECIMAL_OUTPUT);
			}else if(span == 's'){
				s = va_arg(arg_ptr,char *);//get string value
				puts(s);
			}else if(span == 'o'){
				j = va_arg(arg_ptr,unsigned int);//get octal value
				puti(j,OCTAL_OUTPUT);
			}else if(span == 'x'){
					j = va_arg(arg_ptr,unsigned int);//get hex value
					puti(j,HEX_OUTPUT);
			}else if(span == 0){
				break;
			}else{
				putchar(span);
			}
		}

	}
	va_end(arg_ptr);
	Mesh_SetEvent(gLogt_Task_c);
}

void log_write_hex(uint8_t *ptr, uint16_t len){
	uint16_t tl = 0;
	char re[]="0123456789ABCDEF";
	char buf[50];
	while(tl < len){
		char *addr = &buf[49];
		*addr = '\0';
		int num = ptr[tl++];
		do{
			*--addr = re[num%HEX_OUTPUT];
			num/=HEX_OUTPUT;
		}while(num!=0);
		puts(addr);
	}
	puts((char *)changeLine);
}

WEAK void app_send_debug_byte(uint8_t ch);

void log_task(void *arg){
	while(printf_w_ptr != printf_r_ptr){
		app_send_debug_byte(printf_buffer[printf_r_ptr++ & PTR_MASK]);
	}
}
