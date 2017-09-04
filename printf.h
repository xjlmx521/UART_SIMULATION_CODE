#pragma once

void my_array_printf(char*data, int len);
int Tl_printf(const char *format, ...);
#if (UART_PRINTF_MODE)

#define printf			Tl_printf
#define	printfArray		arrayPrint
#define	logPrint		Tl_printf
#define	logPrintArray	arrayPrint
#define	arrayPrint(arrayAddr,len)					\
{													\
	Tl_printf("\n*********************************\n");		\
	unsigned char	i = 0;							\
	do{												\
		Tl_printf(" %x",((unsigned char *)arrayAddr)[i++]);						\
	}while(i<len);										\
	Tl_printf("\n*********************************\n");		\
}

#define	DEBUG(compileFlag,...)						\
		do{											\
			if(compileFlag) Tl_printf(__VA_ARGS__);					\
		}while(0)
#else
#define printf
#define	printfArray
#define	DEBUG(compileFlag,...)
#endif

#if (FLASH_PRINTF_MODE)

#define quick_printf ftl_write
#else
#define quick_printf
#endif

