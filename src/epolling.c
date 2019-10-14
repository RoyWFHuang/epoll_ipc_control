
#include <sys/epoll.h>
#include <stdint.h>
#include <string.h>
#include  <fcntl.h>
#include <unistd.h>
#include <pthread.h>


#include "epolling.h"
#include "PreDefine.h"





static int __g_running_int;
tDeviceEvent __g_device_event_struct[MAX_EVENT_NUM];
struct epoll_event __g_events[MAX_EVENT_NUM];
int __g_epfd_int;


int8_t epollAddEventByFd(
	int fd_int, short event_short)
{
#if 0
	__g_events[deviceEvnetIndex_int].data.fd= fd_int;
	__g_events[deviceEvnetIndex_int].events = event_short ;


	//(EPOLLIN | EPOLLOUT)
	if(epoll_ctl (__g_epfd_int, 	EPOLL_CTL_ADD,
		fd_int,
		&__g_events[deviceEvnetIndex_int]) == -1 )
	{
		__g_events[deviceEvnetIndex_int].data.fd = -1;
		PRINT_ERR("epollAddEvent error\n");
		return FALSE;
	}
#endif

	struct epoll_event event_struct;

	event_struct.data.fd= fd_int;
	event_struct.events = event_short ;
	if(epoll_ctl (__g_epfd_int, 	EPOLL_CTL_ADD,
		fd_int,
		&event_struct) == -1 )
	{
		PRINT_ERR("epollAddEvent error\n");
		return FALSE;
	}


	return TRUE;
}

int8_t epollAddEvent(
	int device_index_int, uint32_t event_uint32)
{
#if 0
	__g_events[deviceEvnetIndex_int].data.fd= fd_int;
	__g_events[deviceEvnetIndex_int].events = event_short ;


	//(EPOLLIN | EPOLLOUT)
	if(epoll_ctl (__g_epfd_int, 	EPOLL_CTL_ADD,
		fd_int,
		&__g_events[deviceEvnetIndex_int]) == -1 )
	{
		__g_events[deviceEvnetIndex_int].data.fd = -1;
		PRINT_ERR("epollAddEvent error\n");
		return FALSE;
	}
#endif

	struct epoll_event event_struct;

	event_struct.data.ptr= &__g_device_event_struct[device_index_int];
	event_struct.events = event_uint32 ;
	if(epoll_ctl (__g_epfd_int, EPOLL_CTL_ADD,
		__g_device_event_struct[device_index_int].fd_int,
		&event_struct) == -1 )
	{
		PRINT_ERR("epollAddEvent error\n");
		return FALSE;
	}


	return TRUE;
}


int8_t epollDelEvent(int fd_int)
{
#if 0
	if(epoll_ctl (__g_epfd_int, EPOLL_CTL_DEL,
		__g_events[deviceEvnetIndex_int].data.fd,
		&__g_events[deviceEvnetIndex_int]) == -1)
		return FALSE;

	__g_events[deviceEvnetIndex_int].data.fd = -1;
#endif
	struct epoll_event event_struct;

	if(epoll_ctl (__g_epfd_int, EPOLL_CTL_DEL,fd_int, &event_struct) == -1)
		return FALSE;
	return TRUE;
}


//	ret = epoll_ctl (__g_epfd_int, EPOLL_CTL_ADD, fd, &event);
//	ret = epoll_ctl (epfd, EPOLL_CTL_MOD, fd, &event);
//	ret = epoll_ctl (epfd, EPOLL_CTL_DEL, fd, &event);

#define eEvent_Error_DeviceEvent_struct_FULL -1



int8_t undefineDeviceEvent(int fd_int)
{
	for (int index_int = 0;index_int < MAX_EVENT_NUM;index_int++)
	{
		if(__g_device_event_struct[index_int].fd_int == fd_int)
		{
			__g_device_event_struct[index_int].fd_int = -1;
			__g_device_event_struct[index_int].use_int8_t = FALSE;
			__g_device_event_struct[index_int].event_type_uint32 &= EVENT_TYPE_NULL;
			break;
		}
	}
//	if(index_int >= MAX_EVENT_NUM)
//		return FALSE;

//	__g_device_event_struct[index_int].fd_int = -1;
//	__g_device_event_struct[index_int].use_int8_t = FALSE;
//	__g_device_event_struct[index_int].event_type_uint32 &= EVENT_TYPE_NULL;

	return TRUE;
}

pthread_mutex_t device_event_mutex;

int defineDeviceEvent(
	int fd_int,
	uint32_t event_type_uint32,
	void  *pdata_pvoid,
	deviceEventHandler event_handler,
	char *description_pchar)
{
	int index_int;


	pthread_mutex_lock(&device_event_mutex);
	for(index_int =0;index_int<MAX_EVENT_NUM;index_int++)
	{
		if(!__g_device_event_struct[index_int].use_int8_t)
		{
			__g_device_event_struct[index_int].use_int8_t = TRUE;
			break;
		}

	}
	pthread_mutex_unlock(&device_event_mutex);
	if(index_int == MAX_EVENT_NUM)
		return eEvent_Error_DeviceEvent_struct_FULL;

	__g_device_event_struct[index_int].fd_int = fd_int;
	__g_device_event_struct[index_int].event_handler = event_handler;
	__g_device_event_struct[index_int].event_type_uint32 = event_type_uint32;
	__g_device_event_struct[index_int].pdata_pvoid = pdata_pvoid;

	if(description_pchar != NULL)
	{
		int desc_len = strlen(description_pchar);
		if(desc_len > MAX_EVENT_DESCRIPTION_SIZE)
			desc_len = 128;

		memcpy(__g_device_event_struct[index_int].description_achar,
			description_pchar,
			sizeof(char[desc_len]));
	}
	return index_int;
}

int8_t setEpollProcessStop( void )
{
	__g_running_int = 0;
	return TRUE;
}

int8_t setEpollProcessStart( void )
{
	__g_running_int = 1;
	return TRUE;
}

int8_t createEpollfd( void )
{
	__g_epfd_int = epoll_create (MAX_EVENT_NUM);  /* plan to watch ~100 fds */
	if (__g_epfd_int < 0)
	{
		PRINT_ERR ("epoll_create error (epfd_int = %d)\n",__g_epfd_int);
		return FALSE;
	}
	return TRUE;
}

int8_t initialEpollDeviceEvent()
{
	if(!createEpollfd())
		return FALSE;
	memset(__g_device_event_struct,
		0,sizeof(tDeviceEvent[MAX_EVENT_NUM]));
	if (pthread_mutex_init(&device_event_mutex, NULL) != 0)
	{
		PRINT_ERR("mutex init failed\n");
		return FALSE;
    }
	return TRUE;
}

void *epollProcessActivity(void *arg)
{

	int num_events = 0;
	int index_int;
	uint64_t  timer_value = 0;
	//char buf[1024];
	tDeviceEvent *event_pstruct;
	while(__g_running_int)
	{
		PRINT_DBG("wait evnet.......\n");
		num_events = epoll_wait (__g_epfd_int, __g_events, MAX_EVENT_NUM, -1);
		if(num_events <=0)
		{
			continue;
		}
		PRINT_DBG("num_events = %d.......\n", num_events);


		for(int i =0;i< num_events;i++)
		{
			PRINT_DBG("i = %d\n ",i);
			if(__g_events[i].events & EPOLLIN)
			{
#if 0
				for(index_int =0;index_int<MAX_EVENT_NUM;index_int++)
				{
					if(__g_events[i].data.ptr ==
						__g_device_event_struct[index_int].fd_int)
					{
						if(EVENT_TYPE_TIMER &
							__g_device_event_struct[index_int].event_type_int)
						{
					                    read(__g_events[i].data.fd, &timer_value, 8 );
						}
						__g_device_event_struct[index_int].event_handler(
							__g_device_event_struct[index_int].fd_int,
							__g_device_event_struct[index_int].pdata_pvoid
							);
					}

				}
#endif
				event_pstruct = (tDeviceEvent *)__g_events[i].data.ptr;
				if((EVENT_TYPE_TIMER &
					event_pstruct->event_type_uint32))
				{
					PRINT_DBG("event_pstruct->fd_int = %d\n", event_pstruct->fd_int);
			        read(event_pstruct->fd_int, &timer_value, 8);
					event_pstruct->event_handler(
						event_pstruct->fd_int,
						event_pstruct->pdata_pvoid);

				}
				else if(EVENT_TYPE_READ_WRITE &
					event_pstruct->event_type_uint32)
				{
					PRINT_DBG("event_pstruct->fd_int = %d\n", event_pstruct->fd_int);
					event_pstruct->event_handler(
						event_pstruct->fd_int,
						event_pstruct->pdata_pvoid);
				}

					PRINT_DBG("\n");
			}
		}
	}
}






