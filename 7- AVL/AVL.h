#pragma once
#include<iostream>

using namespace std;

class AVLTree
{
private:

	int data{};
	int height{};
	AVLTree* left{};
	AVLTree* right{};

public:

	AVLTree() {};
	AVLTree(int data) :data(data) {};

	int ch_height(AVLTree* Node)
	{
		return (!Node ? -1 : Node->height); // return =1 for Null , 0 for leaf
	}

	int Update_height() 
	{
		return 1 + max(ch_height(left), ch_height(right));
	}

	int Balance_Factor()
	{
		return ch_height(left) - ch_height(right);
	}

	AVLTree* left_rotation(AVLTree* Node)
	{
		AVLTree* rightNode = Node->right;   
		Node->right = rightNode->left;
		rightNode->left = Node;

		Node->Update_height();
		rightNode->Update_height();

		return rightNode;
	}

	AVLTree* right_rotation(AVLTree* Node)
	{
		AVLTree* leftNode = Node->left;
		Node->left = leftNode->right;
		leftNode->right = Node;

		Node->Update_height();
		leftNode->Update_height();

		return leftNode;
	}




};

