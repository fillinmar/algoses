/*
 АВЛ-дерево. Порядковые статистики.
*/

#include <iostream>

template<typename T>
class AvlTree {
    struct Node {
        Node(const T &data) : data(data), left(nullptr), right(nullptr), height(1), weight(1) {}
        T data;
        Node *left, *right;
        size_t height;
        size_t weight;
    };
public:
    AvlTree() : root(nullptr) {}
    ~AvlTree() {
        destroyTree(root);
    }
    bool Has(const T &data) {
        Node *temp = root;
        while (temp) {
            if (temp->data == data)
                return true;
            else if (temp->data >= data)
                temp = temp->left;
            else
                temp = temp->right;
        }
        return false;
    }
    void Add(const T &data) {
        root = addInternal(root, data);
    }
    void Remove(const T &data) {
        root = removeInternal(root, data);
    }
    int GetKStat(int index) {
        Node *temp = KStat(root, index);
        if (temp)
            return temp->data;
        else
            return 0;
    }

private:
    void fixHeight(Node *node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
    void fixWeight(Node *node) {
        node->weight = 1 + getWeight(node->left) + getWeight(node->right);
    }
    size_t getHeight(Node *node) {
        return node ? node->height : 0;
    }
    size_t getWeight(Node *node) {
        return node ? node->weight : 0;
    }
    int getBalance(Node *node) {
        return getHeight(node->right) - getHeight(node->left);
    }
    Node *rotateLeft(Node *node) {
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        fixHeight(node);
        fixHeight(temp);
        fixWeight(node);
        fixWeight(temp);
        return temp;
    }
    Node *rotateRight(Node *node) {
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        fixHeight(node);
        fixHeight(temp);
        fixWeight(node);
        fixWeight(temp);
        return temp;
    }
    Node *doBalance(Node *node) {
        fixHeight(node);
        fixWeight(node);

        switch(getBalance(node)) {
            case 2:
            {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2:
            {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }
    Node *addInternal(Node *node, const T &data) {
        if (!node)
            return new Node(data);
        if (node->data <= data)
            node->right = addInternal(node->right, data);
        else
            node->left = addInternal(node->left, data);
        return doBalance(node);
    }
    Node *RemoveMin(Node *node, Node **min) {
        if (!node->left) {
            *min = node;
            return node->right;
        }
        node->left = findAndRemoveMin(node->left, min);
        return doBalance(node);
    }
    Node *RemoveMax(Node *node, Node **max) {
        if (!node->right) {
            *max = node;
            return node->left;
        }
        node->right = findAndRemoveMax(node->right, max);
        return doBalance(node);
    }
    Node *removeInternal(Node *node, const T &data) {
        if (!node)
            return nullptr;
        if (node->data < data) {
            node->right = removeInternal(node->right, data);
        } else if (node->data > data) {
            node->left = removeInternal(node->left, data);
        } else {
            Node *left = node->left;
            Node *right = node->right;
            delete node;
            if (!left && !right)
                return nullptr;
            if (!right)
                return left;
            if (!left)
                return right;
            if (right->height >= left->height) {
                Node *min = nullptr;
                Node *temp1 = RemoveMin(right, &min);
                min->right = temp1;
                min->left = left;
                return doBalance(min);
            } else {
                Node *max = nullptr;
                Node *temp2 = RemoveMax(left, &max);
                max->left = temp2;
                max->right = right;
                return doBalance(max);
            }
        }
        return doBalance(node);
    }
    Node *KStat(Node *node, int index) {
        if (!node)
            return nullptr;
        int delta = index - getWeight(node->left);
        if (delta == 0)
            return node;
        else if (delta < 0)
            return KStat(node->left, index);
        else
            return KStat(node->right, delta - 1);
    }
    void destroyTree(Node *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node *root;
};

int main() {
    AvlTree<int> tree;

    int n;
    std::cin >> n;
    int element, k;
    for (int i = 0; i < n; ++i) {
        std::cin >> element >> k;
        if (element >= 0) {
            tree.Add(element);
            std::cout << tree.GetKStat(k) << std::endl;
        } else {
            tree.Remove(-element);
            std::cout << tree.GetKStat(k) << std::endl;
        }
    }
    return 0;
}
