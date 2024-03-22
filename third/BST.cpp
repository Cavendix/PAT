#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 定义二叉查找树节点结构
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 向二叉查找树中插入节点
/*TreeNode* insertNode(TreeNode* root, int key) {
    if (root == nullptr) { // 如果树为空，则创建新节点作为根节点
        return new TreeNode(key);
    }
    if (key < root->val) { // 如果关键词小于当前节点值，则插入左子树
        root->left = insertNode(root->left, key);
    } else if (key > root->val) { // 如果关键词大于当前节点值，则插入右子树
        root->right = insertNode(root->right, key);
    }
    return root;
}*/

TreeNode* insertNode(TreeNode* root, int key) {
    if (root == nullptr) { // 如果树为空，则创建新节点作为根节点
        return new TreeNode(key);
    }
    
    TreeNode* current = root;
    TreeNode* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (key < current->val) { // 如果关键词小于当前节点值，则插入左子树
            current = current->left;
        } else if (key > current->val) { // 如果关键词大于当前节点值，则插入右子树
            current = current->right;
        } else { // 如果关键词已存在，则不进行插入操作
            return root;
        }
    }

    // 创建新节点，并根据关键词的大小关系插入到父节点的左子树或右子树
    TreeNode* newNode = new TreeNode(key);
    if (key < parent->val) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

// 从二叉查找树中删除节点
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) { // 如果树为空，直接返回
        return nullptr;
    }
    if (key < root->val) { // 如果关键词小于当前节点值，则在左子树中删除
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) { // 如果关键词大于当前节点值，则在右子树中删除
        root->right = deleteNode(root->right, key);
    } else { // 找到了要删除的节点
        if (root->left == nullptr) { // 如果左子树为空，则将右子树提上来
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) { // 如果右子树为空，则将左子树提上来
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // 如果左右子树都不为空，则找到右子树中最小的节点来替换当前节点
        TreeNode* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        root->val = temp->val; // 替换值
        root->right = deleteNode(root->right, temp->val); // 在右子树中删除最小节点
    }
    return root;
}

// 中序遍历二叉查找树
void inOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->left);
    printf("%d ",root->val);
    inOrderTraversal(root->right);
}

// 先序遍历二叉查找树
void preOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    printf("%d ",root->val);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

int main() {
    int T;
    cin >> T;

    TreeNode* root = nullptr; // 初始化根节点为空

    // 循环处理每个操作
    for (int i = 0; i < T; ++i) {
        char operation[6];
        int key;
        scanf("%s%d",&operation,&key);

        if (operation[0] == 'I') {
            root = insertNode(root, key); // 插入节点
        } else if (operation[0] == 'R') {
            root = deleteNode(root, key); // 删除节点
        }
    }

    // 中序遍历
    inOrderTraversal(root);

    cout << endl << endl;
    // 先序遍历
    preOrderTraversal(root);

    cout << endl;
    cout << endl;

    return 0;
}
