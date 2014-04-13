/*
 * File_node.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Piotr Fatyga
 *      Login:	pfatyga
 */

#include "File_node.h"

File_node::File_node(std::string file_name, unsigned int file_size) {
	file = new File(file_name, file_size);
}

File_node::~File_node() {
	//TODO: Remove from Linked list
	delete file;
}

File *File_node::get_file() {
	return file;
}
