#pragma once
#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

class Max_Heap
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
        return child_pos == 0 ? -1 : ((child_pos - 1) / 2);
    }

    void heapify_up(int child_pos)// using in push (log n)
    {
        int par_pos = parent_pos(child_pos);

        if (child_pos == 0 || array[par_pos] > array[child_pos])
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

        if (right != -1 && array[right] > array[child_pos])
            child_pos = right;

        if (array[par_pos] < array[child_pos])
        {
            swap(array[par_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }


public:

    Max_Heap(int Capacity)
    {
        this->Capacity = Capacity;
        array = new int[this->Capacity];
        size = 0;
    }

    ~Max_Heap()
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



};