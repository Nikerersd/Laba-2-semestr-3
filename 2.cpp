#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    int data; 
    Node* next;
};

struct Set {
    Node* head;

    Set() : head(nullptr) {}

    // Добавление элемента в множество
    void add(int value) {
        if (!contains(value)) {
            Node* newNode = new Node{value, head};
            head = newNode;
        }
    }

    // Удаление элемента из множества
    void remove(int value) {
        Node** current = &head;
        while (*current) {
            if ((*current)->data == value) {
                Node* toDelete = *current;
                *current = (*current)->next;
                delete toDelete;
                return;
            }
            current = &((*current)->next);
        }
    }

    // Проверка наличия элемента в множестве
    bool contains(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Запись в файл
    void saveToFile(const char* filename) {
        ofstream file(filename);
        Node* current = head;
        while (current) {
            file << current->data << endl;
            current = current->next;
        }
        file.close();
    }

    // Считывание из файла
    void loadFromFile(const char* filename) {
        ifstream file(filename);
        int value;
        while (file >> value) {
            add(value);
        }
        file.close();
    }

    // Освобождение памяти
    ~Set() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Функция для выполнения команды
void executeCommand(Set& set, const string& command, int value) {
    if (command == "SETADD") {
        set.add(value);
    } else if (command == "SETDEL") {
        set.remove(value);
    } else if (command == "SET_AT") {
        cout << (set.contains(value) ? "YES" : "NO") << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        cerr << "Usage: " << argv[0] << " --file <path to file> --query <command>" << endl;
        return 1;
    }

    const char* filename = argv[2];
    const string command = argv[4];
    int value = stoi(argv[5]);

    Set set;
    set.loadFromFile(filename);

    // Пример выполнения команд, можно изменить по необходимости
    executeCommand(set, command, value); // пример команды

    set.saveToFile(filename); // Сохраняем изменения

    return 0;
}
