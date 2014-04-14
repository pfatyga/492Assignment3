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

class Tree_node {
protected:
	std::string name;
	std::string path;
public:
	Tree_node() {};
	virtual ~Tree_node() {};
	std::string get_name();
	std::string get_path();

	static Disk_node *disk_nodes;
};

#endif /* TREE_NODE_H_ */
