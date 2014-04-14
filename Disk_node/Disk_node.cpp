/*
 * Disk_node.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: peter
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

Disk_node::Disk_node(unsigned int block_ID_start, unsigned int block_ID_end,
		Disk_node *prev, Disk_node *next) {
	this->block_ID_start = block_ID_start;
	this->block_ID_end = block_ID_end;
	this->prev = prev;
	this->next = next;
	this->in_use = false;
	update_size();
	if (this->next != NULL)
		this->next->prev = this;
}

Disk_node::~Disk_node() {
	// TODO Auto-generated destructor stub
}

void Disk_node::split(unsigned int next_block_ID_start) {
	next_block_ID_start += this->block_ID_start;	//relative
	//std::cout << "Splitting [" << block_ID_start << "," << block_ID_end << "] at " << next_block_ID_start << '\n';
	if (next_block_ID_start > this->block_ID_end)
		return;
	assert(
			next_block_ID_start > this->block_ID_start
					&& next_block_ID_start < this->block_ID_end);
	next = new Disk_node(next_block_ID_start, this->block_ID_end, this,
			this->next);
	block_ID_end = next_block_ID_start - 1;
	update_size();
	assert(block_ID_start <= block_ID_end);
}

void Disk_node::merge() {
	//std::cout << "merging " << *this << '\n';
	Disk_node *temp;
	unsigned int left = this->block_ID_start;
	unsigned int right = this->block_ID_end;
	temp = this->next;
	while (temp != NULL && temp->in_use == this->in_use) {
		std::cout << "right side\n";
		right = temp->block_ID_end;
		if (temp->next != NULL) {
			temp = temp->next;
			delete temp->prev;
			temp->prev = this;
		} else {
			delete temp;
			temp = NULL;
			this->next = NULL;
		}
	}
	this->block_ID_end = right;
	//std::cout << "merged right side: " << this << '\n';
	temp = this->prev;
	//std::cout << "prev: " << temp << '\n';
	while (temp != NULL && temp->in_use == this->in_use) {
		//std::cout << "merge: " << *temp << '\n';
		left = temp->block_ID_start;
		if (temp->prev != NULL) {
			temp = temp->prev;
			delete temp->next;
			temp->next = this;
		} else {
			temp->next = this->next;
			temp->next->prev = temp;
			temp->block_ID_end = this->block_ID_end;
			temp->update_size();
			delete this;//we cant delete the root. It might be used somewhere else. Delete this object instead
			return;
		}
	}
	this->block_ID_start = left;
	this->update_size();
	//std::cout << "done\n";
}

void Disk_node::update_size() {
	block_ID_size = block_ID_end - block_ID_start + 1;//block 3 - 5 is 3 blocks: 3, 4, 5 but 5 - 3 = 2
}

unsigned int Disk_node::size() {
	unsigned int total = 1;
	Disk_node *temp = this;
	while ((temp = temp->next) != NULL)
		total++;
	return total;
}

Disk_node *Disk_node::get_next_free_block() {
	Disk_node *temp = this;
	while (temp != NULL && temp->in_use == true)
		temp = temp->next;
	return temp;
}

std::ostream &operator<<(std::ostream &os, Disk_node const &node) {
	Disk_node *temp = node.next;
	os << &node << ":[" << node.block_ID_start << "," << node.block_ID_end
			<< "," << node.in_use << "]";
	while (temp != NULL) {
		os << '\t' << temp << ":[" << temp->block_ID_start << ","
				<< temp->block_ID_end << "," << temp->in_use << "]";
		temp = temp->next;
	};
	return os;
}
