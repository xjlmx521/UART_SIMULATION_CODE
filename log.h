#ifndef _LOG_H_
#define	_LOG_H_

extern uint32_t mesh_log_mask;


typedef enum{
	MESH_LOG_LEVEL_INFO,
	MESH_LOG_LEVEL_DEBUG,
	MESH_LOG_LEVEL_CRITICAL,
	MESH_LOG_LEVEL_WARNING,
	MESH_LOG_LEVEL_ERROR
}mesh_log_level_e;


#define	MESH_LOG_BEARER				(1UL<<0)
#define	MESH_LOG_PROXY				(1UL<<1)
#define MESH_LOG_PROV				(1UL<<2)
#define MESH_LOG_SECURITY			(1UL<<3)
#define	MESH_LOG_NWK				(1UL<<4)
#define MESH_LOG_TRANSPORT			(1UL<<5)
#define MESH_LOG_ACCESS				(1UL<<6)
#define MESH_LOG_CONFIG_SERVER		(1UL<<7)
#define MESH_LOG_COMMON				(1UL<<8)
#define MESH_LOG_MESSAGING			(1UL<<9)
#define MESH_LOG_MEMORY				(1UL<<10)
#define MESH_LOG_APPLICATION		(1UL<<11)

void log_send(uint16_t flag, mesh_log_level_e level, char *str,...);

#define MESH_LOG_HEX(dst,len)	log_write_hex(dst,len)
#define	MESH_LOG(debug_flag,level,...)				\
	if(mesh_log_mask & debug_flag){						\
		log_send(debug_flag,level,__VA_ARGS__);						\
	}													
#endif
