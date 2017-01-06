#ifndef __epolling_H__
#define __epolling_H__

#include <sys/epoll.h>
#include <stdint.h>

#define MAX_EVENT_DESCRIPTION_SIZE 128
#define MAX_EVENT_NUM 32
typedef void (* deviceEventHandler)(int ,void *);

typedef struct _tDeviceEvent
{
	int fd_int;
	bool use_bool;
	uint32_t event_type_uint32;
	void *pdata_pvoid;
	deviceEventHandler  event_handler;
	char description_achar[MAX_EVENT_DESCRIPTION_SIZE];
}tDeviceEvent;



bool 
epollAddEventByFd(int fd_int, short event_short);
bool 
epollAddEvent(
	int device_evnet_pstruct, 
	uint32_t event_short);

bool 
epollDelEvent (int fd_int);





#define eEvent_Error_DeviceEvent_struct_FULL -1
bool 
undefineDeviceEvent(int index_int);

int 
defineDeviceEvent(
	int fd_int,
	uint32_t event_type_uint32,
	void  *pdata_pvoid,
	deviceEventHandler event_handler,
	char *description_pchar);


void epollProcessActivity(void);
bool setEpollProcessStop( void );
bool setEpollProcessStart( void );
bool initialEpollDeviceEvent();

#define EVENT_TYPE_NULL			0x00000000
#define EVENT_TYPE_TIMER	 		0x00000001
#define EVENT_TYPE_READ_WRITE 	0x00000002

#endif

