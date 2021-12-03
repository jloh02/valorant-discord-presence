#pragma once

#include <iostream>
#include <thread>

#include "httplib/httplib.h"

#include "riot_api_connection.h"

#define LOCAL_PORT 36886

namespace server {
	bool initialize();
	void listenAsync();
	void stop();
}