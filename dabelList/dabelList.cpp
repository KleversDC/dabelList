#include <iostream>
#include <initializer_list>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int data) : data(data), next(nullptr), prev(nullptr) {}
};

class List {
private:
    Node* head;
    Node* tail;
    size_t size;

    void checkIndex(size_t index) const {
        if (index >= size) throw "Index out of bounds";
    }

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    List(initializer_list<int> values) : List() {
        for (int value : values) {
            append(value);
        }
    }

    ~List() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (!newNode) throw "Memory allocation failed";
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

    void deleteByValue(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current == head) {
                    head = head->next;
                    if (head) head->prev = nullptr;
                }
                else if (current == tail) {
                    tail = tail->prev;
                    if (tail) tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                --size;
                return;
            }
            current = current->next;
        }
        throw "Value not found";
    }

    void removeDuplicates() {
        Node* current = head;
        while (current) {
            Node* runner = current->next;
            while (runner) {
                if (runner->data == current->data) {
                    Node* toDelete = runner;
                    if (runner == tail) {
                        tail = tail->prev;
                        tail->next = nullptr;
                    }
                    else {
                        runner->prev->next = runner->next;
                        runner->next->prev = runner->prev;
                    }
                    runner = runner->next;
                    delete toDelete;
                    --size;
                }
                else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    int findMax() const {
        if (!head) throw "List is empty";
        int maxVal = head->data;
        Node* current = head->next;
        while (current) {
            if (current->data > maxVal) maxVal = current->data;
            current = current->next;
        }
        return maxVal;
    }

    int findMin() const {
        if (!head) throw "List is empty";
        int minVal = head->data;
        Node* current = head->next;
        while (current) {
            if (current->data < minVal) minVal = current->data;
            current = current->next;
        }
        return minVal;
    }

    void reversePrint() const {
        if (!tail) throw "List is empty";
        Node* current = tail;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    int& operator[](size_t index) {
        checkIndex(index);
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void display() const {
        if (!head) throw "List is empty";
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    try {
        List list = { 1, 2, 3, 4, 5 };
        list.display();

        list[2] = 42;
        list.display();

        list.deleteByValue(42);
        list.display();

        list.append(2);
        list.append(3);
        list.display();

        list.removeDuplicates();
        list.display();

        cout << "Max: " << list.findMax() << endl;
        cout << "Min: " << list.findMin() << endl;

        cout << "Reverse: ";
        list.reversePrint();

    }
    catch (const char* e) {
        cerr << "Exception: " << e << endl;
    }
}
