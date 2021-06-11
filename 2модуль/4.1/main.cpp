
#include <iostream>

using namespace std;

template<class T>
class LeftMoreThanRight {
public:
    bool operator()(const T &l, const T &r) {
        return l > r;
    }
};

template<class T, class Comparator = less<T>>
class AVLTree {
    struct Node {
        explicit Node(const T &key)
                : key(key), left(nullptr), right(nullptr), height(1), weight(1) {}

        T key;
        Node *left;
        Node *right;
        int height;
        int weight;
    };

public:
    bool Search(const T &key) {
        return Find(key).first;
    }

    explicit AVLTree(const Comparator &compare = Comparator()) : root(nullptr), size(0) {};

    ~AVLTree() {
        destroyTree(root);
    }

    void Add(const T &key) {
        ++size;
        root = addInternal(root, key);
    }

    bool Delete(const T &key) {
        if (Search(key)) {
            root = deleteInternal(root, key);
            --size;
            return true;
        } else {
            return false;
        }
    };

    int Position(const T &key) {
        return positionTrail(root, key);
    }

    pair<bool, T> KStatistics(int index) {
        if (index >= size) {
            return make_pair(false, 0);
        }
        return make_pair(true, statisticsTrail(root, index));
    }

private:
    Node *root;
    int size;
    Comparator cmp;

    pair<bool, Node *> Find(const T &key) {
        Node *current = root;
        while (true) {
            if (current == nullptr) {
                return make_pair(false, nullptr);
            } else if (!(cmp(current->key, key)) && !(cmp(key, current->key))) {
                return make_pair(true, current);
            } else if (cmp(key, current->key)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }

    void destroyTree(Node *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    int weight(Node *node) {
        return node ? node->weight : 0;
    }

    int height(Node *node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node *node) {
        return height(node->left) - height(node->right);
    }

    int positionTrail(Node *node, const T &key) {
        if (node == nullptr) {
            return 0;
        }
        if (cmp(key, node->key)) {
            return positionTrail(node->left, key);
        }
        return positionTrail(node->right, key) + weight(node->left) + 1;
    }

    T statisticsTrail(Node *node, int index) {
        if (weight(node->left) == index) {
            return node->key;
        }
        if (index < weight(node->left)) {
            return statisticsTrail(node->left, index);
        }
        return statisticsTrail(node->right, index - (weight(node->left) + 1));
    }

    Node *addInternal(Node *node, const T &key) {
        if (node == nullptr) {
            return new Node(key);
        } else {
            if (cmp(key, node->key)) {
                node->left = addInternal(node->left, key);
            } else {
                node->right = addInternal(node->right, key);
            }
        }
        return balance(node);
    }

    Node *findAndRemoveMin(Node *node, Node **min){
        if (!node->left) {
            *min = node;
            return node->right;
        }
        node->left = findAndRemoveMin(node->left, min);
        return balance(node);
    }
    Node *findAndRemoveMax(Node *node, Node **max){
        if (!node->right) {
            *max = node;
            return node->left;
        }
        node->right = findAndRemoveMax(node->right, max);
        return balance(node);

    }
    Node *deleteInternal(Node *node, const T &key) {
        if (cmp(node->key, key)) {                      //Спуск
            node->right = deleteInternal(node->right, key);
        } else if (cmp(key, node->key)) {
            node->left = deleteInternal(node->left, key);
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
                Node *temp1 = findAndRemoveMin(right, &min);
                min->right = temp1;
                min->left = left;
                return balance(min);
            } else {
                Node *max = nullptr;
                Node *temp2 = findAndRemoveMax(left, &max);
                max->left = temp2;
                max->right = right;
                return balance(max);
            }
        }
        return balance(node);
    }

    Node *balance(Node *balancing) {
        Node *returned = balancing;
        if (balanceFactor(balancing) == -2) {
            if (balanceFactor(balancing->right) == 1) {
                Node *tmp = balancing->right;
                balancing->right = balancing->right->left;
                rightRotate(tmp);
            }
            returned = balancing->right;
            leftRotate(balancing);

        } else if (balanceFactor(balancing) == 2) {
            if (balanceFactor(balancing->left) == -1) {
                Node *tmp = balancing->left;
                balancing->left = balancing->left->right;
                leftRotate(tmp);
            }
            returned = balancing->left;
            rightRotate(balancing);
        }
        returned->weight = weight(returned->left) + weight(returned->right) + 1;
        returned->height = max(height(returned->left), height(returned->right)) + 1;
        return returned;
    }

    void leftRotate(Node *rotated) {
        Node *tmp = rotated->right;
        rotated->right = tmp->left;
        tmp->left = rotated;
        rotated->weight = weight(rotated->left) + weight(rotated->right) + 1;
        tmp->weight = weight(tmp->left) + weight(tmp->right) + 1;

        rotated->height = max(height(rotated->left), height(rotated->right)) + 1;
        tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
    }

    void rightRotate(Node *rotated) {
        Node *tmp = rotated->left;
        rotated->left = tmp->right;
        tmp->right = rotated;
        rotated->weight = weight(rotated->left) + weight(rotated->right) + 1;
        tmp->weight = weight(tmp->left) + weight(tmp->right) + 1;

        rotated->height = max(height(rotated->left), height(rotated->right)) + 1;
        tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
    }

};

int main() {
    int n;
    cin >> n;
    AVLTree<int, LeftMoreThanRight<int>> tree;
    for (int i = 0; i < n; ++i) {
        int command, value;
        cin >> command >> value;
        if (command == 1) {
            cout << tree.Position(value) << endl;
            tree.Add(value);
        } else {
            tree.Delete(tree.KStatistics(value).second);
        }
    }
    return 0;
}


//#include <iostream>
//
//using namespace std;
//
//template<class T>
//class LeftMoreThanRight {
//public:
//    bool operator()(const T &l, const T &r) {
//        return l > r;
//    }
//};
//
//template<class T, class Comparator = less<T>>
//class AVLTree {
//    struct Node {
//        explicit Node(const T &key)
//                : key(key), left(nullptr), right(nullptr), height(1), weight(1) {}
//
//        T key;
//        Node *left;
//        Node *right;
//        int height;
//        int weight;
//    };
//
//public:
//    bool Search(const T &key) {
//        return Find(key).first;
//    }
//
//    explicit AVLTree(const Comparator &compare = Comparator()) : root(nullptr), size(0) {};
//
//    ~AVLTree() {
//        destroyTree(root);
//    }
//
//    void Add(const T &key) {
//        ++size;
//        root = addInternal(root, key);
//    }
//
//    bool Delete(const T &key) {
//        if (Search(key)) {
//            root = deleteInternal(root, key);
//            --size;
//            return true;
//        } else {
//            return false;
//        }
//    };
//
//    int Position(const T &key) {
//        return positionTrail(root, key);
//    }
//
//    pair<bool, T> KStatistics(int index) {
//        if (index >= size) {
//            return make_pair(false, 0);
//        }
//        return make_pair(true, statisticsTrail(root, index));
//    }
//
//private:
//    Node *root;
//    int size;
//    Comparator cmp;
//
//    Node *FindMin(Node *node) {
//        if (node == nullptr) {
//            return nullptr;
//        }
//        while (node->left != nullptr) {
//            node = node->left;
//        }
//        return node;
//    }
//
//    pair<bool, Node *> Find(const T &key) {
//        Node *current = root;
//        while (true) {
//            if (current == nullptr) {
//                return make_pair(false, nullptr);
//            } else if (!(cmp(current->key, key)) && !(cmp(key, current->key))) {
//                return make_pair(true, current);
//            } else if (cmp(key, current->key)) {
//                current = current->left;
//            } else {
//                current = current->right;
//            }
//        }
//    }
//
//    void destroyTree(Node *node) {
//        if (node) {
//            destroyTree(node->left);
//            destroyTree(node->right);
//            delete node;
//        }
//    }
//
//    Node *findAndRemoveMin(Node *node) {
//        if (node->left == nullptr) {           //Как только нашли минимум, подвязываем
//            return node->right;                             //правого ребенка к родителю
//        }
//        node->left = findAndRemoveMin(node->left);                   //Рекурсивно балансируем
//        return balance(node);
//    }
//
//    int weight(Node *node) {
//        return node ? node->weight : 0;
//    }
//
//    int height(Node *node) {
//        return node ? node->height : 0;
//    }
//
//    int balanceFactor(Node *node) {
//        return Height(node->left) - height(node->right);
//    }
//
//    int positionTrail(Node *node, const T &key) {
//        if (node == nullptr) {                        //Дойдя до нуля, возвращает нуль
//            return 0;
//        }
//        if (cmp(key, node->key)) {// Если ключ меньше, то рекурсивно спускается влево
//            return positionTrail(node->left, key);
//        }
//        return positionTrail(node->right, key) + weight(node->left) + 1; //Если больше, то спускается влево, добавляя
//    }
//
//    T statisticsTrail(Node *node, int index) {
//        if (weight(node->left) == index) { //Если вес левой ноды равен индексу, возвращаем ее ключ
//            return node->key;
//        }
//        if (index < weight(node->left)) { //Индекс меньше левой ноды -> рекурсивно идем в левое поддерево
//            return statisticsTrail(node->left, index);
//        }
//        return statisticsTrail(node->right, index - (weight(node->left) + 1));
//        // Индекс больше веса левой ноды -> идем в правое поддерево с индексом
//        // (необходимым весом), равным инд - вес л.п. + 1
//    }
//
//    Node *addInternal(Node *node, const T &key) {
//        if (node == nullptr) {                     //Дойдя до нуля, создаем новый лист
//            return new Node(key);
//        } else {
//            if (cmp(key, node->key)) {                    //Спуск по ключу
//                node->left = addInternal(node->left, key);
//            } else {
//                node->right = addInternal(node->right, key);
//            }
//        }
//        return balance(node);    //Балансировка поддерева и возврат наверх по рекурсии
//    }
//
//    Node *deleteInternal(Node *node, const T &key) {
//        if (cmp(node->key, key)) {                      //Спуск по ключу
//            node->right = deleteInternal(node->right, key);
//        } else if (cmp(key, node->key)) {
//            node->left = deleteInternal(node->left, key);
//        } else {
//            if (node->right == nullptr) { //Нет правого поддерева -> подвязываем левое поддерево
//                Node *tmp = node->left;
//                delete node;
//                return tmp;
//            }
//            Node *min = FindMin(node->right); //Есть правое поддерево -> ищем минимум
//            node->right = findAndRemoveMin(node->right);    //в правом поддереве, удаляем его и
//            Node *tmp_left = node->left; //рекурсивно балансируем его
//            Node *tmp_right = node->right; //Вставляем минимум вместо удаленной ноды
//            delete node;
//            node = min;
//            min->left = tmp_left;
//            min->right = tmp_right;
//            return balance(min);
//        }
//        return balance(node);
//    }
//
//    Node *balance(Node *balancing) {
//        Node *returned = balancing;
//        if (balanceFactor(balancing) == -2) { //Делаем левый поворот при необходимости
//            if (balanceFactor(balancing->right) == 1) { //Делаем большой левый поворот при необходимости
//                Node *tmp = balancing->right;
//                balancing->right = balancing->right->left;          //Перепривязываем ноды
//                rightRotate(tmp);                            //Делаем малый правый поворот
//            }
//            returned = balancing->right;                             //Меняем возвращаемую ноду
//            leftRotate(balancing);                                //Делаем левый поворот
//
//        } else if (balanceFactor(balancing) == 2) {            //Симметричные действия
//            if (balanceFactor(balancing->left) == -1) {
//                Node *tmp = balancing->left;
//                balancing->left = balancing->left->right;
//                leftRotate(tmp);
//            }
//            returned = balancing->left;
//            rightRotate(balancing);
//        }
//        returned->weight = Weight(returned->left) + weight(returned->right) + 1;//Обновляем вес
//        returned->height = max(Height(returned->left), height(returned->right)) + 1;//Обновляем высоту
//        return returned;
//    }
//
//    void leftRotate(Node *rotated) {
//        Node *tmp = rotated->right;
//        rotated->right = tmp->left;                             //Перепривязываем ноды
//        tmp->left = rotated;
//        rotated->weight = Weight(rotated->left) + weight(rotated->right) + 1; //Обновляем веса
//        tmp->weight = weight(tmp->left) + Weight(tmp->right) + 1;
//
//        rotated->height = max(Height(rotated->left), height(rotated->right)) + 1; //Обновляем высоты
//        tmp->height = max(Height(tmp->left), height(tmp->right)) + 1;
//    }
//
//    void rightRotate(Node *rotated) {
//        Node *tmp = rotated->left;
//        rotated->left = tmp->right;
//        tmp->right = rotated;
//        rotated->weight = weight(rotated->left) + Weight(rotated->right) + 1;
//        tmp->weight = Weight(tmp->left) + weight(tmp->right) + 1;
//
//        rotated->height = max(Height(rotated->left), height(rotated->right)) + 1;
//        tmp->height = max(height(tmp->left), Height(tmp->right)) + 1;
//    }
//
//};
//
//int main() {
//    int n;
//    cin >> n;
//    AVLTree<int, LeftMoreThanRight<int>> tree;
//    for (int i = 0; i < n; ++i) {
//        int command, value;
//        cin >> command >> value;
//        if (command == 1) {
//            cout << tree.Position(value) << endl;
//            tree.Add(value);
//        } else {
//            tree.Delete(tree.KStatistics(value).second);
//        }
//    }
//    return 0;
//}
//
