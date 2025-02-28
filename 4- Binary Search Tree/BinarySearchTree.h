#pragma once
#include<iostream>
#include<vector>
#include<cassert>
#include <limits>
using namespace std;


struct TreeNode
{
	TreeNode* left{};
	TreeNode* right{};
	int val{};

	
	TreeNode(int val) :val(val) {};
	TreeNode(TreeNode* left, TreeNode* right, int val) :
		val(val), left(left), right(right) {};

};


class BinarySearchTree
{

private:
	
	TreeNode* root;

	// usually in recursion 'Modification Functions(insert\delete)' which return TreeNode , we return root in end (don't ask why ).
	TreeNode* _insert(TreeNode* root ,int value)
	{
		if (!root)
			return new TreeNode(value);

		if (value < root->val)
			root->left =  _insert(root->left, value);

		else if(value > root->val)
			root->right = _insert(root->right, value);

		return root;
	}

	void _print_inOrder(TreeNode* root)
	{
		if (!root)
			return;

		_print_inOrder(root->left);
		cout << root->val << " ";
		_print_inOrder(root->right);

	}

	
	int _height(TreeNode* root)
	{
		if (!root)
			return 0;

		return 1 + max(_height(root->left), _height(root->right));

	}

	bool _is_balanced(TreeNode* root,int height) 
	{
		if (!root)
			return true;

		if (is_leaf(root))
			return height == 0 || height == 1;

		return _is_balanced(root->left,height-1) && _is_balanced(root->right,height-1);
	}

	static TreeNode* _sortedArrayToBST(vector<int>& nums, int start , int end)
	{
		if (start > end)
			return nullptr;

		int mid = start + (end - start) / 2;
		TreeNode* root = new TreeNode(nums[mid]);

		root->left  = _sortedArrayToBST(nums, start, mid - 1);
		root->right = _sortedArrayToBST(nums, mid + 1, end);

		return root;

	}

	TreeNode* _lowestCommonAncestor(TreeNode* root,int p, int q)
	{
		if (!root)
			return nullptr;

		if (root->val > p && root->val > q)
			return _lowestCommonAncestor(root->left, p, q);

		if (root->val < p&& root->val < q)
			return _lowestCommonAncestor(root->right, p, q);

		return root;

	}

	TreeNode* _searchBST(TreeNode* root, int val)
	{
		if (!root)
			return nullptr;

		if (root->val == val)
			return root;

		if (root->val > val)
			return _searchBST(root->left, val);

		return _searchBST(root->right, val);

	}

	pair<TreeNode*, TreeNode*> _treeToDoublyListTraversal(TreeNode* root) {
		if (!root)
			return { nullptr, nullptr };

		pair<TreeNode*, TreeNode*> left = _treeToDoublyListTraversal(root->left);
		pair<TreeNode*, TreeNode*> right = _treeToDoublyListTraversal(root->right);

		TreeNode* first = root;	
		TreeNode* last = root;

		if (left.first) {
			left.second->right = root;
			root->left = left.second;
			first = left.first;
		}
		if (right.first) { 
			root->right = right.first;
			right.first->left = root;
			last = right.second;
		}
		return { first, last };
	}

	int _minValue(TreeNode* root)
	{
		if (!root->left)
			return root->val;

		return _minValue(root->left);
	}

	bool find_chain(TreeNode* root, int target, vector<TreeNode*>& ancestors) {
		ancestors.push_back(root);

		if (target == root->val)
			return true;

		if (target < root->val)
			return find_chain(root->left, target, ancestors);

		return root->right && find_chain(root->right, target, ancestors);
	}

	TreeNode* get_next(vector<TreeNode*>& ancestors) {
		if (ancestors.size() == 0)
			return nullptr;
		TreeNode* node = ancestors.back();	
		ancestors.pop_back();
		return node;
	}

	pair<bool, int> successor(int target) {
		vector<TreeNode*> ancestors;

		if (!find_chain(root, target, ancestors))	
			return make_pair(false, -1);

		TreeNode* child = get_next(ancestors);

		if (child->right)	
			return make_pair(true, _minValue(child->right));

		TreeNode* parent = get_next(ancestors);
		
		while (parent && parent->right == child)
			child = parent, parent = get_next(ancestors);

		if (parent)	
			return make_pair(true, parent->val);

		return make_pair(false, -1);
	}

	TreeNode* _minNode(TreeNode* root)
	{
		if (!root)
			return nullptr;

		if (!root->left)
			return root;

		return _minNode(root->left);
	}

	TreeNode* _delete_node(TreeNode* root, int target)
	{
		if (!root)
			return nullptr;
		if (target < root->val)
			root->left = _delete_node(root->left, target);
		else if (target > root->val)
			root->right = _delete_node(root->right, target);

		//target == root->val
		else {	
			TreeNode* tmp = root;
			
			// if root is leaf
			if (!root->left && !root->right)	
				root = nullptr;
			else if (!root->right) 				
				root = root->left;				
			else if (!root->left)				
				root = root->right;
			else {								
				TreeNode* mn = _minNode(root->right);
				root->val = mn->val;	
				root->right = _delete_node(root->right, root->val);
				tmp = nullptr;	//don't delete the node in the next condition
			}

			if (tmp)
				delete tmp;
		}
		return root;
	}


	

	static bool _isValidBST(TreeNode* root,long long min, long long max)
	{
		if (!root)
			return true;

		if (root->val <= min || root->val >= max)
			return false;

		return _isValidBST(root->left,min,root->val) &&
			_isValidBST(root->right,root->val, max);
	}

	
	


public:

	BinarySearchTree(int val) :root(new TreeNode(val)) {};

	BinarySearchTree(TreeNode* root):root(root) {};

	bool is_leaf(TreeNode* root)
	{
		return root && !root->left && !root->right;
	}

	int get_root()
	{
		return root->val;
	}

	void insert(int value)
	{
		root = _insert(root, value);
	}

	void print_inOrder()
	{
		_print_inOrder(root);
	}

	int height()
	{
		return _height(root) -1 ;
	}

	bool is_balanced()
	{
		return _is_balanced(root, height());
	}

	static BinarySearchTree* sortedArrayToBST(vector<int>& nums)
	{
		return (new BinarySearchTree(_sortedArrayToBST(nums, 0, (int)nums.size()-1)));
	}

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		return _lowestCommonAncestor(root, p->val, q->val);
	};
	
	TreeNode* lowestCommonAncestor(TreeNode* root, int p, int q)
	{
		return _lowestCommonAncestor(root, p, q);
	};

	TreeNode* searchBST(int val)
	{
		return _searchBST(root, val);
	}

	TreeNode* treeToDoublyList(TreeNode* root) {
		if (!root)
			return root;

		pair<TreeNode*, TreeNode*> dll = _treeToDoublyListTraversal(root);
		dll.first->left = dll.second;
		dll.second->right = dll.first;

		return dll.first;
	}

	int minValue()
	{
		assert(root);
		return _minValue(root);
	}

	void delete_node(int target) 
	{
		root = _delete_node(root, target);
	}
	
	static bool isValidBST(TreeNode* root)
	{
		return _isValidBST(root, numeric_limits<long long>::min(), numeric_limits<long long>::max());
	}

};

