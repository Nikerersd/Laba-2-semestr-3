#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int TABLE_SIZE = 10;

struct BitNode {
    bool bit;
    BitNode* next;
};

int hashFunction1(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % TABLE_SIZE;
}

int hashFunction2(const string& key) {
    int hash = 1;
    for (char ch : key) {
        hash *= ch;
    }
    return hash % TABLE_SIZE;
}

int hashFunction3(const string& key) {
    int hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash += (key[i] * (i + 1));
    }
    return hash % TABLE_SIZE;
}

// Создание битового массива
BitNode* createBitArray() {
    BitNode* head = new BitNode{false, nullptr};
    BitNode* current = head;

    for (int i = 1; i < TABLE_SIZE; i++) {
        current->next = new BitNode{false, nullptr};
        current = current->next;
    }
    return head;
}

// Установка бита по индексу
void setBit(BitNode* head, int index) {
    BitNode* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->bit = true;
}

// Получение состояния бита по индексу
bool getBit(BitNode* head, int index) {
    BitNode* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->bit;
}

// Добавление элемента в фильтр Блума
void addBloomFilter(BitNode* bitArray, const string& key) {
    int index1 = hashFunction1(key);
    int index2 = hashFunction2(key);
    int index3 = hashFunction3(key);

    setBit(bitArray, index1);
    setBit(bitArray, index2);
    setBit(bitArray, index3);
}

// Проверка элемента в фильтре Блума
bool checkBloomFilter(BitNode* bitArray, const string& key) {
    int index1 = hashFunction1(key);
    int index2 = hashFunction2(key);
    int index3 = hashFunction3(key);

    return getBit(bitArray, index1) && getBit(bitArray, index2) && getBit(bitArray, index3);
}

// Очистка битового массива
void freeBitArray(BitNode* head) {
    while (head != nullptr) {
        BitNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    BitNode* bloomFilter = createBitArray();

    addBloomFilter(bloomFilter, "apple");
    addBloomFilter(bloomFilter, "banana");
    addBloomFilter(bloomFilter, "cherry");

    cout << "apple: " << (checkBloomFilter(bloomFilter, "apple") ? "Возможно в множестве" : "Не в множестве") << endl;
    cout << "banana: " << (checkBloomFilter(bloomFilter, "banana") ? "Возможно в множестве" : "Не в множестве") << endl;
    cout << "cherry: " << (checkBloomFilter(bloomFilter, "cherry") ? "Возможно в множестве" : "Не в множестве") << endl;
    cout << "grape: " << (checkBloomFilter(bloomFilter, "grape") ? "Возможно в множестве" : "Не в множестве") << endl;

    freeBitArray(bloomFilter);

}
