#include <iostream>

template <typename T>
class AvlTree
{
    struct Node
    {
        Node(const T &key)
                : key(key), left(nullptr), right(nullptr), height(1)
        {
        }
        Node *left;
        Node *right;
        T key;
        size_t height;
    };
public:
    AvlTree()
            : root(nullptr)
    {
    }
    ~AvlTree()
    {
        destroyTree(root);
    }

    void Add(const T &key)
    {
        root = addInternal(root, key);
    }

    bool Has(const T &key)//елемент существует
    {
        Node *tmp = root;//временный указатель
        while (tmp)
        {
            if (tmp->key == key)
                return true;
            if (tmp->key < key)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        return false;
    }

    void Delete(const T &key)
    {
        root = deleteInternal(root, key);
    }

private:
    Node *root;

    Node* addInternal(Node *node, const T &key)
    {
        if (!node)
            return new Node(key);
        if (node->key <= key)
            node->right = addInternal(node->right, key);
        else
            node->left = addInternal(node->left, key);
        return doBalance(node);
    }

    Node* deleteInternal(Node *node, const T &key)
    {
        if (!node)
            return nullptr;
        if (node->key < key)
            node->right = deleteInternal(node->right, key);
        else if (node->key > key)
            node->left = deleteInternal(node->left, key);
        else
        {
            Node *left = node->left;//запоминаем потомков
            Node *right = node->right;
            delete node;

            if (!right)
                return left;

            // Нужно сравнить высоты поддеревьев left, right:
            // на место удаляемого узла можно поставить либо
            // максимальный из left, либо минимальный из
            // right. Нужно брать из того поддерева, чья
            // высота больше.

            // Логику findMin и removeMin нужно реализовать в
            // рамках одной функции:
            // findAndRemoveMin(right)
            // findAndRemoveMax(left)
            Node *min = findMin(right);
            min->right = removeMin(right);//удалить минимульный надо будет
            min->left = left;

            return doBalance(min);
        }
        return doBalance(node);//для всех родительских узлов
    }

    Node* findMin(Node *node)
    {
        while (node->left)
        {
            node = node->left;
        }
        return node;
    }

    Node* removeMin(Node *node)
    {
        if (!node->left)
            return node->right;
        node->left = removeMin(node->left);
        return doBalance(node);
    }

    Node* doBalance(Node *node)
    {
        fixHeight(node);//обновим значения высот в узле

        switch (getBalance(node))
        {
            case 2://правое поддерево отличается от левого
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

    //  a         b
    //   \       /
    //    b     a

    Node* rotateLeft(Node *node)
    {
        Node *tmp = node->right;//запоминаем правого потомка
        node->right = tmp->left;
        tmp->left = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

    Node* rotateRight(Node *node)
    {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

    size_t getHeight(Node *node)
    {
        return node ? node->height : 0;
    }

    void fixHeight(Node *node)
    {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalance(Node *node)
    {
        return getHeight(node->right) - getHeight(node->left);
    }

    void destroyTree(Node *node)
    {
        if (node)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
};

int main(int argc, const char * argv[]) {
    AvlTree<int> avlTree;

    char op;
    int key;
    while (std::cin >> op >> key)
    {
        switch (op)
        {
            case '+':
            {
                avlTree.Add(key);
                break;
            }
            case '-':
            {
                avlTree.Delete(key);
                break;
            }
            case '?':
            {
                std::cout << avlTree.Has(key) << std::endl;
                break;
            }
        }
    }
    return 0;
}
