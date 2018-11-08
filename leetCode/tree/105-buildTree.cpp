#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x)
		: val(x),
		  left(nullptr),
		  right(nullptr)
	{}
};

class Solution
{
public:
	// redo: 用指针代替使用栈空间
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		if (preorder.size() == 0 or inorder.size() == 0)
		{
			return nullptr;
		}

		TreeNode *root = new TreeNode(preorder[0]);

		auto target = find(inorder.begin(), inorder.end(), preorder[0]);
		if (target == inorder.end())
		{
			return root;
		}

		int distanceStep = distance(inorder.begin(), target);
		if (distanceStep != 0)
		{
			vector<int> leftPre(preorder.begin() + 1, preorder.begin() + distanceStep +1);
			vector<int> leftIn(inorder.begin(), inorder.begin() + distanceStep);
			root->left = buildTree(leftPre, leftIn);
		}

		vector<int> rightPre(preorder.begin() + distanceStep + 1, preorder.end());
		vector<int> rightIn(inorder.begin() + distanceStep + 1, inorder.end());
		root->right = buildTree(rightPre, rightIn);

		return root;
	}
};

void printBinaryTree(TreeNode* root)
{
	if (root->left)
	{
		printBinaryTree(root->left);
	}

	cout << root->val << ' ';

	if (root->right)
	{
		printBinaryTree(root->right);
	}
}

int main(int argc, char* argv[])
{
	Solution solution;
	vector<int> preorder{3, 9, 20, 15, 7};
	vector<int> inorder{9, 3, 15, 20, 7};

	auto ptr = solution.buildTree(preorder, inorder);
	printBinaryTree(ptr);
	puts("");

	preorder = {1, 2};
	inorder = {1, 2};
	ptr = solution.buildTree(preorder, inorder);
	printBinaryTree(ptr);
	puts("");

	preorder = {1, 2};
	inorder = {2, 1};
	ptr = solution.buildTree(preorder, inorder);
	printBinaryTree(ptr);
	puts("");

}