/*
 * Tree_node.h
 *
 *  Created on: Apr 13, 2014
 *      Author: Piotr Fatyga
 *      Login:	pfatyga
 */

#ifndef TREE_NODE_H_
#define TREE_NODE_H_

#include "../main.h"
#include "../Disk_node/Disk_node.h"
#include <ctime>

class Tree_node {
protected:
	std::string name;
	std::string path;
	std::string timestamp;
	bool directory;	//1 - directory, 0 - file
public:
	Tree_node() {};
	virtual ~Tree_node() {};
	std::string get_name();
	std::string get_path();
	bool is_directory();
	void update_timestamp();
	static Disk_node *disk_nodes;

};

#endif /* TREE_NODE_H_ */
