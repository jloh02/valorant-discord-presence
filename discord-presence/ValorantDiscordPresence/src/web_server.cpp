#include "web_server.h"

namespace server {
	httplib::Server svr;

	bool initialize() {
		svr.Get("/hi", [](const httplib::Request& req, httplib::Response& res) {
			res.set_content("Hello World!", "text/plain");
		});
		svr.Get(R"(/numbers/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
			auto numbers = req.matches[1];
			res.set_content(numbers, "text/plain");
			});

		svr.Get("/body-header-param", [](const httplib::Request& req, httplib::Response& res) {
			if (req.has_header("Content-Length")) {
				auto val = req.get_header_value("Content-Length");
			}
			if (req.has_param("key")) {
				auto val = req.get_param_value("key");
			}
			res.set_content(req.body, "text/plain");
			});
		svr.Post("/invite", [](const httplib::Request& req, httplib::Response& res) {

		});
		int port = MIN_PORT;
		while (!svr.bind_to_port("localhost", port) && port < MIN_PORT + NUM_PORTS) port++;
		std::cout << port << std::endl;

		return (port < MIN_PORT + NUM_PORTS);
	}

	void listenAsync() {
		svr.listen_after_bind();
	}

	void stop() {
		svr.stop();
	}
}