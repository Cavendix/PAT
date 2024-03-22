#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 红黑树节点结构体
struct Node {
    int key;
    char color; // 'R'表示红色，'B'表示黑色
    Node* left;
    Node* right;
    Node* parent;

    Node(int k, char c) : key(k), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

// 左旋操作
void left(Node*& root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// 右旋操作
void right(Node*& root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// 插入修正操作
void fixup(Node*& root, Node* z) {
    while (z != root && z->parent->color == 'R') {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;

            if (y != nullptr && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                right(root, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != nullptr && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                left(root, z->parent->parent);
            }
        }
    }
    root->color = 'B';
}

// 插入节点
void insert(Node*& root, int key) {
    Node* z = new Node(key, 'R');
    Node* y = nullptr;
    Node* x = root;
    while (x != nullptr) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    fixup(root, z);
}

// 中序遍历
void inorder(Node* root) {
    if (root == nullptr)
        return;
    inorder(root->left);
    printf("%d %c ",root->key,root->color);
    inorder(root->right);
}

// 先序遍历
void preorder(Node* root) {
    if (root == nullptr)
        return;
    printf("%d %c ",root->key,root->color);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    int T;
    cin >> T;

    Node* root = nullptr;

    for (int i = 0; i < T; ++i) {
        char operation[6];
        int key;
        scanf("%s%d",&operation,&key);

        if (operation[0] == 'I')
            insert(root, key);
    }

    inorder(root);

    cout << endl;

    preorder(root);

    cout << endl;
    cout << endl;

    return 0;
}
