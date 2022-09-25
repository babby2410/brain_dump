#include <iostream>

using namespace std;

struct TreeNode {
    TreeNode(int x) {
        this->val = x;
        this->left = NULL;
        this->right = NULL;
    }

    TreeNode(int x, TreeNode* l, TreeNode* r) {
        this->val = x;
        this->left = l;
        this->right = r;
    }

    int val;
    TreeNode* left;
    TreeNode* right;
};

bool checkBSTUtil(TreeNode *root, TreeNode* leftLimit, TreeNode* rightLimit) {
    if (!root)
        return true;

    if (leftLimit && root->val <= leftLimit->val || rightLimit && root->val >= rightLimit->val)
        return false;

    return checkBSTUtil(root->left, leftLimit, root) &&
            checkBSTUtil(root->right, root, rightLimit);
}

bool checkBST(TreeNode *root) {
    return checkBSTUtil(root, NULL, NULL);
}

int main() {

    TreeNode *root = new TreeNode(13);
    root->left = new TreeNode(8);
    root->left->left = new TreeNode(6);

    root->left->right = new TreeNode(10);
    root->left->right->left = new TreeNode(9);
    root->left->right->right = new TreeNode(12);

    if (checkBST(root)) {
        cout << "Given tree is a valid BST" << "\n";
    }
    else {
        cout << "Given tree is not a valid BST" << "\n";
    }

    return 0;
}
