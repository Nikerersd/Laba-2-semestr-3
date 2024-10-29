#include <iostream>
#include <string>

using namespace std;

struct NodeS {
    string data;
    NodeS* next;
};

struct Array {
    NodeS* head;
    
    Array() : head(nullptr) {}

    void add(const string& value) {
        NodeS* newNode = new NodeS();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    bool contains(const string& value) const {
        NodeS* current = head;
        while (current != nullptr) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    void remove(const string& value) {
        NodeS* current = head;
        NodeS* prev = nullptr;

        while (current != nullptr) {
            if (current->data == value) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
};

struct Stack {
    NodeS* top;
    
    Stack() : top(nullptr) {}
};

void pushStack(Stack& stack, const string& value) {
    NodeS* newNode = new NodeS();
    newNode->data = value;
    newNode->next = stack.top;
    stack.top = newNode;
}

void popStack(Stack& stack) {
    if (stack.top != nullptr) {
        NodeS* temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
}

// Рекурсивная функция
bool order(const string& task, Array& dependencies, Array& visited, Array& visiting, Stack& taskOrder) {
    if (visiting.contains(task)) return false; // Найден цикл
    if (visited.contains(task)) return true;

    visiting.add(task);

    // Проверка всех зависимостей для текущей задачи
    NodeS* dep = dependencies.head;
    while (dep != nullptr) {
        if (dep->data == task && !order(dep->next->data, dependencies, visited, visiting, taskOrder))
            return false;
        dep = dep->next->next;
    }

    visiting.remove(task); // Удаляем задачу из visiting после её обработки
    visited.add(task);
    pushStack(taskOrder, task);
    return true;
}

bool canFinishTasks(Array& tasks, Array& dependencies) {
    Array visited; // Для хранения посещённых задач
    Array visiting; // Для хранения задач, находящихся в процессе посещения
    Stack taskOrder;

    NodeS* task = tasks.head;
    while (task != nullptr) {
        if (!visited.contains(task->data)) {
            if (!order(task->data, dependencies, visited, visiting, taskOrder))
                return false; // Цикл найден, выполнение невозможно
        }
        task = task->next;
    }

    while (taskOrder.top != nullptr) {
        cout << taskOrder.top->data << " ";
        popStack(taskOrder);
    }
    cout << endl;
    return true;
}

int main() {
    Array tasks;
    Array dependencies;

    int numTasks, numDependencies;
    cout << "Введите количество задач: ";
    cin >> numTasks;
    cout << "Введите задачи:" << endl;
    for (int i = 0; i < numTasks; i++) {
        string task;
        cin >> task;
        tasks.add(task);
    }

    cout << "Введите количество зависимостей: ";
    cin >> numDependencies;
    cout << "Введите зависимости (каждая строка содержит две задачи, например, A B):" << endl;
    for (int i = 0; i < numDependencies; i++) {
        string from, to;
        cin >> from >> to;
        dependencies.add(from);
        dependencies.add(to);
    }

    if (canFinishTasks(tasks, dependencies)) {
        cout << "Возможно выполнить все задачи." << endl;
    } 
    else {
        cout << "Невозможно выполнить все задачи." << endl;
    }
}