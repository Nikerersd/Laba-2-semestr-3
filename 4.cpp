#include <iostream>
using namespace std;

struct Array {
    int* data;
    int size;        // Текущий размер массива
    int capacity;    // Максимальная вместимость массива
};

void initArray(Array& arr, int cap) {
    arr.data = new int[cap];
    arr.size = 0;
    arr.capacity = cap;
}

void appendArray(Array& arr, int value) {
    if (arr.size >= arr.capacity) {
        // Увеличение емкости массива
        arr.capacity *= 2;
        int* newData = new int[arr.capacity];
        for (int i = 0; i < arr.size; ++i) {
            newData[i] = arr.data[i];
        }
        delete[] arr.data;
        arr.data = newData;
    }
    arr.data[arr.size++] = value;
}

void findSubarraysWithSum(const Array& arr, int targetSum) {
    for (int start = 0; start < arr.size; start++) {
        int currentSum = 0; // Сброс текущей суммы
        for (int end = start; end < arr.size; end++) {
            currentSum += arr.data[end];
            if (currentSum == targetSum) {
                // Если сумма подмассива равна целевой, выводим подмассив
                cout << "[";
                for (int i = start; i <= end; i++) {
                    cout << arr.data[i];
                    if (i < end) cout << ", ";
                }
                cout << "]" << endl;
            }
        }
    }
}

void freeArray(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

int main() {
    Array arr;
    initArray(arr, 10);

    int count;
    cout << "Введите количество чисел: ";
    cin >> count;

    cout << "Введите числа: ";
    for (int i = 0; i < count; i++) {
        int value;
        cin >> value;
        appendArray(arr, value);
    }

    int targetSum;
    cout << "Введите целевую сумму: ";
    cin >> targetSum;

    cout << "Подмассивы с суммой " << targetSum << ":" << endl;
    findSubarraysWithSum(arr, targetSum);

    freeArray(arr);
}
