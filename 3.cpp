#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

struct Node {
    int value;
    Node* next;
};

struct Set {
    Node* head;

    Set() : head(nullptr) {}

    ~Set() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(int value) {
        if (!contains(value)) {
            Node* newNode = new Node{value, head};
            head = newNode;
        }
    }

    bool contains(int value) const {
        Node* current = head;
        while (current) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int sum() const {
        int sum = 0;
        Node* current = head;
        while (current) {
            sum += current->value;
            current = current->next;
        }
        return sum;
    }

    void print() const {
        Node* current = head;
        while (current) {
            cout << current->value << " ";
            current = current->next;
        }
        cout << "\n";
    }
};

void findMinPartition(Node* current, Set& set1, Set& set2, Set& bestSet1, Set& bestSet2, int& minDiff) {
    if (current == nullptr) {
        int sum1 = set1.sum();
        int sum2 = set2.sum();
        int diff = abs(sum1 - sum2);
        if (diff < minDiff) {
            minDiff = diff;
            bestSet1 = set1;
            bestSet2 = set2;
        }
        return;
    }

    set1.insert(current->value);
    findMinPartition(current->next, set1, set2, bestSet1, bestSet2, minDiff);
    set1.head = set1.head->next;

    set2.insert(current->value);
    findMinPartition(current->next, set1, set2, bestSet1, bestSet2, minDiff);
    set2.head = set2.head->next;
}

int main() {
    Set originalSet;
    int count;
    cout << "Введите количество чисел: ";
    cin >> count;

    cout << "Введите числa: ";
    for (int i = 0; i < count; i++) {
        int value;
        cin >> value;
        originalSet.insert(value);
    }

    Set set1, set2, bestSet1, bestSet2;
    int minDiff = INT_MAX;
    findMinPartition(originalSet.head, set1, set2, bestSet1, bestSet2, minDiff);

    cout << "Подмножество 1: ";
    bestSet1.print();
    cout << "Подмножество 2: ";
    bestSet2.print();
    cout << "Разность сумм: " << minDiff << endl;
}
