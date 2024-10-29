#include <iostream>

using namespace std;

// Структура узла дерева
struct NodeT {
    int key;
    int height;
    NodeT* left;
    NodeT* right;

    NodeT(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int heightTree(NodeT* n) {
    return n ? n->height : 0;
}

// Функция для получения баланса узла
int getBalance(NodeT* n) {
    return n ? heightTree(n->left) - heightTree(n->right) : 0;
}

// Функция для обновления высоты узла
void updateHeight(NodeT* n) {
    if (n) {
        n->height = 1 + max(heightTree(n->left), heightTree(n->right));
    }
}

// Правое вращение вокруг узла y
NodeT* rotateRight(NodeT* y) {
    NodeT* x = y->left;
    NodeT* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левое вращение вокруг узла x
NodeT* rotateLeft(NodeT* x) {
    NodeT* y = x->right;
    NodeT* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Вставка узла в АВЛ-дерево
NodeT* insertTree(NodeT* node, int key) {
    if (!node) return new NodeT(key);

    if (key < node->key) {
        node->left = insertTree(node->left, key);
    } else if (key > node->key) {
        node->right = insertTree(node->right, key);
    } else {
        return node;  // Дубликаты не допускаются
    }

    updateHeight(node);

    // Проверка баланса узла и балансировка
    int balance = getBalance(node);

    // Левый поворот
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    // Правый поворот
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    // Левый-правый поворот
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Правый-левый поворот
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Структура для очереди
struct QueueNode {
    NodeT* data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(NodeT* node) {
        QueueNode* newNode = new QueueNode{node, nullptr};
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    NodeT* dequeue() {
        if (!front) return nullptr;
        QueueNode* temp = front;
        NodeT* node = front->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return node;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

// Функция обхода дерева змейкой
void zigzagTraversal(NodeT* root) {
    if (!root) return;

    Queue q;
    q.enqueue(root);
    bool leftToRight = true;

    while (!q.isEmpty()) {
        int levelSize = 0;
        QueueNode* current = q.front;
        while (current) {
            levelSize++;
            current = current->next;
        }

        NodeT** levelNodes = new NodeT*[levelSize];
        for (int i = 0; i < levelSize; ++i) {
            NodeT* node = q.dequeue();
            levelNodes[i] = node;

            if (node->left) q.enqueue(node->left);
            if (node->right) q.enqueue(node->right);
        }

        if (leftToRight) {
            for (int i = 0; i < levelSize; i++) {
                cout << levelNodes[i]->key << " ";
            }
        } 

        else {
            for (int i = levelSize - 1; i >= 0; i--) {
                cout << levelNodes[i]->key << " ";
            }
        }

        leftToRight = !leftToRight;
        delete[] levelNodes;
    }
    cout << endl;
}

int main() {
    NodeT* root = nullptr;
    int count;

    cout << "Введите количество чисел: ";
    cin >> count;

    cout << "Введите числа:" << endl;
    for (int i = 0; i < count; i++) {
        int key;
        cin >> key;
        root = insertTree(root, key);
    }

    cout << "Вывод змейкой:" << endl;
    zigzagTraversal(root);

    return 0;
}