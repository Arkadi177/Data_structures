#include <iostream>
#include <stack>
template <class T>
struct TreeNode{
    T m_data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode<T>* parent;
    explicit TreeNode(T data)
            : m_data{data} , left(nullptr) , right(nullptr) , parent(nullptr)
    {}
    explicit TreeNode()
            : left(nullptr) , right(nullptr) , parent(nullptr)
    {}
    explicit TreeNode(TreeNode<T>* other)
    {
        this->m_data = other->m_data;
        this->left = other->left;
        this->right = other->right;
        this->parent = other->parent;
    }
};
template <class T>
void postorder(TreeNode<T>* root){
    std::stack<TreeNode<T>*> stack1;
    std::stack<TreeNode<T>*> stack2;
    stack1.push(root);
    while(!stack1.empty())
    {
        TreeNode<T>* temp = stack1.top();
        stack1.pop();
        stack2.push(temp);
        if(temp->left)
        {
            stack1.push(temp->left);
        }
        if(temp->right)
        {
            stack1.push(temp->right);
        }
    }
    while(!stack2.empty())
    {
        std::cout << stack2.top()->m_data << " ";
        stack2.pop();
    }
    std::cout << std::endl;
}
template <class T>
void postorder_parent(TreeNode<T>* root){
    TreeNode<T>* new_root = new TreeNode<T>(root);
    while(new_root)
    {
        while(new_root->left){
            new_root = new_root->left;
        }
        std::cout << new_root->m_data << " ";
        if(new_root->parent && new_root->parent->right != nullptr && new_root != new_root->parent->right)
        {
            new_root = new_root->parent->right;
            new_root->parent->left = nullptr;
        }else{
            new_root = new_root->parent;
            if(new_root) {
                new_root->left = nullptr;
            }
        }
    }
    delete new_root;
}
template <class T>
void deleteTree(TreeNode<T>* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    TreeNode<char>* node1 = new TreeNode<char>('A');
    node1->left = new TreeNode<char>('B');
    node1->left->parent = node1;
    node1->left->left = new TreeNode<char>('D');
    node1->left->left->parent = node1->left;
    node1->right = new TreeNode<char>('C');
    node1->right->parent = node1;
    node1->right->left = new TreeNode<char>('E');
    node1->right->left->parent = node1->right;
    node1->right->left->left = new TreeNode<char>('G');
    node1->right->left->left->parent = node1->right->left;
    node1->right->right = new TreeNode<char>('F');
    node1->right->right->parent = node1->right;
    node1->right->right->left = new TreeNode<char>('H');
    node1->right->right->left->parent = node1->right->right;
    node1->right->right->right = new TreeNode<char>('I');
    node1->right->right->right->parent = node1->right->right;

    postorder(node1);
    postorder_parent(node1);

    deleteTree(node1);
}