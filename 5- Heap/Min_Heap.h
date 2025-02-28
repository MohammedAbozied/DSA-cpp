#pragma once
#include <iostream>
#include <queue>
#include <cassert>
#include <vector>
using namespace std;

class Min_Heap
{
    int* array{};
    int size{};
    int Capacity{};

    int left_pos(int parent_pos)
    {
        int pos = 2 * parent_pos + 1;
        return pos >= size ? -1 : pos;
    }

    int right_pos(int parent_pos)
    {
        int pos = 2 * parent_pos + 2;
        return pos >= size ? -1 : pos;
    }

    int parent_pos(int child_pos)
    {
        return child_pos == 0 ? -1 : (floor)((child_pos - 1) / 2);
    }

    void heapify_up(int child_pos)// using in push  (log n)
    {
        int par_pos = parent_pos(child_pos);

        if (child_pos == 0 || array[par_pos] <= array[child_pos])
            return;

        swap(array[child_pos], array[par_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int par_pos) // (log n)
    {
        int child_pos = left_pos(par_pos);
        int right = right_pos(par_pos);

        if (child_pos == -1) // no left child , then no right child
            return;

        if (right != -1 && array[right] < array[child_pos])
            child_pos = right;

        if (array[par_pos] > array[child_pos])
        {
            swap(array[par_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }

    void heapify() // (n)
    {	
        for (int i = size / 2 - 1; i >= 0; --i)
            heapify_down(i);
    }


public:
    Min_Heap() { }

    Min_Heap(int Capacity)
    {
        this->Capacity = Capacity;
        array = new int[this->Capacity];
        size = 0;
    }

    Min_Heap(const vector<int>& v,int Capacity = 1000) 
    {
        this->Capacity = Capacity;
        assert((int)v.size() <= this->Capacity);
        array = new int[this->Capacity] {};
        size = v.size();

        for (int i = 0; i < (int)v.size(); ++i)
            array[i] = v[i];

        heapify();
    }

    ~Min_Heap()
    {
        delete[]array;
        array = nullptr;
    }

    void push(int key)
    {
        assert(size + 1 <= Capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }

    int top()
    {
        assert(!is_empty());
        return array[0];
    }

    void pop()
    {
        assert(!is_empty());
        array[0] = array[--size];
        heapify_down(0);
    }

    bool is_empty()
    {
        return (size == 0);
    }



    void print_less_than(int value, int parent_pos = 0)
    {
        if (array[parent_pos] >= value || parent_pos == -1)
            return;

        cout << array[parent_pos] << " ";
        print_less_than(value, left_pos(parent_pos));
        print_less_than(value, right_pos(parent_pos));

    }

    bool is_heap_array(int parent_pos =0) {	// O(n)
        if (parent_pos == -1)
            return true;

        int left = left_pos(parent_pos);
        int right = right_pos(parent_pos);

        if (left != -1 && array[parent_pos] > array[left])
            return false;

        if (right != -1 && array[parent_pos] > array[right])
            return false;

        return is_heap_array(left) && is_heap_array(right);

    }


    void heap_sort(int* p, int n) {	// O(nlogn)
        if (n <= 1)
            return;

        int* old_arr = array;
        int old_size = size;

        size = n;
        array = p;

        heapify();	// O(n)

        while (size--) {	// O(nlogn)
            swap(array[0], array[size]);
            heapify_down(0);
        }

        // reverse
        for (int i = 0; i < n / 2; ++i)
            swap(array[i], array[n - i - 1]);

        size = old_size;
        array = old_arr;
    }



};
