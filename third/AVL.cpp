#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// AVL树节点结构体
struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

// 获取节点高度
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// 更新节点高度
void updateHeight(Node* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// 获取节点平衡因子
int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 右旋转操作
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // 执行旋转
    x->right = y;
    y->left = T2;

    // 更新节点高度
    updateHeight(y);
    updateHeight(x);

    return x;
}

// 左旋转操作
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // 执行旋转
    y->left = x;
    x->right = T2;

    // 更新节点高度
    updateHeight(x);
    updateHeight(y);

    return y;
}

// 插入节点
Node* insert(Node* root, int key) {
    if (root == nullptr)
        return new Node(key);

    // 插入节点
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else // 如果节点已存在，不做操作
        return root;

    // 更新节点高度
    updateHeight(root);

    // 平衡树
    int balance = getBalanceFactor(root);

    // 左边更重，需要右旋
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // 右边更重，需要左旋
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // 左右不平衡，左子树比较重，需要先左旋再右旋
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // 左右不平衡，右子树比较重，需要先右旋再左旋
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// 查找节点中最小值
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// 删除节点
Node* remove(Node* root, int key) {
    if (root == nullptr)
        return root;

    // 执行删除
    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    else {
        // 找到要删除的节点
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        } else {
            Node* temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = remove(root->right, temp->key);
        }
    }

    // 如果树为空，则直接返回
    if (root == nullptr)
        return root;

    // 更新节点高度
    updateHeight(root);

    // 平衡树
    int balance = getBalanceFactor(root);

    // 左边更重，需要右旋
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // 右边更重，需要左旋
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // 左右不平衡，左子树比较重，需要先左旋再右旋
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // 左右不平衡，右子树比较重，需要先右旋再左旋
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// 中序遍历二叉查找树
void inOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->left);
    printf("%d ",root->key);
    inOrderTraversal(root->right);
}

// 先序遍历二叉查找树
void preOrderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    printf("%d ",root->key);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

int main() {
    int T;
    cin >> T;

    Node* root = nullptr; // 初始化根节点为空

    // 循环处理每个操作
    for (int i = 0; i < T; ++i) {
        char operation[6];
        int key;
        scanf("%s%d",&operation,&key);

        if (operation[0] == 'I') {
            root = insert(root, key); // 插入节点
        } else if (operation[0] == 'R') {
            root = remove(root, key); // 删除节点
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
