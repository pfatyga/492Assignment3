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
	parent_directory = NULL;
	directory = true;
}

Directory_node::Directory_node(std::string directory_name, std::string directory_path, Directory_node *parent_directory) {
	name = directory_name;
	path = directory_path;
	this->parent_directory = parent_directory;
	directory = true;
}

Directory_node::~Directory_node() {
	// TODO Auto-generated destructor stub
}

Directory_node *Directory_node::get_directory(std::string name) {
	if(name == ".")
		return this;
	if(name == "..")
	{
		if(parent_directory == NULL)
			std::cout << "no parent directory\n";
		return NULL;
	}
	if(children.find(name) != children.end())	//cant just check children[name] == NULL because it actually creates the key,value pair and then causes segfaults later on
	{
		if(children[name]->is_directory())
		{
			return dynamic_cast<Directory_node *>(children[name]);
		}
		else	//not a directory
		{
			std::cout << "not a directory: " << name << '\n';
		}
	}
	else
	{
		std::cout << "no such file or directory: " << name << '\n';
	}
	return NULL;

}

File_node *Directory_node::get_file(std::string name) {
	if(children.find(name) != children.end())	//cant just check children[name] == NULL because it actually creates the key,value pair and then causes segfaults later on
	{
		if(!(children[name]->is_directory()))
		{
			return dynamic_cast<File_node *>(children[name]);
		}
		else	//not a file
		{
			std::cout << "not a file: " << name << '\n';
		}
	}
	else
	{
		std::cout << "no such file or directory: " << name << '\n';
	}
	return NULL;

}

void Directory_node::create_directory(char *path) {
	if(path == this->path)
		return;
	else
	{
		std::cout << "Creating directory " << path << '\n';
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
					temp->children[directory_name] = new Directory_node(directory_name, temp_path, temp);
				}
				temp = dynamic_cast<Directory_node *>(temp->children[directory_name]);
			}

		    directory_name = strtok(NULL, "/");
		}
	}
}

bool Directory_node::create_file(char *path, unsigned int size) {
	std::cout << "Creating file " << path << '\n';
	Directory_node *temp = this;
	std::string temp_path = "";
	char *file_name = strtok(path, "/");
	char *temp_name = NULL;
	while (file_name) {
		//printf ("Token: %s\n", p);
		if(strcmp(file_name, ".") == 0)	//dont add . as subdirectory
		{
			temp_path += file_name;
		}
		else
		{
			temp_path += "/";
			temp_path += file_name;
			if(temp->children[file_name] == NULL)
			{
				if(!(temp_name = strtok(NULL, "/")))	//if there is no more in string then create the file
				{
					File_node *file = new File_node(file_name, temp_path, size);
					bool success = size > 0 ? file->allocate_disk_space() : true;
					temp->children[file_name] = file;
					//////////////////////////////////////
					//if(size > 0)
					//	std::cout << *(file->get_file()) << '\n';
					////////////////////////////////////////
					return success;
				}
				else
				{
					file_name = temp_name;
					temp->children[file_name] = new Directory_node(file_name, temp_path, temp);
					temp = dynamic_cast<Directory_node *>(temp->children[file_name]);
					std::cout << "Created a directory when adding a file....should not happen.\n";
					continue;	//need to skip strtok because we already did it
				}
			}
			temp = dynamic_cast<Directory_node *>(temp->children[file_name]);
		}

		file_name = strtok(NULL, "/");
	}
	return false;
}

bool Directory_node::create_file(std::string name, unsigned int size) {
	if(this->children[name] == NULL)
	{
		File_node *file = new File_node(name, this->path + "/" + name, size);
		bool success = size > 0 ? file->allocate_disk_space() : true;
		this->children[name] = file;
		return success;
	}
	else	//directory already exists
	{
		return false;
	}
}

bool Directory_node::create_subdirectory(std::string name) {
	if(this->children[name] == NULL)
	{
		this->children[name] = new Directory_node(name, this->path + "/" + name, this);
		return true;
	}
	else	//directory already exists
	{
		return false;
	}
}

bool Directory_node::delete_child(std::string name) {
	auto it = children.find(name);
	if(it != children.end()) {
		if((*it).second->is_directory())
		{
			Directory_node *temp = dynamic_cast<Directory_node *>((*it).second);
			if(temp->children.size() > 0)
			{
				std::cout << "Directory not empty.\n";
				return false;
			}
		}
		delete (*it).second;
		children.erase(it);
		return true;
	}
	else
	{
		std::cout << "File not found.\n";
		return false;
	}
}

void Directory_node::dir_print(Directory_node *root) {
	for(auto it = root->children.begin(); it != root->children.end(); it++)
	{
		if((*it).second->is_directory())
			std::cout << (*it).second->get_name() << '\n';
	}
}

void Directory_node::ls_print(Directory_node *root) {
	for(auto it = root->children.begin(); it != root->children.end(); it++)
	{
		std::cout << (*it).second->get_name() << '\n';
	}
}

void Directory_node::BFS_print(Tree_node *root) {
	std::cout << root->get_path() << '\n';
	if(!(root->is_directory()))
		return;
	Directory_node *temp = dynamic_cast<Directory_node *>(root);
	for(auto it = temp->children.begin(); it != temp->children.end(); it++)
	{
		BFS_print((*it).second);
	}
}
