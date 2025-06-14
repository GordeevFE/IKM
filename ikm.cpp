#include <iostream>

using namespace std;

// Структура узла стека
struct StackNode {
    int data;
    StackNode* prev;  // Указатель на предыдущий элемент
};

// Класс стека целых чисел
class IntStack {
    StackNode* top_ptr;  // Указатель на вершину стека

public:
    // Инициализируем пустой стек
    IntStack() : top_ptr(nullptr) {}

    // Освобождаем память, удаляя все элементы
    ~IntStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Добавление элемента в стек
    void push(int num) {
        StackNode* new_node = new StackNode;
        new_node->data = num;
        new_node->prev = top_ptr;
        top_ptr = new_node;
    }

    // Извлечение элемента из стека
    int pop() {
        if (isEmpty()) { // Проверка на пустоту
            cout << "Недостаточно" << endl;
            return -1;
        }
        StackNode* old_top = top_ptr;
        int result = old_top->data;
        top_ptr = old_top->prev;
        delete old_top;
        return result;
    }

    // Просмотр верхнего элемента без удаления
    int top() const {
        if (isEmpty()) {
            cout << "Пустая стопка" << endl;
            return -1;
        }
        return top_ptr->data;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return top_ptr == nullptr;
    }
};

// Класс для обработки контейнеров
class ContainerHandler {
    IntStack stacks[500];
    int total_containers;

    // Обработка случая с двумя контейнерами
    void processTwoContainers() {
        int cnt1, cnt2;
        int first, second;
        bool possible = true;
        int moves = 0;   

        // Чтение первого контейнера
        cin >> cnt1;
        for (int i = 0; i < cnt1; ++i) {
            int x;
            cin >> x;
            if (i == 0) first = x;
            if (x == 2) moves++;
            if (i > 0 && x == 1) possible = false;
        }

        // Чтение второго контейнера
        cin >> cnt2;
        for (int i = 0; i < cnt2; ++i) {
            int x;
            cin >> x;
            if (i == 0) second = x;
            if (x == 1) moves++;
            if (i > 0 && x == 2) possible = false;
        }

        // Если решение невозможно
        if (!possible) {
            cout << "0\n";
            return;
        }

        // Вывод перемещений в зависимости от первого элемента
        if (first == 1 || (second == 2 && first != 2)) {
            for (int i = 0; i < moves; ++i) {
                cout << "1 2\n";
            }
        } else {
            for (int i = 0; i < moves; ++i) {
                cout << "2 1\n";
            }
        }
    }

    // Загрузка данных о контейнерах
    void loadContainers() {
        for (int i = 1; i <= total_containers; ++i) {
            int items;
            cout << "Введите кол-во конт. в стопке, а затем виды товаров: ";
            cin >> items;
            for (int j = 0; j < items; ++j) {
                int elem;
                cin >> elem;
                if (elem != i) {
                    stacks[i].push(elem);
                }
            }
        }
    }

    // Решение задачи для 3+ контейнеров
    void solveContainers() {
        const int last = total_containers;
        int buffer = 1;
        int buffer_count = 0;

        // Основной цикл по всем контейнерам, кроме последнего
        for (int i = 1; i < last; ++i) {
            while (!stacks[i].isEmpty()) {
                int target = stacks[i].top();
                if (stacks[target].isEmpty()) {
                    // Если целевой контейнер пуст, перемещаем напрямую
                    cout << i << " " << target << "\n";
                    stacks[i].pop();
                } else {
                    // Иначе перемещаем в буфер (последний контейнер)
                    cout << i << " " << last << "\n";
                    stacks[last].push(stacks[i].pop());
                }
            }
        }

        // Обработка буфера (последнего контейнера)
        while (!stacks[last].isEmpty()) {
            int elem = stacks[last].pop();
            if (elem == last) {
                // Если элемент принадлежит буферу, временно перемещаем
                cout << last << " " << buffer << "\n";
                buffer_count++;
            } else if (elem == buffer) {
                // Если элемент совпадает с временным буфером, меняем буфер
                buffer = 3 - buffer;  // Переключаем между 1 и 2
                for (int i = 0; i < buffer_count; ++i) {
                    cout << elem << " " << buffer << "\n";
                }
                cout << last << " " << elem << "\n";
            } else {
                // Иначе перемещаем в целевой контейнер
                cout << last << " " << elem << "\n";
            }
        }

        // Возвращаем элементы из временного буфера
        for (int i = 0; i < buffer_count; ++i) {
            cout << buffer << " " << last << "\n";
        }
    }

public:
    // Точка входа в программу
    void start() {
        cout << "Введите кол-во стопок контейнеров: ";
        cin >> total_containers;

        if (total_containers == 2) {
            processTwoContainers();
            return;
        }
        if (total_containers <= 0) {
            cout << "Введено некоректное число!" << endl;
        }
        loadContainers();
        solveContainers();
    }
};

// Главная функция
int main() {
    ContainerHandler handler;
    handler.start();
    return 0;
}
