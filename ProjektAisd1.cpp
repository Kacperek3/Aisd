#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>
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

    
    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->previous = top;
        top = newNode;
    }

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

    void display() {
        Node<T>* current = top;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->previous;
        }
        //std::cout << std::endl;
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


String intToChar(int value) {
    String contener = "";
    int numDigits = 1;
    int temp = value;
    while (temp /= 10) {
        ++numDigits;
    }


    while (numDigits-- > 0) {
        temp = value;
        temp = temp / pow(10, numDigits);

        contener = contener + char(temp + '0');
        value = value % int(pow(10, numDigits));

    }

    return contener;
}


struct Data {
    String result;
    int moved;
    int characterNumber;
};
/*
String MaxOrMin(String& tmp, int index) {
    Stack<char> list;
    String result = "";
    int leftBracket = 0;
    int rightBracket = 0;


    for (int i = index; i < tmp.length(); i++) {
        if (tmp.isDigit(i)) {
            if (tmp.isDigit(i + 1)) result = result + tmp[i];//std::cout << tmp[i];
            else result = result + tmp[i] + " ";//std::cout << tmp[i] << " ";
        }
        else if (tmp[i] == ' ') {
            continue;
        }
        else if (tmp[i] == 'M' and tmp[i + 2] == 'X') {
            result = result + MaxOrMin(tmp, i + 5);
            i += 24;

        }
        else if (tmp[i] == ',') {
            while (!list.isEmpty()) {
                result = result + list.peek() + " ";
                list.pop();
            }
        }
        else if (tmp[i] == '(') {
            leftBracket++;
            list.push(tmp[i]);
        }
        else if (tmp[i] == ')') {
            rightBracket++;
            if (rightBracket > leftBracket) {
                result = result + " MAX ";
                return result;
            }

            while (list.peek() != '(') {
                result = result + list.peek() + " ";
                list.pop();
            }
            list.pop();
        }

        else if (tmp[i] == '+' or tmp[i] == '-') {
            while (list.peek() != '(' and !list.isEmpty()) {
                result = result + list.peek() + " ";
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
}
*/

Data MaxOrMin(String& tmp, int index) {

    Data temporaly;
    temporaly.moved = 1;
    temporaly.result = "";
    temporaly.characterNumber = 0;

    Stack<char> list;
    int leftBracket = 0;
    int rightBracket = 0;

    Data returned;

    for (int i = index; i < tmp.length(); i++) {
        temporaly.characterNumber++;
        if (tmp.isDigit(i)) {
            if (tmp.isDigit(i + 1)) temporaly.result = temporaly.result + tmp[i];
            else temporaly.result = temporaly.result + tmp[i] + " ";
        }
        else if (tmp[i] == ' ') {
            continue;
        }
        else if (tmp[i] == 'M' and tmp[i + 2] == 'X') {
            returned = MaxOrMin(tmp, i + 5);
            temporaly.result = temporaly.result + returned.result;
            i += returned.characterNumber + 5;
            temporaly.characterNumber += returned.characterNumber + 5;
        }
        else if (tmp[i] == ',') {
            temporaly.moved++;
            while (!list.isEmpty()) {
                temporaly.result = temporaly.result + list.peek() + " ";
                list.pop();
            }
        }
        else if (tmp[i] == '(') {
            leftBracket++;
            list.push(tmp[i]);
        }
        else if (tmp[i] == ')') {
            rightBracket++;
            String numberOfDigitsToString;
            if (rightBracket > leftBracket) {
                temporaly.result = temporaly.result + "MAX" + intToChar(temporaly.moved) + " ";
                return temporaly;
            }

            while (list.peek() != '(') {
                temporaly.result = temporaly.result + list.peek() + " ";
                list.pop();
            }
            list.pop();
        }

        else if (tmp[i] == '+' or tmp[i] == '-') {
            while (list.peek() != '(' and !list.isEmpty()) {
                temporaly.result = temporaly.result + list.peek() + " ";
                list.pop();
            }
            list.push(tmp[i]);
        }

        else if (tmp[i] == '*' or tmp[i] == '/') list.push(tmp[i]);

    }
    while (!list.isEmpty()) {
        temporaly.result = temporaly.result + list.peek() + " ";
        list.pop();
    }
}

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
        else if (tmp[i] == 'M' and tmp[i+2] == 'X') {




        }
        else if (tmp[i] == '(') list.push(tmp[i]);
        else if (tmp[i] == ')') {
            while (list.peek() != '('){
                result = result + list.peek() + " ";
                list.pop();
            }
            list.pop();
        }
    
        else if (tmp[i] == '+' or tmp[i] == '-') {
            while (list.peek() != '(' and !list.isEmpty()) {
                result = result + list.peek() + " ";
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

            std::cout << "+ ";
            list.display();
            std::cout << std::endl;

            int operand2 = list.pop();
            int operand1 = list.pop();
            list.push(operand1 + operand2);
        }
        else if (tmp[i] == '-') {
            std::cout << "- ";
            list.display();
            std::cout << std::endl;
            int operand2 = list.pop();
            int operand1 = list.pop();
            list.push(operand1 - operand2);
        }
        else if (tmp[i] == '*') {

            std::cout << "* ";
            list.display();
            std::cout << std::endl;

            int operand2 = list.pop();
            int operand1 = list.pop();
            list.push(operand1 * operand2);
        }
        else if (tmp[i] == '/') {

            std::cout << "/ ";
            list.display();
            std::cout << std::endl;

            int operand2 = list.pop();
            int operand1 = list.pop();
            if(operand2 != 0) list.push(operand1 / operand2);
            else {
                std::cout << "ERROR";
                return;
            }
        }
    }

    std::cout << "Wynik: " << list.pop() << std::endl;
}




int main() {
    String object = "MAX ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MAX ( 66 , 36  , 35 , 77 ) , 50 , 60 )";
    String object1 = "2 + MAX ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MAX ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3";
    Data ala = MaxOrMin(object1, 0);
    std::cout << ala.result;
    //std::cin >> object;
    //std::cout << ONP(object);
    //std::cout << pow(10,2);
    
    return 0;
}
