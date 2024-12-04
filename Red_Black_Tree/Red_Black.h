#include <iostream>

enum Color {
    RED,
    BLACK
};

struct RBNode {
    int data;
    RBNode *left;
    RBNode *right;
    RBNode *parent;
    Color color;

    RBNode(int d, RBNode *l = nullptr, RBNode *r = nullptr, RBNode *p = nullptr, Color c = RED)
            : data(d), left(l), right(r), parent(p), color(c) {}
    void print() {
        std::cout << data << " ";
        std::cout << (color == RED ? "RED" : "BLACK");
    }

    void ReColor() {
        (color == RED ? color = BLACK : color = RED);
        return;
    }


};

RBNode* find_place(RBNode* root , const int val)
{
    if((root->right == nullptr && val >= root->data)
       || (root->left == nullptr && val <= root->data)){
        return root;
    }
    if(val < root->data)
    {
        return find_place(root->left , val);
    }else if (val > root->data){
        return find_place(root->right , val);
    }else{
        return nullptr;
    }
}

class RBTree {
    RBNode *root = nullptr;

public:
    RBTree(RBNode *r = nullptr) : root(r) {}

    RBNode *search(int elem) {
        RBNode* temp = root;
        while(temp->data != elem)
        {
           if(elem > temp->data)
           {
               temp = temp->right;
           }else{
               temp = temp->left;
           }
        }
        return temp;
    };

    void bstInsert(RBNode* node) {
        // TODO write me (էս արած ունեք)
        if(root == nullptr)
        {
            root = node;
        }else{
            RBNode* temp = find_place(root , node->data);
            if(temp == nullptr)
            {
                return;
            }
            if(node->data < temp->data)
            {
                node->parent = temp;
                temp->left = node;
            }else if (node->data > temp->data){
                node->parent = temp;
                temp->right = node;
            }
        }
    }
    void insert(int elem) {
        // bstree insert

        RBNode *x = new RBNode(elem);

        if (root == nullptr) {
            x->color = BLACK;
            root = x;
            return;
        }

        bstInsert(x);

        insertFixup(x);

        // fixup
    };

    void insertFixup(RBNode *node) {
        while (true) {
            if(node->parent == nullptr)
            {
                node->color = BLACK;
                return;
            }else if(node->parent->color != RED)
            {
                break;
            }
            if (node->parent == node->parent->parent->left) {
                RBNode *uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if(node == node->parent->right)
                    {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else{
                RBNode *uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if(node == node->parent->left)
                    {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }

    };

    void leftRotate(RBNode *node) {
        RBNode *y = node->right;
        node->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = node;
        }
        y->parent = node->parent;
        if (node->parent == nullptr) {
            root = y;
        } else if (node == node->parent->left) {
            node->parent->left = y;
        } else {
            node->parent->right = y;
        }

        y->left = node;
        node->parent = y;

    };

    void rightRotate(RBNode *node){
        RBNode* temp = node->left;
        node->left = temp->right;
        if(temp->right != nullptr)
        {
            temp->right->parent = node;
        }
        temp->parent = node->parent;
        if(node->parent == nullptr)
        {
            root = temp;
        }else if(node->parent->left == node)
        {
            node->parent->left = temp;
        }else{
            node->parent->right = temp;
        }
        temp->right = node;
        node->parent = temp;
    }

};