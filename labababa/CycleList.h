#include <stdexcept>                  

/// <summary>
/// ��������� ��������� ������������ ������������ ������ CycleList.
/// </summary>
/// <typeparam name="T">��� ������, ������� �������� � ������.</typeparam>
template <typename T>
class CycleList
{
private:
    // ���������� ���������, ����������� ���� ������
    struct Node
    {
        T data;                       // ���� ��� �������� ������
        Node* next;                  // ��������� �� ��������� ����

        // ����������� ����: ������������� �����
        Node(T value, Node* next = nullptr) : data(value), next(next) {}
    };

    Node* head = nullptr;            // ��������� �� ������ ������
    Node* tail = nullptr;            // ��������� �� ����� ������
    int size = 0;                    // ���������� ��������� � ������

public:
    /// <summary> ����������: �������� ����� clear() </summary>
    ~CycleList()
    {
        clear();                     // ������� ������ ��� �������� �������
    }

    /// <summary> ���������� �������� � ����� ������ </summary>
    /// <param name="value">�������� ��� ����������</param>
    void add(T value)
    {
        Node* newNode = new Node(value); // ������ ����� ���� � �������� ���������

        if (!head)
        {                      // ���� ������ ������ (head == nullptr)
            head = tail = newNode;        // ����� ������� � � ������, � �����
            newNode->next = head;         // ����������� �����: ��� �� ����
        }
        else
        {
            tail->next = newNode;         // ������������ ����� ���� ����� ������
            tail = newNode;               // ��������� tail �� ����� ����
            tail->next = head;            // ���������� ��������
        }

        size++;                           // ����������� ������ ������
    }

    /// <summary> ������� �������� � ��������� ������� </summary>
    void insert(int index, T value)
    {
        if (index < 0 || index > size)                  // �������� �� ������������ �������
            throw std::out_of_range("Invalid index");   // ���� ������ ���������� � ����������

        Node* newNode = new Node(value);                // ������ ����� ����

        if (index == 0)
        {                                               // ������� � ������
            if (!head)
            {                                           // ���� ������ ����
                head = tail = newNode;                  // ����� ������� � � head, � tail
                newNode->next = head;                   // �������� �� ������ ����
            }
            else {
                newNode->next = head;                   // ����� ���� ��������� �� ������ head
                head = newNode;                         // ��������� head
                tail->next = head;                      // ��������� tail->next �� ����� head
            }
        }
        else
        {
            Node* current = head;                       // ��������� �� ������� �������
            for (int i = 0; i < index - 1; i++)         // ������� �� �������� ����� ��������
                current = current->next;

            newNode->next = current->next;              // ����� ���� ��������� �� ����������
            current->next = newNode;                    // ���������� ��������� �� �����

            if (current == tail)                        // ���� ������� � �����
                tail = newNode;                         // ��������� tail
        }

        size++;                                         // ����������� ������
    }

    /// <summary> �������� �������� �� ������� </summary>
    void removeAt(int index)
    {
        if (!head || index < 0 || index >= size)             // �������� �� ������������
            throw std::out_of_range("Invalid index");

        if (index == 0) {                                    // �������� ������� ��������
            Node* toDelete = head;                           // ��������� ��������� �� ���������

            if (size == 1)
            {                                                // ���� � ������ 1 �������
                head = tail = nullptr;                       // �������� head � tail
            }
            else
            {
                head = head->next;                           // �������� head
                tail->next = head;                           // tail ������ ��������� �� ����� head
            }

            delete toDelete;                                 // ������� ������ head
        }
        else
        {
            Node* current = head;                            // ��������� �� �������
            for (int i = 0; i < index - 1; i++)              // ������� �� �������� ����� ���������
                current = current->next;

            Node* toDelete = current->next;                  // ����, ������� ����� �������
            current->next = toDelete->next;                  // �������������� ������

            if (toDelete == tail)                            // ���� ������� �����
                tail = current;                              // ��������� tail

            delete toDelete;                                 // ������� ����
        }

        size--;                                              // ��������� ������
    }

    /// <summary> ��������� ������ �� ������� �� ������� </summary>
    T& operator[](const int index) const
    {
        if (index < 0 || index >= size)                     // �������� �������
            throw std::out_of_range("Invalid index");

        Node* current = head;                               // �������� � ������
        for (int i = 0; i < index; i++)                     // ������� �� ������� �������
            current = current->next;

        return current->data;                               // ���������� ������
    }

    /// <summary> ��������� ���������� ��������� </summary>
    int count() const
    {
        return size;                                        // ������ ���������� ������
    }

    /// <summary> ������� ���������� ��������� �������� </summary>
    int count(T value) const
    {
        if (!head) return 0;                                // ���� ������ ���� � 0

        int counter = 0;                                    // ������� ���������
        Node* current = head;

        for (int i = 0; i < size; i++)
        {                                                   // �������� �� ���� �����
            if (current->data == value) counter++;          // ���� ������ ��������� � +1
            current = current->next;                        // ������� � ����������
        }

        return counter;                                     // ���������� ���������
    }

    /// <summary> ������ ������� ������ </summary>
    void clear()
    {
        while (size > 0)
        {                                                         // ���� ���� ��������
            removeAt(0);                                    // ������� ������
        }
    }
};
