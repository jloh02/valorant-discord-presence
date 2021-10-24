#pragma once

#include <iostream>
#include <thread>

#include "httplib/httplib.h"

#define MIN_PORT 36888
#define NUM_PORTS 100

namespace server{
	bool initialize();
	void listenAsync();
	void stop();
}