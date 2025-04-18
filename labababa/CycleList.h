#include <stdexcept>                  

/// <summary>
/// Шаблонная структура односвязного циклического списка CycleList.
/// </summary>
/// <typeparam name="T">Тип данных, которые хранятся в списке.</typeparam>
template <typename T>
class CycleList
{
private:
    // Внутренняя структура, описывающая узел списка
    struct Node
    {
        T data;                       // Поле для хранения данных
        Node* next;                  // Указатель на следующий узел

        // Конструктор узла: инициализация полей
        Node(T value, Node* next = nullptr) : data(value), next(next) {}
    };

    Node* head = nullptr;            // Указатель на начало списка
    Node* tail = nullptr;            // Указатель на конец списка
    int size = 0;                    // Количество элементов в списке

public:
    /// <summary> Деструктор: вызывает метод clear() </summary>
    ~CycleList()
    {
        clear();                     // Очищаем список при удалении объекта
    }

    /// <summary> Добавление элемента в конец списка </summary>
    /// <param name="value">Значение для добавления</param>
    void add(T value)
    {
        Node* newNode = new Node(value); // Создаём новый узел с заданным значением

        if (!head)
        {                      // Если список пустой (head == nullptr)
            head = tail = newNode;        // Новый элемент — и голова, и хвост
            newNode->next = head;         // Циклическая связь: сам на себя
        }
        else
        {
            tail->next = newNode;         // Присоединяем новый узел после хвоста
            tail = newNode;               // Обновляем tail на новый узел
            tail->next = head;            // Циклически замыкаем
        }

        size++;                           // Увеличиваем размер списка
    }

    /// <summary> Вставка элемента в указанную позицию </summary>
    void insert(int index, T value)
    {
        if (index < 0 || index > size)                  // Проверка на допустимость индекса
            throw std::out_of_range("Invalid index");   // Если индекс недопустим — исключение

        Node* newNode = new Node(value);                // Создаём новый узел

        if (index == 0)
        {                                               // Вставка в начало
            if (!head)
            {                                           // Если список пуст
                head = tail = newNode;                  // Новый элемент — и head, и tail
                newNode->next = head;                   // Замыкаем на самого себя
            }
            else {
                newNode->next = head;                   // Новый узел указывает на старый head
                head = newNode;                         // Обновляем head
                tail->next = head;                      // Обновляем tail->next на новый head
            }
        }
        else
        {
            Node* current = head;                       // Указатель на текущий элемент
            for (int i = 0; i < index - 1; i++)         // Доходим до элемента перед вставкой
                current = current->next;

            newNode->next = current->next;              // Новый узел указывает на следующего
            current->next = newNode;                    // Предыдущий указывает на новый

            if (current == tail)                        // Если вставка в конец
                tail = newNode;                         // Обновляем tail
        }

        size++;                                         // Увеличиваем размер
    }

    /// <summary> Удаление элемента по индексу </summary>
    void removeAt(int index)
    {
        if (!head || index < 0 || index >= size)             // Проверка на корректность
            throw std::out_of_range("Invalid index");

        if (index == 0) {                                    // Удаление первого элемента
            Node* toDelete = head;                           // Сохраняем указатель на удаляемый

            if (size == 1)
            {                                                // Если в списке 1 элемент
                head = tail = nullptr;                       // Обнуляем head и tail
            }
            else
            {
                head = head->next;                           // Сдвигаем head
                tail->next = head;                           // tail теперь указывает на новый head
            }

            delete toDelete;                                 // Удаляем старый head
        }
        else
        {
            Node* current = head;                            // Указатель на текущий
            for (int i = 0; i < index - 1; i++)              // Доходим до элемента перед удаляемым
                current = current->next;

            Node* toDelete = current->next;                  // Узел, который будем удалять
            current->next = toDelete->next;                  // Переподключаем ссылки

            if (toDelete == tail)                            // Если удаляем хвост
                tail = current;                              // Обновляем tail

            delete toDelete;                                 // Удаляем узел
        }

        size--;                                              // Уменьшаем размер
    }

    /// <summary> Получение ссылки на элемент по индексу </summary>
    T& operator[](const int index) const
    {
        if (index < 0 || index >= size)                     // Проверка индекса
            throw std::out_of_range("Invalid index");

        Node* current = head;                               // Начинаем с головы
        for (int i = 0; i < index; i++)                     // Доходим до нужного индекса
            current = current->next;

        return current->data;                               // Возвращаем данные
    }

    /// <summary> Получение количества элементов </summary>
    int count() const
    {
        return size;                                        // Просто возвращаем размер
    }

    /// <summary> Подсчёт количества вхождений значения </summary>
    int count(T value) const
    {
        if (!head) return 0;                                // Если список пуст — 0

        int counter = 0;                                    // Счётчик вхождений
        Node* current = head;

        for (int i = 0; i < size; i++)
        {                                                   // Проходим по всем узлам
            if (current->data == value) counter++;          // Если данные совпадают — +1
            current = current->next;                        // Переход к следующему
        }

        return counter;                                     // Возвращаем результат
    }

    /// <summary> Полная очистка списка </summary>
    void clear()
    {
        while (size > 0)
        {                                                         // Пока есть элементы
            removeAt(0);                                    // Удаляем первый
        }
    }
};
