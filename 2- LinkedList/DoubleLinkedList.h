#pragma once
#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

class DoubleLinkedList {
private:
    struct Node {
        int data{};
        Node* next{};
        Node* prev{};

        Node(int data) : data(data) {}

        ~Node() {
            cout << "Destroy value: " << data << "\n";
        }
    };

    Node* head{};
    Node* tail{};
    int length{};

public:
    ~DoubleLinkedList() {
        clear();
    }

    void clear() {
        while (head) {
            Node* cur = head->next;
            delete head;
            head = cur;
        }
        head = tail = nullptr;
        length = 0;
    }

    int get_length() const {
        return length;
    }

    void link(Node* first, Node* second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    void insert_end(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            link(tail, newNode);
            tail = newNode;
        }
        ++length;
    }

    void insert_front(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            link(newNode, head);
            head = newNode;
        }
        ++length;
    }

    void print() const {
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    void print_reversed() const {
        for (Node* cur = tail; cur; cur = cur->prev)
            cout << cur->data << " ";
        cout << "\n";
    }

    void delete_node(Node* targetNode) {
        if (!targetNode)
            return;
        delete targetNode;
        --length;
    }

    void delete_front() {
        if (!head)
            return;
        Node* cur = head->next;
        delete_node(head);
        head = cur;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
    }

    void delete_end() {
        if (!head)
            return;
        if (head == tail) {
            delete_node(head);
            head = tail = nullptr;
            return;
        }
        Node* cur = tail;
        tail = tail->prev;
        delete_node(cur);
        if (tail)
            tail->next = nullptr;
    }

    Node* delete_and_link(Node* cur) {
        Node* prev = cur->prev;
        link(cur->prev, cur->next);
        delete_node(cur);
        return prev;
    }

    void delete_node_with_key(int key) {
        if (!head)
            return;
        if (head->data == key) {
            delete_front();
            return;
        }
        for (Node* cur = head; cur; cur = cur->next) {
            if (cur->data == key) {
                cur = delete_and_link(cur);
                if (!cur->next)
                    tail = cur;
                break;
            }
        }
    }


    void embed_after(Node* node_before, int value) {
        // Add a node with value between node and its next
        Node* middle = new Node(value);

        Node* node_after = node_before->next;
        link(node_before, middle);
        link(middle, node_after);
        ++length;
    }

    void insert_sorted(int value) {		// O(n) time - O(1) memory
        // 3 special cases for simplicity
        if (!length || value <= head->data)
            insert_front(value);
        else if (tail->data <= value)
            insert_end(value);
        else {
            // Find the node I am less than. Then I am before it
            for (Node* cur = head; cur; cur = cur->next) {
                if (value <= cur->data) {
                    embed_after(cur->prev, value);
                    break;
                }
            }
        }
        // This idea is used in Insertion Sort Algorithm
    }

    // home work 

    void delete_all_nodes_with_key(int key)
    {
        if (!head)
            return;

        while (head && head->data == key)
        {
            delete_front(); // delete all head if has data = key value 
        } 
        
        // ^ instead of while loop we insert_front(dummy node) here and delete_front() after for loop 

        for (Node* cur = head; cur; cur = cur->next)
        {
            if (cur->data == key)
            {
                cur = delete_and_link(cur);
                if (!cur->next)
                    tail = cur;
            }
        }
    }
    void delete_even_positions()
    {
        if (length <= 1)
            return;

        for (Node* cur = head;cur && cur->next;cur= cur->next )// cur is odd , cur->next is even (target)
        {
            cur = delete_and_link(cur->next);

            if (!cur->next)
                tail = cur;
               
            
        }

    }
    void delete_odd_positions()
    {
        if (length <= 1) 
            return;

        insert_front(-1); // dummy node 
        delete_even_positions();
        delete_front();
    }

    bool is_palindrome() {

        if (length <= 1)
            return true;

        int n = length / 2;
        
        Node* start = head; 
        Node* end = tail;

        while (n--)
        {
            if (start->data != end->data)
                return false;

            start = start->next;
            end = end->prev;
        }

        return true;

    }



};
