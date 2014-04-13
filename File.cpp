/*
 * File.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
 */

#include "File.h"

File::File(std::string file_name, unsigned int file_size) {
	name = file_name;
	size = file_size;
	update_timestamp();
}

File::~File() {
	// TODO Auto-generated destructor stub
}

void File::update_timestamp() {
	//TODO: set timestamp to current time
}

