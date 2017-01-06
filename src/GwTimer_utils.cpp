#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>


#include "GwTimer_utils.h"
#include "PreDefine.h"



bool setupTimer(
	uint64_t seconds_uint64,
	uint64_t milliseconds_uint64, 
	bool continious_bool, 
	deviceEventHandler  eventhandler_callback, 
	void * eventhandler_data_pvoid)
{
	struct itimerspec its_struct;
	int timer_fd_int =  timerfd_create(CLOCK_MONOTONIC, O_CLOEXEC);
	if(timer_fd_int == -1)
	{
		PRINT_ERR("defineDeviceEvent error(timer_fd_int = %d)\n",timer_fd_int);
		return false;
	}
	
	char desc_achar[] = "Timer";
	int index_int = defineDeviceEvent(timer_fd_int, 
					EVENT_TYPE_TIMER,
					eventhandler_data_pvoid,	
					eventhandler_callback, 
					desc_achar);
	if(index_int <0)
	{
		PRINT_ERR("defineDeviceEvent error(index_int = %d)\n",index_int);
		return false;
	}
		
	 
	its_struct.it_value.tv_sec = seconds_uint64;
	its_struct.it_value.tv_nsec = milliseconds_uint64 ;
	its_struct.it_interval.tv_sec = continious_bool ? its_struct.it_value.tv_sec : 0;
	its_struct.it_interval.tv_nsec = continious_bool ? its_struct.it_value.tv_nsec : 0;
	if (timerfd_settime(timer_fd_int, 0, &its_struct, NULL) == 0) 
	{
		
		if(epollAddEvent(index_int,EPOLLIN))
		{
//			PRINT_DBG("add event\n");
			return true;
		}
			
	}
	
	PRINT_ERR("Error setting timer\n");
	
	close(timer_fd_int);
	return false;
}

void timer_data_handler
	(int time_int ,void * data_pvoid)
{
	PRINT_DBG("time = %d data = %s\n",time_int ,(char*)data_pvoid);
}




