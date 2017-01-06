#pragma once



#include <stdint.h>
#include "epolling.h"

bool setupTimer(
	uint64_t seconds_uint64,
	uint64_t milliseconds_uint64, 
	bool continious_bool, 
	deviceEventHandler  eventhandler_callback, 
	void * eventhandler_pvoid);

void timer_data_handler
		(int time ,void * data_pvoid);




