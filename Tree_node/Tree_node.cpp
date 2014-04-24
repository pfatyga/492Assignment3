/*
 * Tree_node.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Piotr Fatyga
 *      Login:	pfatyga
 */

#include "Tree_node.h"

Disk_node *Tree_node::disk_nodes;

std::string Tree_node::get_name() {
	return name;
}

std::string Tree_node::get_path() {
	return path;
}

bool Tree_node::is_directory() {
	return directory;
}

void Tree_node::update_timestamp() {
	time_t now = time(0);
	tm *gmtm = gmtime(&now);
	this->timestamp = asctime(gmtm);
}
