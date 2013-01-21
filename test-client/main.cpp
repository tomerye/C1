#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "connection.hpp" // Must come before boost/serialization headers.
#include <boost/serialization/vector.hpp>
#include "packet.h"
#include "client.cpp"
#include <boost/thread.hpp>

int main(int argc, char* argv[]) {
	try {
		// Check command line arguments.
		if (argc != 3) {
			std::cerr << "Usage: client <host> <port>" << std::endl;
			return 1;
		}

		boost::asio::io_service io_service;
		client client(io_service, argv[1], argv[2],123);
		for(int i=0; i<10;i++)
		{
			boost::this_thread::sleep(boost::posix_time::millisec(1000));
			client.send(new Packet(1,"KEEPALAIVE"));
		}
		io_service.run();

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
