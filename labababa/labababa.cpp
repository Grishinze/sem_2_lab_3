#include <iostream>
#include "CycleList.h"  // Подключаем нашу структуру

using namespace std;

/// <summary>
/// Печатает текущее состояние очереди.
/// </summary>
/// <param name="queue">Список с элементами очереди.</param>
void printQueue(const CycleList<int>& queue) {
    cout << "Текущая очередь: ";
    for (int i = 0; i < queue.count(); ++i) {
        cout << queue[i] << " ";
    }
    cout << endl;
}

/// <summary>
/// Вставляет значение 1 перед каждым отрицательным элементом в очереди.
/// </summary>
void insertBeforeNegatives(CycleList<int>& queue) {
    for (int i = 0; i < queue.count(); ++i) {
        if (queue[i] < 0) {
            queue.insert(i, 1);  // Вставляем 1 перед отрицательным
            ++i;                 // Пропускаем вставленную 1
        }
    }
}

/// <summary>
/// Удаляет все элементы с отрицательными значениями.
/// </summary>
void removeNegatives(CycleList<int>& queue) {
    int i = 0;
    while (i < queue.count()) {
        if (queue[i] < 0) {
            queue.removeAt(i);  // Удаляем и не увеличиваем i
        }
        else {
            ++i;  // Переход к следующему элементу
        }
    }
}

/// <summary>
/// Главное меню управления очередью.
/// </summary>
void Menu() {
    cout << "\n===== МЕНЮ =====" << endl;
    cout << "1. Добавить элемент в очередь" << endl;
    cout << "2. Показать очередь" << endl;
    cout << "3. Вставить 1 перед отрицательными числами" << endl;
    cout << "4. Удалить все отрицательные элементы" << endl;
    cout << "5. Очистить очередь" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите пункт: ";
}

int main()
{
    setlocale(LC_ALL, "");
    CycleList<int> queue;   

    int choice;             
    do {
        Menu();             
        cin >> choice;      

        switch (choice) {
        case 1: 
        {
            int value;
            cout << "Введите элементы (0 — завершить ввод):" << endl;

            while (true) {
                cin >> value;              // Считываем число от пользователя
                if (value == 0) {
                    break;                 // Если ввели 0 — завершаем ввод
                }
                queue.add(value);
            }
            
            break;
        }
        case 2: {
            printQueue(queue);
            break;
        }
        case 3: {
            insertBeforeNegatives(queue);
            cout << "Вставка выполнена." << endl;
            break;
        }
        case 4: {
            removeNegatives(queue);
            cout << "Удаление выполнено." << endl;
            break;
        }
        case 5: {
            queue.clear();
            cout << "Очередь очищена." << endl;
            break;
        }
        case 0: {
            cout << "Завершение работы программы." << endl;
            break;
        }
        default:
            cout << "Неверный пункт меню. Попробуйте ещё раз." << endl;
        }
    } while (choice != 0);  
}
