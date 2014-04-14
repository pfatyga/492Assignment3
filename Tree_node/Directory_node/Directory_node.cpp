/*
 * Directory_node.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
 */

#include "Directory_node.h"

Directory_node::Directory_node(std::string directory_name) {
	name = directory_name;
	path = directory_name;	//this is only used when creating the root node which has the same name and path (.)
	directory = true;
}

Directory_node::Directory_node(std::string directory_name, std::string directory_path) {
	name = directory_name;
	path = directory_path;
	directory = true;
}

Directory_node::~Directory_node() {
	// TODO Auto-generated destructor stub
}

void Directory_node::create_directory(char *path) {
	if(path == this->path)
		return;
	else
	{
		Directory_node *temp = this;
		std::string temp_path = "";
		char *directory_name = strtok(path, "/");
		while (directory_name) {
		    //printf ("Token: %s\n", p);
			if(strcmp(directory_name, ".") == 0)	//dont add . as subdirectory
			{
				temp_path += directory_name;
			}
			else
			{
				temp_path += "/";
				temp_path += directory_name;
				if(temp->children[directory_name] == NULL)
				{
					temp->children[directory_name] = new Directory_node(directory_name, temp_path);
				}
				temp = dynamic_cast<Directory_node *>(temp->children[directory_name]);
			}

		    directory_name = strtok(NULL, "/");
		}
	}
}

bool Directory_node::create_subdirectory(std::string name) {
	if(this->children[name] == NULL)
	{
		this->children[name] = new Directory_node(name, this->path + "/" + name);
		return true;
	}
	else	//directory already exists
	{
		return false;
	}
}

void Directory_node::BFS_print(Tree_node *root) {
	std::cout << root->get_path() << '\n';
	if(!root->is_directory())
		return;
	Directory_node *temp = dynamic_cast<Directory_node *>(root);
	for(auto it = temp->children.begin(); it != temp->children.end(); it++)
	{
		BFS_print(dynamic_cast<Directory_node *>((*it).second));
	}
}
