//
// stock.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SERIALIZATION_STOCK_HPP
#define SERIALIZATION_STOCK_HPP

#include <string>

struct Packet {
	int id_;
	std::string opcode_;
	std::string file_path_="tomer";

	Packet(){};

	Packet(int id, std::string op) :
			id_(id), opcode_(op) {
	}
	;

	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & opcode_;
		ar & file_path_;
		ar & id_;

	}
};

#endif // SERIALIZATION_STOCK_HPP
