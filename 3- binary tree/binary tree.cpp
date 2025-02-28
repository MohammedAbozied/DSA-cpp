#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<cassert>
#include<string>

using namespace std;

 
class BinaryTree {

private:

    struct TreeNode {
        int val{ };
        TreeNode* left{ };
        TreeNode* right{ };
        TreeNode(int val) : val(val) { }
    };
    TreeNode* root{ };
    
	void _print_in_order(TreeNode* root)
	{
		if (!root)
			return;

		_print_in_order(root->left);
		cout << root->val << " ";
		_print_in_order(root->right);
	}

	int _max_value(TreeNode* root)
	{
		if (!root)
			return 0;

		int sub = max(_max_value(root->left), _max_value(root->right));
		return max(root->val, sub);
	}

	bool isLeaf(TreeNode* node)
	{
		return (node && !node->left && !node->right);
	}

	int _maxDepth(TreeNode* root)
	{
		if (!root)
			return 0;

		return 1 + max(_maxDepth(root->left), _maxDepth(root->right));
	}

	bool _hasPathSum(TreeNode* root, int targetSum)
	{
		if (!root)
			return false;

		if (isLeaf(root) && targetSum == root->val)
			return true;

		return _hasPathSum(root->left, targetSum - root->val) ||
			_hasPathSum(root->right, targetSum - root->val);

	}

	int _sumOfLeftLeaves(TreeNode* root)
	{
		if (!root)
			return 0;

		int sum = 0;

		if (isLeaf(root->left))
			sum += root->left->val;

		sum += _sumOfLeftLeaves(root->left);
		sum += _sumOfLeftLeaves(root->right);


		return sum;


	}

	bool _is_perfect(TreeNode* root, int h) {
		if (isLeaf(root))
			return h == 0;	

		if (!root->left && root->right || root->left && !root->right)
			return false;	

		return _is_perfect(root->left, h - 1) && _is_perfect(root->right, h - 1);
	}

	// represent Binary tree in string way 
	string _parenthesize(TreeNode* root)
	{
		if (!root)
			return "()";

		string repr = "(" + to_string(root->val);

		if (root->left)
			repr += _parenthesize(root->left);
		else
			repr += "()";

		if (root->right)
			repr += _parenthesize(root->right);
		else
			repr += "()";

		repr += ")";

		return repr;

	}

	int max_diameter_so_far = 0;

	int _height(TreeNode* root) {
		if (!root)
			return 0;

		int left_height = _height(root->left);
		int right_height = _height(root->right);

		max_diameter_so_far = max(max_diameter_so_far, left_height + right_height);

		return 1 + max(left_height, right_height);
	}

	bool _is_complete(TreeNode* root, int height) {
		if (!root)
			return true;

		if (isLeaf(root))
			return height == 0;

		if (height == 1) {
			if (!root->left && root->right)
				return false;
			return true;
		}

		if ((root->left && !root->right) || (!root->left && root->right))
			return false;

		return _is_complete(root->left, height - 1) &&
			_is_complete(root->right, height - 1);
	}


public:

    BinaryTree(int root_value) :
        root(new TreeNode(root_value)) {}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		TreeNode* current = this->root;

		for (int i = 0; i < (int)values.size(); ++i) {
			if (direction[i] == 'L') {
				if (!current->left)
					current->left = new TreeNode(values[i]);
				else
					assert(current->left->val == values[i]);
				current = current->left;
			}
			else {
				if (!current->right)
					current->right = new TreeNode(values[i]);
				else
					assert(current->right->val == values[i]);
				current = current->right;
			}
		}
	}

	// easy homeWork
	void print_in_order()
	{
		_print_in_order(root);
		cout << "\n";
	}

	int max_value()
	{
		return _max_value(root);
	}
	
	int maxDepth()
	{
		return _maxDepth(root);
	}

	bool hasPathSum(int targetSum)
	{
		return _hasPathSum(root, targetSum);
	}

	int sumOfLeftLeaves()
	{
		return _sumOfLeftLeaves(root);
	}

	bool isPerfect()
	{
		return _is_perfect(root, maxDepth()-1);
	}

	void level_order_traversal() {
		queue<TreeNode*> nodes_queue;
		nodes_queue.push(root);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout << "Level " << level << ": ";
			while (sz--) {
				TreeNode* cur = nodes_queue.front();
				nodes_queue.pop();

				cout << cur->val << " ";
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
			cout << "\n";
		}
	}

	string parenthesize()
	{
		return _parenthesize(root);
	}

	int diameterOfBinaryTree()
	{
		if (!root)
			return 0;
		_height(root);
		return max_diameter_so_far;
	}

	// height based on edges between nodes
	int height()
	{
		return _height(root)-1;
	}

	bool is_complete()
	{
		return _is_complete(root, height());
	}


};

int main()
{
	BinaryTree tree(1);
	tree.add({ 2, 4}, { 'L', 'L'});
	tree.add({ 2, 5}, { 'L', 'R'});
	//tree.add({ 2, 5}, { 'L', 'R'});
	tree.add({ 3, 6}, { 'R', 'L'});

	tree.print_in_order();
	cout<<tree.is_complete();
}