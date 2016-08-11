#include "stdafx.h"
#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
struct avl {
	struct avl *link[2];//using this pointer instead of left and right and handle symmetric cases. 0 indicates left and 1 indicates right.
	int val;
	int height;
	avl(int x) {
		link[0] = NULL;
		link[1] = NULL;
		val = x;
		height = 1;
	}
};

class Solution {
public:
	//To return height of a node.
	int get_height(avl* root) {
		if (!root)
			return 0;
		return root->height;
	}
	//To return the balance value of a particular node.

	int get_bal(avl* root) {
		return get_height(root->link[0]) - get_height(root->link[1]);
	}

	//To calculate height of a particular node.
	int update_height(avl* root) {
		return max(get_height(root->link[0]), get_height(root->link[1]))+1;
	}

	//Single rotation.
	avl* single_rotate(avl *root,int dir) {
		avl *node = root->link[dir];
		root->link[dir] = node->link[!dir];
		node->link[!dir] = root;

		root->height=update_height(root);
		node->height=update_height(node);
		return node;
	}

	//Double Rotation.
	avl* double_rotate(avl* root, int dir) {
		root->link[dir] = single_rotate(root->link[dir], !dir);
		return single_rotate(root, dir);
	}
	
	avl* insert_avl(avl *root,int data) {
		if (!root) {
			root = new avl(data);
			root->height=update_height(root);
		}
		else
		{
			int dir = root->val < data;
			root->link[dir] = insert_avl(root->link[dir], data);
			root->height=update_height(root);
			if (get_bal(root) < -1) {
				int bal = get_bal(root->link[dir]);
				if (bal < 0) { //left-left balance
					root = single_rotate(root, dir);
				}
				else { //left right balance
					root = double_rotate(root, dir);
				}
			}
			else if (get_bal(root) > 1) {
				//right right balance
				int bal = get_bal(root->link[dir]);
				if (bal > 0)
					root=single_rotate(root, dir);
				//right left balance
				else
					root=double_rotate(root, dir);
			}
		}
		return root;
	}
};

int main()
{
	vector<int> v{ 10,5,80,90,85,8,4,6,7 };
	//This is an example of the several vector values which I used while testing, this code works for any integer input and self balances.
	Solution s;
	avl* root = NULL;

	for (auto i : v) {
		root = s.insert_avl(root, i);
	}

    return 0;
}
