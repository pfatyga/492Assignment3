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
	// TODO Auto-generated destructor stub
}

Disk_node *Disk_node::split(unsigned int next_block_ID_start) {
	next_block_ID_start += this->block_ID_start;	//relative
	//std::cout << "Splitting [" << block_ID_start << "," << block_ID_end << "] at " << next_block_ID_start << '\n';
	if (next_block_ID_start <= this->block_ID_start || next_block_ID_start > this->block_ID_end)
		return this;
	//std::cout << "[" << block_ID_start << ", " << block_ID_end << "]\n";
	//std::cout << "next_block: " << next_block_ID_start << '\n';
	//assert(next_block_ID_start > this->block_ID_start);
	//assert(next_block_ID_start <= this->block_ID_end);
	next = new Disk_node(next_block_ID_start, this->block_ID_end, this->in_use, this, this->next);
	if(next->next != NULL)
		next->next->prev = next;
	block_ID_end = next_block_ID_start - 1;
	update_size();
	//assert(block_ID_start <= block_ID_end);
	return next;
}

void Disk_node::merge() {
	//std::cout << "merging " << *this << '\n';
	Disk_node *temp;
	unsigned int left = this->block_ID_start;
	unsigned int right = this->block_ID_end;
	temp = this->next;
	//merge everything to the right into this Disk_node
	while (temp != NULL && temp->in_use == this->in_use) {
		//std::cout << "right side\n";
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
	//std::cout << "merged right side: " << this << '\n';
	temp = this->prev;
	//std::cout << "prev: " << temp << '\n';
	//merge everything to the left into this Disk_node EXCEPT the first node.
	while (temp != NULL && temp->in_use == this->in_use) {
		//std::cout << "left side\n";
		//std::cout << temp << '\n';
		//std::cout << "merge: " << *temp << '\n';
		left = temp->block_ID_start;
		if (temp->prev != NULL) {
			//std::cout << "A\n";
			temp = temp->prev;
			delete temp->next;
			//std::cout << temp << '\n';
			temp->next = this;
			this->prev = temp;
		} else {
			//std::cout << "B\n";
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
	/*if(this->prev != NULL)
		assert(this->prev->next == this);
	if(this->next != NULL)
		assert(this->next->prev == this);*/
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

void Disk_node::free(unsigned int block_ID) {
	Disk_node *temp = this;
	while(temp != NULL && !(block_ID >= temp->block_ID_start && block_ID <= temp->block_ID_end))
	{
		temp = temp->next;
	}
	if(temp == NULL)
		return;
	//std::cout << "block_ID: " << block_ID << ", " << block_ID - temp->block_ID_start << '\n';
	//std::cout << (*temp) << '\n';
	//if(temp->prev != NULL)
	//		std::cout << temp->prev->prev << '\n';
	//assert(temp->in_use == true);
	temp = temp->split(block_ID - temp->block_ID_start);
	//std::cout << (*temp) << '\n';
	//if(temp->prev != NULL)
	//	std::cout << temp->prev->prev << '\n';
	temp->split(1);
	temp->in_use = false;
	//std::cout << (*temp) << '\n';
	//if(temp->prev != NULL)
	//		std::cout << temp->prev->prev << '\n';
	temp->merge();
	//if(temp->prev != NULL)
	//		std::cout << temp->prev->prev << '\n';
	//std::cout << (*temp) << '\n';
}

/*std::ostream &operator<<(std::ostream &os, Disk_node const &node) {
	Disk_node *temp = node.next;
	os << &node << ":[" << node.block_ID_start << "," << node.block_ID_end
			<< "," << node.in_use << "]";
	while (temp != NULL) {
		os << '\t' << temp << ":[" << temp->block_ID_start << ","
				<< temp->block_ID_end << "," << temp->in_use << "]";
		temp = temp->next;
	};
	return os;
}*/

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
