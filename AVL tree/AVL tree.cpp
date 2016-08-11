// AVL tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
struct avl {
	struct avl *link[2];
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
	int get_height(avl* root) {
		if (!root)
			return 0;
		return root->height;
	}
	int get_bal(avl* root) {
		return get_height(root->link[0]) - get_height(root->link[1]);
	}
	int update_height(avl* root) {
		return max(get_height(root->link[0]), get_height(root->link[1]))+1;
	}
	avl* single_rotate(avl *root,int dir) {
		avl *node = root->link[dir];
		root->link[dir] = node->link[!dir];
		node->link[!dir] = root;

		root->height=update_height(root);
		node->height=update_height(node);
		return node;
	}
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
				if (bal < 0) {
					root = single_rotate(root, dir);
				}
				else {
					root = double_rotate(root, dir);
				}
			}
			else if (get_bal(root) > 1) {
				int bal = get_bal(root->link[dir]);
				if (bal > 0)
					root=single_rotate(root, dir);
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
	Solution s;
	avl* root = NULL;

	for (auto i : v) {
		root = s.insert_avl(root, i);
	}

    return 0;
}

