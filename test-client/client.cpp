//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "connection.hpp"
#include <boost/serialization/vector.hpp>
#include "packet.h"

class client {
public:
	client(boost::asio::io_service& io_service, const std::string& host, const std::string& service, int id) :
			connection_(io_service), id_(id) {
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(host, service);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		boost::asio::async_connect(connection_.socket(), endpoint_iterator,
				boost::bind(&client::handle_connect, this, boost::asio::placeholders::error));
	}

	void handle_connect(const boost::system::error_code& e) {
		if (!e) {
			Packet *sendPacket = new Packet(id_, "REGISTER");
			connection_.async_write(sendPacket,
					boost::bind(&client::handel_connect, this, boost::asio::placeholders::error, sendPacket));
		} else {

			std::cerr << e.message() << std::endl;
		}
	}

	void handel_connect(const boost::system::error_code& e, Packet *sendPacket) {
		delete sendPacket;
		if (!e) {
			lisening_for_incoming_packet();
		} else {
			std::cout << "cannot connect\n";
		}
	}

	void lisening_for_incoming_packet() {
		Packet *recvPacket = new Packet();
		connection_.async_read(*recvPacket,
				boost::bind(&client::handle_action, this, boost::asio::placeholders::error, recvPacket));
	}
	void handle_action(const boost::system::error_code& e, Packet *recvPacket) {
		if (!e) {
			//TODO do something
			delete recvPacket;
			lisening_for_incoming_packet();

		} else {
			std::cerr << e.message() << std::endl;
		}

	}

	void send(Packet *sendPacket) {
		connection_.async_write(*sendPacket,
				boost::bind(&client::do_nothing, this, boost::asio::placeholders::error, sendPacket));
		std::cout << "sent packet\n";
	}

	void do_nothing(const boost::system::error_code& e, Packet *sendPacket) {
		delete sendPacket;
		if (!e) {

		} else {
			std::cerr << e.message() << std::endl;
		}
	}
private:
	connection connection_;
	int id_;
};

