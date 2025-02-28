#pragma once
#include <iostream>
#include <cassert>
#include <climits>
using namespace std;


class SingleLinkedList 
{

private:
	struct Node {

		int data{ };
		Node* next{ };

		Node(int data) :data(data) {}

		~Node() {
			//To easily test your nodes are destructed
			cout << "Destroy value: " << data << "\n";
		}
	};


	Node* head{ };
	Node* tail{ };
	int length = 0;	// let's maintain how many nodes

public:
	//destructor of single linked list
	~SingleLinkedList() {

		while (head) {
			Node* current = head->next;
			delete head; // the node will deleted and call destructor of node 
			head = current;
		}
	}


	void print() {

		cout << "\nElements in single linked list: ";
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur->data << " ";
		cout << "\n";
	}

	int getLength() {
		return length;
	}

	void insert_end(int value) {
		Node* item = new Node(value);
		if (!head)
			head = tail = item;
		else
		{
			tail->next = item;
			tail = item;
		}
		++length;
	}

	void insert_front(int value) {

		Node* newNode = new Node(value);

		if (head)
		{
			newNode->next = head;
			head = newNode;
		}
		else
			head = tail = newNode;

		++length;
	}

	void delete_front()
	{
		if (!head)
			return;

		Node* current = head;
		head = head->next;

		if (!head)
			tail = nullptr;

		delete current;
		--length;
	}



	Node* get_node_With_Pos(int pos)
	{
		int cur_pos = 1;

		for (Node* cur_node = head; cur_node; cur_node = cur_node->next)
		{
			if (pos == cur_pos)
				return cur_node;

			++cur_pos;
		}

		return nullptr;
	}

	Node* get_node_With_Value(int value)
	{

		for (Node* cur_node = head; cur_node; cur_node = cur_node->next)
			if (cur_node->data == value)
				return cur_node;

		return nullptr;
	}

	void delete_node_With_Key(int key)
	{
		delete_node(get_node_With_Value(key));
	}

	void reverse()
	{
		if (length <= 1) return;

		tail = head;

		Node* prev = nullptr;
		Node* current = head;

		while (current)
		{
			Node* next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		head = prev;
		
	}
	void delete_node(Node* node)
	{
		if (!node || !head) return;  // Handle null node or empty list case

		// Special case: If the list has only one node
		if (head == tail && node == head)
		{
			head = tail = nullptr;
			delete node;
			--length;
			return;
		}

		// Handle case where the node to delete is the head node
		if (node == head)
		{
			head = head->next;
			if (head == nullptr)  // List is now empty
			{
				tail = nullptr;
			}
			delete node;
			--length;
			return;
		}

		// Find the previous node
		Node* prev = head;
		while (prev && prev->next != node)
		{
			prev = prev->next;
		}

		if (prev)
		{
			prev->next = node->next;
			if (node == tail)  // Update tail if needed
			{
				tail = prev;
			}
			delete node;
			--length;
		}
	}

	void delete_next(Node* cur)
	{

		if (!cur->next) return;

		Node* targetNode = cur->next;
		cur->next = cur->next->next;

		bool is_tail = targetNode == tail;

		delete_node(targetNode);

		if (is_tail)
			tail = cur;
	}

	void delete_even_positions()
	{
		if (length <= 1)
			return;
		// maintain previous and delete its next (even order)
		for (Node* cur = head->next, *prv = head;cur;)
		{
			delete_next(prv);	// prev is odd, prev-next is even
			if (!prv->next)	// tail
				break;
			cur = prv->next->next;
			prv = prv->next;
		}

	}

	void insert_to_be_sorted(int value)
	{
		if (length == 0 || head->data >= value)
		{
			insert_front(value);
			return;
		}

		if (tail->data <= value)
		{
			insert_end(value);
			return;
		}

		for (Node* prev = head, *cur = head->next; cur; cur = cur->next)
		{
			//insert new node before node has data greater than newNode->data
			if (cur->data >= value)
			{
				Node* insertedNode = new Node(value);
				insertedNode->next = cur;
				prev->next = insertedNode;

				++length;
				return;
			}
			prev = cur;
		}

	}

	void swap_head_with_tail()
	{
		if (length <= 1)
			return;

		Node* prev = get_node_With_Pos(length - 1);

		prev->next = head;
		tail->next = head->next;
		head->next = nullptr;

		swap(head, tail);
		tail->next = nullptr;
	}

	void left_rotate(int k) // make linked list shift to left k times ,to efficient solving: we say k is pos and make after pos to right 
	{
		k %= length;  // ex : after left 19 times = 4 times

		if (length <= 1 || k == 0) // if k=nk will be k=0
			return;


		if (length == 2)
		{
			swap_head_with_tail();
			return;
		}

		Node* newTail = get_node_With_Pos(k);
		tail->next = head;
		head = newTail->next;
		newTail->next = nullptr;
		tail = newTail;

	}

	void remove_duplicates()
	{

		if (length <= 1) return;

		for (Node* cur1 = head; cur1; cur1 = cur1->next)
		{
			for (Node* cur2 = cur1->next, *prev = cur1; cur2;)
			{
				if (cur2->data == cur1->data)
				{
					delete_next(prev);
					cur2 = prev->next;

				}
				else
				{
					prev = cur2;
					cur2 = cur2->next;
				}
			}
		}
	}


	Node* get_prev_node(Node* cur)
	{
		if (length <= 1 || !cur || head == cur)
			return nullptr;

		Node* prev = head;

		while (prev && prev->next != cur)
		{
			prev = prev->next;
		}


		return prev;

	}

	void remove_last_occurrence(int key)
	{
		if (length <= 1)
			return;

		Node* targetNode = nullptr;
		Node* prev = nullptr;
		Node* cur = head;
		;

		bool is_found = false;

		// continue from here 

	}

	


};



