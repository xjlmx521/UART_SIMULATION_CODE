#include <stdarg.h>

#define			DECIMAL_OUTPUT		10
#define			OCTAL_OUTPUT		8
#define			HEX_OUTPUT			16


static int puts(char *s){
	while((*s != '\0')){
		putchar(*s++);
	}
}



static void puti(unsigned int num, int base){
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


int Tl_printf(const char *format, ...){

	char span;
	unsigned long j;
	char *s;
	//char *msg;
	va_list arg_ptr;
	va_start(arg_ptr, format);

	while((span = *(format++))){
		if(span != '%'){
			putchar(span);
		}else{
			span = *(format++);
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
}
