/*
 * Disk_node.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Piotr Fatyga
 *      login:	pfatyga
 */

#include "Disk_node.h"

unsigned int Disk_node::block_size;
unsigned int Disk_node::disk_size;
unsigned int Disk_node::total_blocks;

Disk_node::Disk_node(unsigned int block_ID_start, unsigned int block_ID_end) {
	this->block_ID_start = block_ID_start;
	this->block_ID_end = block_ID_end;
	this->next = NULL;
	this->prev = NULL;
	this->in_use = false;
	update_size();
}

Disk_node::Disk_node(unsigned int block_ID_start, unsigned int block_ID_end, bool in_use, Disk_node *prev, Disk_node *next) {
	this->block_ID_start = block_ID_start;
	this->block_ID_end = block_ID_end;
	this->prev = prev;
	this->next = next;
	this->in_use = in_use;
	update_size();
	if (this->next != NULL)
		this->next->prev = this;
}

Disk_node::~Disk_node() {

}

//splits a disk node [5 -> 20].split(2) = [5 -> 6] -> [7 -> 20]
Disk_node *Disk_node::split(unsigned int next_block_ID_start) {
	next_block_ID_start += this->block_ID_start;	//relative
	if (next_block_ID_start <= this->block_ID_start || next_block_ID_start > this->block_ID_end)
		return this;
	next = new Disk_node(next_block_ID_start, this->block_ID_end, this->in_use, this, this->next);
	if(next->next != NULL)
		next->next->prev = next;
	block_ID_end = next_block_ID_start - 1;
	update_size();
	return next;
}

//merges a disk_node to the left and right
void Disk_node::merge() {
	Disk_node *temp;
	unsigned int left = this->block_ID_start;
	unsigned int right = this->block_ID_end;
	temp = this->next;
	//merge everything to the right into this Disk_node
	while (temp != NULL && temp->in_use == this->in_use) {
		right = temp->block_ID_end;
		if (temp->next != NULL) {
			temp = temp->next;
			delete temp->prev;
			temp->prev = this;
			this->next = temp;
		} else {
			delete temp;
			temp = NULL;
			this->next = NULL;
		}
	}
	this->block_ID_end = right;
	temp = this->prev;
	//merge everything to the left into this Disk_node EXCEPT the first node.
	while (temp != NULL && temp->in_use == this->in_use) {
		left = temp->block_ID_start;
		if (temp->prev != NULL) {
			temp = temp->prev;
			delete temp->next;
			temp->next = this;
			this->prev = temp;
		} else {
			temp->next = this->next;
			if(temp->next != NULL)
				temp->next->prev = temp;
			temp->block_ID_end = this->block_ID_end;
			temp->update_size();
			delete this;	//we cant delete the root. It might be used somewhere else. Merge into root and delete this object
			return;
		}
	}
	this->block_ID_start = left;
	this->update_size();
}

void Disk_node::update_size() {
	block_ID_size = block_ID_end - block_ID_start + 1;//block 3 - 5 is 3 blocks: 3, 4, 5 but 5 - 3 = 2
}

//returns how many nodes in the linked list
unsigned int Disk_node::size() {
	unsigned int total = 1;
	Disk_node *temp = this;
	while ((temp = temp->next) != NULL)
		total++;
	return total;
}

//goes through the linked list and returns the first node which is free
Disk_node *Disk_node::get_next_free_block() {
	Disk_node *temp = this;
	while (temp != NULL && temp->in_use == true)
		temp = temp->next;
	return temp;
}

//goes through the list, finds the node that contains block_ID, splits it to isolate block_ID, sets block_ID to free, merges block_ID
void Disk_node::free(unsigned int block_ID) {
	Disk_node *temp = this;
	while(temp != NULL && !(block_ID >= temp->block_ID_start && block_ID <= temp->block_ID_end))
	{
		temp = temp->next;
	}
	if(temp == NULL)
		return;
	temp = temp->split(block_ID - temp->block_ID_start);
	temp->split(1);
	temp->in_use = false;
	temp->merge();
}

//prints Disk_node linked list
std::ostream &operator<<(std::ostream &os, Disk_node const &node) {
	Disk_node *temp = node.next;
	std::string temp_use;
	if(node.in_use)
		temp_use = "In use: ";
	else
		temp_use = "Free: ";
	os << temp_use << node.block_ID_start << "-" << node.block_ID_end;
	while (temp != NULL) {
		if(temp->in_use)
				temp_use = "In use: ";
			else
				temp_use = "Free: ";
		os << '\n' << temp_use << temp->block_ID_start << "-" << temp->block_ID_end;
		temp = temp->next;
	};
	return os;
}
