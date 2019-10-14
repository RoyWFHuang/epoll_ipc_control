#pragma once



#include <stdint.h>
#include "epolling.h"

int8_t setupTimer(
	uint64_t seconds_uint64,
	uint64_t milliseconds_uint64,
	int8_t continious_bool,
	deviceEventHandler  eventhandler_callback,
	void * eventhandler_pvoid);

void timer_data_handler
		(int time ,void * data_pvoid);




