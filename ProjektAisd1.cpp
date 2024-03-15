#include <iostream>
#include <cstring>
// Struktura węzła listy
struct Node {
    int data;
    Node* previous;

    // Konstruktor
    Node(int value) : data(value), previous(nullptr) {}
};

// Implementacja stosu oparta na liście wiązanej
class Stack {
private:
    Node* top; // Wierzchołek stosu

public:
    // Konstruktor
    Stack() : top(nullptr) {}

    // Destruktor
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Sprawdza, czy stos jest pusty
    bool isEmpty() {
        return top == nullptr;
    }

    // Dodaje element na wierzchołek stosu
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->previous = top;
        top = newNode;
    }

    // Usuwa element z wierzchołka stosu i zwraca jego wartość
    int pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty." << std::endl;
            return -1; // Możesz obsłużyć ten przypadek zgodnie z twoimi potrzebami
        }
        int value = top->data;
        Node* temp = top;
        top = top->previous;
        delete temp;
        return value;
    }

    // Zwraca wartość na wierzchołku stosu bez usuwania jej
    int peek() {
        if (isEmpty()) {
            std::cerr << "Stack is empty." << std::endl;
            return -1; // Możesz obsłużyć ten przypadek zgodnie z twoimi potrzebami
        }
        return top->data;
    }
};

class String {
private:
    char* string;

public:
    String() : string(nullptr) {}

    String(const char* str) {
        if (str != nullptr) {
            string = new char[strlen(str) + 1];
            strcpy_s(string, strlen(str) + 1, str);
        }
        else {
            string = nullptr;
        }
    }

    int length() const {
        return this->string ? strlen(this->string) : 0;
    }

    String operator+(const String& other) const {
        String result;
        result.string = new char[length() + other.length() + 1];
        strcpy_s(result.string, length() + other.length() + 1, string);
        strcat_s(result.string, length() + other.length() + 1, other.string);
        return result;
    }
    char& operator[](int index) {
        return this->string[index];
    }
    friend std::istream& operator>>(std::istream& is, String& str) {
        delete[] str.string;

        char temp;
        int size = 0;
        str.string = new char[1];
        while (is.get(temp) && temp != '\n') {
            str.string[size++] = temp;
            char* newData = new char[size + 1];
            strncpy_s(newData, size + 1, str.string, size);
            delete[] str.string;
            str.string = newData;
        }
        str.string[size] = '\0';

        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        if (str.string)
            os << str.string;
        return os;
    }

    ~String() {
        delete[] string;
    }
};

int main() {
    String object;
    String object1= "aaa";

    std::cin >> object;

    std::cout << object1 << object.length();

    return 0;
}
