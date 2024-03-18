#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>
#define MIN 0
#define MAX 1
#define IF 2

template <typename T>
struct Node {
    T data;
    Node<T>* previous;

    Node(T value) : data(value), previous(nullptr) {}
};

template <typename T>
class Stack {
private:
    Node<T>* top; 

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

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
            return -1;
        }
        T value = top->data;
        Node<T>* temp = top;
        top = top->previous;
        delete temp;
        return value;
    }

    T peek() {
        if (isEmpty()) {
            return -1;
        }
        return top->data;
    }

    void display() {
        Node<T>* current = top;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->previous;
        }
    }
    void reverse() {
        if (isEmpty() || top->previous == nullptr) {
            return;
        }

        Node<T>* prevNode = nullptr;
        Node<T>* current = top;
        Node<T>* nextNode;

        while (current != nullptr) {
            nextNode = current->previous;
            current->previous = prevNode;
            prevNode = current;
            current = nextNode;
        }

        top = prevNode;
    }
    T min() {
        if (isEmpty()) {
            std::cerr << "Stack is empty." << std::endl;
            return T(); // Zwróć wartość domyślną dla typu T
        }
        Node<T>* current = top;
        T minVal = current->data;
        while (current != nullptr) {
            if (current->data < minVal) {
                minVal = current->data;
            }
            current = current->previous;
        }
        return minVal;
    }

    T max() {
        if (isEmpty()) {
            std::cerr << "Stack is empty." << std::endl;
            return T(); // Zwróć wartość domyślną dla typu T
        }
        Node<T>* current = top;
        T maxVal = current->data;
        while (current != nullptr) {
            if (current->data > maxVal) {
                maxVal = current->data;
            }
            current = current->previous;
        }
        return maxVal;
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

Data MaxOrMin(String& tmp, int index, int Max) {
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
            returned = MaxOrMin(tmp, i + 5, MAX);
            temporaly.result = temporaly.result + returned.result;
            i += returned.characterNumber + 5;
            temporaly.characterNumber += returned.characterNumber + 5;
        }
        else if (tmp[i] == 'M' and tmp[i + 2] == 'N') {
            returned = MaxOrMin(tmp, i + 5, MIN);
            temporaly.result = temporaly.result + returned.result;
            i += returned.characterNumber + 5;
            temporaly.characterNumber += returned.characterNumber + 5;
        }
        else if (tmp[i] == 'I' and tmp[i + 1] == 'F') {
            returned = MaxOrMin(tmp, i + 4, IF);
            temporaly.result = temporaly.result + returned.result;
            i += returned.characterNumber + 4;
            temporaly.characterNumber += returned.characterNumber + 4;
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
                while (!list.isEmpty()) {
                    temporaly.result = temporaly.result + list.peek() + " ";
                    list.pop();
                }
                if(Max == MAX) temporaly.result = temporaly.result + "MAX" + intToChar(temporaly.moved) + " ";
                else if(Max == MIN) temporaly.result = temporaly.result + "MIN" + intToChar(temporaly.moved) + " ";
                else temporaly.result = temporaly.result + "IF" + " ";
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

        else if (tmp[i] == '*' or tmp[i] == '/') {
            while (list.peek() != '(' and list.peek() != '+' and list.peek() != '-' and !list.isEmpty()) {
                temporaly.result = temporaly.result + list.peek() + " ";
                list.pop();
            }
            list.push(tmp[i]);
        }

        else if (tmp[i] == 'N') list.push(tmp[i]);


    }
    while (!list.isEmpty()) {
        temporaly.result = temporaly.result + list.peek() + " ";
        list.pop();
    }
    return temporaly;
}

int ONPtoResult(String& tmp) {
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
                return 2004;
            }
        }
        else if (tmp[i] == 'N') {

            std::cout << "N ";
            list.display();
            std::cout << std::endl;

            int operand1 = list.pop();
            list.push(operand1 * (-1));
            
        }

        else if (tmp[i] == 'I' and tmp[i + 1] == 'F') {

            std::cout << "IF ";
            list.display();
            std::cout << std::endl;

            int operand1 = list.pop();
            int operand2 = list.pop();
            int operand3 = list.pop();
            
            if(operand3 > 0) list.push(operand2);
            else list.push(operand1);
            i += 2;
        }
        else if (tmp[i] == 'M' and tmp[i + 2] == 'X') {
            
            String a = "";
            Stack<int> max;
            int t = i + 3;
            int digits;
            int lenght = tmp.length();
            while (tmp[t] != ' ' and t < tmp.length()) {

                a = a + tmp[t];
                t++;
            }
            int number = 0;

            for (int j = 0; j < a.length(); j++) {
                number = number * 10 + (a[j] - '0');
            }
            std::cout << "MAX" << number << " ";
            list.display();
            for (int j = 0; j < number; j++) {
                max.push(list.pop());
            }
            max.reverse();
            list.push(max.max());
            std::cout << std::endl;
            i += 3 + a.length();
        }
        else if (tmp[i] == 'M' and tmp[i + 2] == 'N') {

            String a = "";
            Stack<int> max;
            int t = i + 3;
            int digits;
            int lenght = tmp.length();
            while (tmp[t] != ' ' and t < tmp.length()) {

                a = a + tmp[t];
                t++;
            }
            int number = 0;

            for (int j = 0; j < a.length(); j++) {
                number = number * 10 + (a[j] - '0');
            }
            std::cout << "MIN" << number << " ";
            list.display();
            for (int j = 0; j < number; j++) {
                max.push(list.pop());
            }
            max.reverse();
            list.push(max.min());
            std::cout << std::endl;
            i += 3 + a.length();
        }
    }

    return list.pop();
}



int main() {
    int n;
    scanf_s("%d", &n); // Read the number of inputs
    getchar(); // Consume the newline character after reading 'n'

    char buffer[100]; // Assuming a maximum input length of 100 characters
    int result;
    for (int i = 0; i < n; i++) {
        scanf_s("%s", buffer); // Read a string into buffer
        String object(buffer); // Convert the C-style string to your custom String object
        Data ala = MaxOrMin(object, 0, 0); // Process the input string
        printf_s("%s\n", ala.result); // Print the result
        result = ONPtoResult(ala.result); // Compute the result
        if (result != 2004)
            printf_s("%d\n\n", result); // Print the result if it's not 2004
        else
            printf_s("\n\n"); // Otherwise, print newlines
    }

    return 0;
}

