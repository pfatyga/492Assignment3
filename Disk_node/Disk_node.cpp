/*
 * Disk_node.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
 */

#include "Disk_node.h"

Disk_node::Disk_node(unsigned int block_ID_start, unsigned int block_ID_end) {
	this->block_ID_start = block_ID_start;
	this->block_ID_end = block_ID_end;
	this->next = NULL;
	this->prev = NULL;
	this->in_use = false;
	update_size();
}

Disk_node::Disk_node(unsigned int block_ID_start, unsigned int block_ID_end, Disk_node *prev, Disk_node *next) : Disk_node(block_ID_start, block_ID_end) {
	this->prev = prev;
	this->next = next;
	if(this->next != NULL)
		this->next->prev = this;
}

Disk_node::~Disk_node() {
	// TODO Auto-generated destructor stub
}

void Disk_node::split(unsigned int next_block_ID_start) {
	assert(next_block_ID_start > this->block_ID_start && next_block_ID_start < this->block_ID_end);
	next = new Disk_node(next_block_ID_start, this->block_ID_end, this, this->next);
	block_ID_end = next_block_ID_start-1;
	update_size();
	assert(block_ID_start <= block_ID_end);
}

void Disk_node::merge() {
	Disk_node *temp;
	unsigned int left = this->block_ID_start;
	unsigned int right = this->block_ID_end;
	temp = this->next;
	while(temp != NULL && temp->in_use == this->in_use)
	{

		right = temp->block_ID_end;
		if(temp->next != NULL)
		{
			temp = temp->next;
			delete temp->prev;
			temp->prev = this;
		}
		else
		{
			delete temp;
			temp = NULL;
			this->next = NULL;
		}
	}
	this->block_ID_end = right;
	temp = this->prev;
	while(temp != NULL && temp->in_use == this->in_use)
	{

		left = temp->block_ID_start;
		if(temp->prev != NULL)
		{
			temp = temp->prev;
			delete temp->next;
			temp->next = this;
		}
		else
		{
			temp->next = this->next;
			temp->block_ID_end = this->block_ID_end;
			temp->update_size();
			delete this;	//we cant delete the root. It might be used somewhere else. Delete this object instead
			return;
		}
	}
	this->block_ID_start = left;
	this->update_size();
}

void Disk_node::update_size() {
	block_ID_size = block_ID_end - block_ID_start + 1;	//block 3 - 5 is 3 blocks: 3, 4, 5 but 5 - 3 = 2
}

unsigned int Disk_node::size() {
	unsigned int total = 1;
	Disk_node *temp = this;
	while((temp = temp->next) != NULL)
		total++;
	return total;
}

std::ostream &operator<<(std::ostream &os, Disk_node const &node) {
	Disk_node *temp = node.next;
	os << &node << ":[" << node.block_ID_start << "," << node.block_ID_end << "]";
	while(temp != NULL){
		os << '\t' << temp << ":[" << temp->block_ID_start << "," << temp->block_ID_end << "]";
		temp = temp->next;
	};
	return os;
}
