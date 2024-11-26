#include <iostream>

struct TreeNode{
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    explicit TreeNode(int val = 0)
            : value(val) , left(nullptr) , right(nullptr) , parent(nullptr){}
    explicit TreeNode(TreeNode* other)
    {
        this->value = other->value;
        this->left = other->left;
        this->right = other->right;
        this->parent = other->parent;
    }
};

TreeNode* find_place(TreeNode* root , const int val)
{
    if((root->right == nullptr && val >= root->value)
       || (root->left == nullptr && val <= root->value)){
        return root;
    }
    if(val < root->value)
    {
        return find_place(root->left , val);
    }else if (val > root->value){
        return find_place(root->right , val);
    }else{
        return nullptr;
    }
}

TreeNode* find_value(TreeNode* root , int val){
    if(root == nullptr)
    {
        return nullptr;
    }
    if(val < root->value)
    {
        return find_value(root->left , val);
    }else if(val > root->value)
    {
        return find_value(root->right , val);
    }
    return root;
}

TreeNode* get_min(TreeNode* root)
{
    if(root->left == nullptr)
    {
        return root;
    }
    return get_min(root->left);
}

TreeNode* get_max(TreeNode* root)
{
    if(root->right == nullptr)
    {
        return root;
    }
    return get_min(root->right);
}

void dfs(TreeNode* root)
{
    if(root == nullptr)
    {
        return;
    }
    std::cout << root->value << " ";
    dfs(root->left);
    dfs(root->right);
}

void deleteTree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

class Tree{
    TreeNode* nodes;
public:
    Tree(): nodes(nullptr) {}

    void insert(int val)
    {
        if(nodes == nullptr)
        {
            nodes = new TreeNode();
            nodes->value = val;
        }else{
            TreeNode* node = new TreeNode(val);
            TreeNode* temp = find_place(nodes , val);
            if(temp == nullptr)
            {
                return;
            }
            if(val < temp->value)
            {
                node->parent = temp;
                temp->left = node;
            }else if (val > temp->value){
                node->parent = temp;
                temp->right = node;
            }
        }
    }

    void remove(const int val){
        TreeNode* temp = find_value(nodes , val);
        if(temp == nullptr)
        {
            perror("Value don't found: " );
            return;
        }
        if(temp->left == nullptr && temp->right == nullptr)
        {
            if(temp->parent->left->value == temp->value)
            {
                temp->parent->left = nullptr;
            }else{
                temp->parent->right = nullptr;
            }
            return;
        }
        TreeNode *min_max = temp->left != nullptr ? get_max(temp->left) : get_min(temp->right);
        int temp_val = min_max->value;
        min_max->value = temp->value;
        temp->value = temp_val;
        if(min_max->parent->left->value == min_max->value)
        {
            min_max->parent->left = nullptr;
        }else{
            min_max->parent->right = nullptr;
        }
    }

    TreeNode* get()
    {
        return nodes;
    }

    ~Tree(){
        deleteTree(nodes);
    }
};
//insert(40); insert(20); insert(10); insert(30);
//insert(50); insert(60); insert(40); insert(70);
//insert(55);

int main() {
    Tree car;

    car.insert(40);
    car.insert(20);
    car.insert(10);
    car.insert(30);
    car.insert(50);
    car.insert(60);
    car.insert(40);
    car.insert(70);
    car.insert(55);

    dfs(car.get());
    std::cout << std::endl;

    car.remove(70);
    car.remove(60);
    car.remove(40);

    dfs(car.get());

    return 0;
}
