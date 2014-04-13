/*
 * Directory_node.h
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
 */

#ifndef DIRECTORY_NODE_H_
#define DIRECTORY_NODE_H_

#include "main.h"

class Directory_node: public Tree_node {
	std::string name;
	std::string path;
	std::map<std::string, Tree_node *> children;	//key: name of file/directory
public:
	Directory_node(std::string directory_name);
	virtual ~Directory_node();
};

#endif /* DIRECTORY_NODE_H_ */
