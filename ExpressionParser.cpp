﻿#define _CRT_SECURE_NO_WARNINGS
#include "ExpressionParser.h"

bool ExpressionParser::isCharacterValid(char ch) {
    return isdigit(ch) || isOperator(ch) || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '.' || ch == '^' || ch == '#';
}

bool ExpressionParser::isParenthesesBalanced(const string& expresie) {
    char stack[MAX];
    int top = -1;
    for (char c : expresie) {
        if (c == '(' || c == '[') {
            stack[++top] = c;
        }
        else if (c == ')' || c == ']') {
            if (top == -1 || (c == ')' && stack[top] != '(') || (c == ']' && stack[top] != '[')) return false;
            top--;
        }
    }
    return top == -1;
}

int ExpressionParser::prioritate(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^' || op == '#') return 3;
    return 0;
}

bool ExpressionParser::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '#';
}

//Constructor fara parametri
ExpressionParser::ExpressionParser() : expresie(new char[MAX]()) {}

//Constructor cu parametru
ExpressionParser::ExpressionParser(const string& str) : expresie(new char[MAX]()) {
    strncpy(expresie, str.c_str(), MAX);
}

//Destructor
ExpressionParser::~ExpressionParser() {
    delete[] expresie;
}

//Constructor de copiere
ExpressionParser::ExpressionParser(const ExpressionParser& other) : expresie(new char[MAX]()) {
    strncpy(expresie, other.expresie, MAX);
}

//Operator= (de atribuire)
ExpressionParser& ExpressionParser::operator=(const ExpressionParser& other) {
    if (this != &other) {
        delete[] expresie;
        expresie = new char[MAX]();
        strncpy(expresie, other.expresie, MAX);
    }
    return *this;
}

//Getter
string ExpressionParser::getExpresie() const {
    return string(expresie);
}

//Setter
void ExpressionParser::setExpresie(const string& nouaExpresie) {
    if (nouaExpresie.length() >= MAX) {
        cerr << "Eroare: expresia introdusa este prea lunga. Maxim permis: " << MAX - 1 << " caractere." << endl;

        return;
    }
    strncpy(expresie, nouaExpresie.c_str(), MAX);
    expresie[MAX - 1] = '\0';
}

string ExpressionParser::convertToPostfix() {
    char stack[MAX];
    int top = -1;
    string postfix;
    string numarCurent;

    for (int i = 0; i < strlen(expresie); ++i) {
        char c = expresie[i];
        if (isCharacterValidForExpression(c) || (c == '.' && i > 0 && isdigit(expresie[i - 1]))) {
            numarCurent += c;
        }
        else {
            if (!numarCurent.empty()) {
                if (!isNumberValid(numarCurent)) {
                    throw std::runtime_error("Numarul introdus este invalid: " + numarCurent);
                }
                postfix += numarCurent + ' ';
                numarCurent.clear();
            }

            if (c == '(' || c == '[') {
                stack[++top] = c;
            }
            else if (c == ')' || c == ']') {
                char coresp = (c == ')') ? '(' : '[';
                while (top != -1 && stack[top] != coresp) {
                    postfix += stack[top--];
                    postfix += ' ';
                }
                top--;
            }
            else if (isOperator(c)) {
                while (top != -1 && prioritate(stack[top]) >= prioritate(c)) {
                    postfix += stack[top--];
                    postfix += ' ';
                }
                stack[++top] = c;
            }
        }
    }


    if (!numarCurent.empty()) {
        if (!isNumberValid(numarCurent)) {
            throw std::runtime_error("Numar invalid: " + numarCurent);
        }
        postfix += numarCurent + ' ';
    }


    while (top != -1) {
        postfix += stack[top--];
        postfix += ' ';
    }

    return postfix;
}

bool ExpressionParser::isNumberValid(const string& numar) {
    int countPuncte = 0;
    for (char c : numar) {
        if (c == '.') {
            countPuncte++;
            if (countPuncte > 1) {
                return false;
            }
        }
        else if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

//Operator[] (de indexare)
const char& ExpressionParser::operator[](int index) const {
    if (index >= 0 && index < strlen(expresie)) {
        return expresie[index];
    }
    throw std::out_of_range("Index invalid");
}

//Conversie la string
ExpressionParser::operator string() const {
    return string(expresie);
}

//Metoda statica
bool ExpressionParser::isCharacterValidForExpression(char c) {
    return isdigit(c) || isalpha(c) || c == '.';
}

//Operator<< (de citire)
ostream& operator<<(ostream& os, const ExpressionParser& parser) {
    os << parser.expresie;
    return os;
}

//Operator>> (de afisare)
istream& operator>>(istream& in, ExpressionParser& parser) {
    cout << "Introduceti expresia: ";
    string expresie;
    getline(in, expresie);
    parser.setExpresie(expresie);
    return in;
}