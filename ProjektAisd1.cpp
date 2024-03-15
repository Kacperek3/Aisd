#include <iostream>
#include <cstring>
#include <stdio.h>
// Struktura węzła listy
template <typename T>
struct Node {
    T data;
    Node<T>* previous;

    // Konstruktor
    Node(T value) : data(value), previous(nullptr) {}
};

// Implementacja stosu oparta na liście wiązanej
template <typename T>
class Stack {
private:
    Node<T>* top; // Wierzchołek stosu

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
    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->previous = top;
        top = newNode;
    }

    // Usuwa element z wierzchołka stosu i zwraca jego wartość
    T pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty." << std::endl;
            return -1; // Możesz obsłużyć ten przypadek zgodnie z twoimi potrzebami
        }
        T value = top->data;
        Node<T>* temp = top;
        top = top->previous;
        delete temp;
        return value;
    }

    // Zwraca wartość na wierzchołku stosu bez usuwania jej
    T peek() {
        if (isEmpty()) {
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

    String(const String& other) {
        if (other.string != nullptr) {
            string = new char[other.length() + 1];
            strcpy_s(string, other.length() + 1, other.string);
        }
        else {
            string = nullptr;
        }
    }

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

    bool isDigit(int index) {
        if (int(this->string[index] - '0') >= 0 and int(this->string[index] - '0') <= 9) {
            return true;
        }
        return false;
    }


    String operator+(const String& other) const {
        String result;
        result.string = new char[length() + other.length() + 1];
        strcpy_s(result.string, length() + other.length() + 1, string);
        strcat_s(result.string, length() + other.length() + 1, other.string);
        return result;
    }
    String operator+(const String&& other) const {
        String result;
        result.string = new char[length() + other.length() + 1];
        strcpy_s(result.string, length() + other.length() + 1, string);
        strcat_s(result.string, length() + other.length() + 1, other.string);
        return result;
    }
    String operator+(char character) const {
        String result;
        result.string = new char[length() + 2];
        strcpy_s(result.string, length() + 1, string);
        result.string[length()] = character;
        result.string[length() + 1] = '\0';
        return result;
    }


    String& operator=(const char* str) {
        if (string != nullptr)
            delete[] string;
        if (str != nullptr) {
            string = new char[strlen(str) + 1];
            strcpy_s(string, strlen(str) + 1, str);
        }
        else {
            string = nullptr;
        }
        return *this;
    }

    String& operator=(const String& str) {
        if (string != nullptr)
            delete[] string;
        if (str.string != nullptr) {
            string = new char[str.length() + 1];
            strcpy_s(string, str.length() + 1, str.string);
        }
        else {
            string = nullptr;
        }
        return *this;
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



String ONP(String& tmp) {
    Stack<char> list;
    String result = "";

    for (int i = 0; i < tmp.length(); i++) {
        if (tmp.isDigit(i)) {
            if (tmp.isDigit(i + 1)) result = result + tmp[i];//std::cout << tmp[i];
            else result = result + tmp[i] + " ";//std::cout << tmp[i] << " ";
        }
        else if (tmp[i] == ' ') {
            continue;
        }
        else if (tmp[i] == '(') list.push(tmp[i]);
        else if (tmp[i] == ')') {
            while (list.peek() != '('){
                result = result + list.peek() + " ";//std::cout << list.peek() << " ";
                list.pop();
            }
            list.pop();
        }
        //jesli puste zwraca 0 jesli nie zwraca 1
        else if (tmp[i] == '+' or tmp[i] == '-') {
            while (list.peek() != '(' and !list.isEmpty()) {
                result = result + list.peek() + " ";
                //std::cout << list.peek() << " ";
                list.pop();
            }
            list.push(tmp[i]);
        }
            
        else if (tmp[i] == '*' or tmp[i] == '/') list.push(tmp[i]);
        
    }
    while (!list.isEmpty()) {
        result = result + list.peek() + " ";
        //std::cout << list.peek() << " ";
        list.pop();
    }
    return result;
}

void ONPtoResult(String& tmp) {
    Stack<int> list;
    String result = "";

    bool collectingNumber = false;
    int number = 0;

    for (int i = 0; i < tmp.length(); i++) {
        if (tmp.isDigit(i)) {
            if (!collectingNumber) {
                collectingNumber = true;
                number = tmp[i] - '0';
            }
            else {
                number = number * 10 + (tmp[i] - '0');
            }
        }
        else if (tmp[i] == ' ') {
            if (collectingNumber) {
                list.push(number);
                collectingNumber = false;
                number = 0;
            }
            continue;
        }
        else if (tmp[i] == '+') {
            // Tutaj możesz pobrać dwa ostatnie elementy ze stosu, dodać je i umieścić wynik z powrotem na stosie
            int operand2 = list.pop();
            int operand1 = list.pop();
            list.push(operand1 + operand2);
        }
        else if (tmp[i] == '-') {
            int operand2 = list.pop();
            int operand1 = list.pop();
            list.push(operand1 - operand2);
        }
        else if (tmp[i] == '*') {
            // Tutaj możesz pobrać dwa ostatnie elementy ze stosu, pomnożyć je i umieścić wynik z powrotem na stosie
            int operand2 = list.pop();
            int operand1 = list.pop();
            list.push(operand1 * operand2);
        }
        // Analogicznie obsłuż inne operacje arytmetyczne
    }

    // Wyświetlenie wyniku
    std::cout << "Wynik: " << list.pop() << std::endl;
}


int main() {
    String object = "23 2 * 1 45 5 + 3 * * + 22 +";
    ONPtoResult(object);
    //std::cin >> object;
    //std::cout << ONP(object);
    
    return 0;
}
