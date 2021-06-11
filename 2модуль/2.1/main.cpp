#include <iostream>
#include <stack>

template<class T>
class LeftMoreOrEqualThanRight {
public:
    bool operator()(const T &l, const T &r) {
        return l >= r;
    }
};

template<typename T, class Comparator = std::less<T>>
class Tree {
public:
    struct Node {
        explicit Node(const T &data) : data(data), left(nullptr), right(nullptr) {}
        T data;
        Node *left, *right;
    };

    Tree() : root(nullptr) {

    }

    ~Tree() {
        auto f = &Tree::deleteElement;
        this->inOrderTraversal(f);
    }

    void Add(const T &data) {
        root = addNode(root, data);
    }


    void inOrderTraversal(void (Tree::*f)(Node *node)) {
        std::stack<Node *> treeStack;
        Node *curr = root;
        while (curr != nullptr || treeStack.empty() == false) {
            while (curr != nullptr) {
                treeStack.push(curr);
                curr = curr->left;
            }
            curr = treeStack.top();
            treeStack.pop();
            (this->*f)(curr);
            curr = curr->right;
        }
    }

    void print() {
        auto f = &Tree::printElement;
        this->inOrderTraversal(f);
    }

private:
    Node *root;
    Comparator cmp;


    void printElement(Node *node) {
        std::cout << node->data << std::endl;
    };


    void deleteElement(Node *node) {
        delete node;
    }

    Node *addNode(Node *node, const T &data) {
        if (!node)
            return new Node(data);
        Node *start = node;
        while ((node->right != nullptr && cmp(data, node->data)) || (node->left != nullptr && !cmp(data, node->data))) {
            if (cmp(data, node->data))
                node = node->right;
            else
                node = node->left;
        }
        if (cmp(data, node->data))
            node->right = new Node(data);
        else
            node->left = new Node(data);
        node = start;
        return node;
    }
//    void deleteTree() {
//        std::stack<Node *> s;
//        Node *curr = root;
//        while (curr != nullptr || s.empty() == false) {
//            while (curr != nullptr) {
//                s.push(curr);
//                curr = curr->left;
//            }
//            curr = s.top();
//            s.pop();
//            Node *buff = curr;
//            curr = buff->right;
//            buff->right = nullptr;
//            buff->left = nullptr;
//        }
//    }
};


int main() {
    Tree<int, LeftMoreOrEqualThanRight<int>> tree;
    int n, elem;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> elem;
        tree.Add(elem);
    }
    tree.print();
    return 0;
}