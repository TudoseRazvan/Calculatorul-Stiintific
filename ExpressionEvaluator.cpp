#define _CRT_SECURE_NO_WARNINGS

#include "ExpressionEvaluator.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <cctype>
#include <limits>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

double ExpressionEvaluator::applyOperator(double stanga, double dreapta, char op) {
    switch (op) {
    case '+':
        return stanga + dreapta;
    case '-':
        return stanga - dreapta;
    case '*':
        return stanga * dreapta;
    case '/':
        if (dreapta == 0) {
            cerr << "Eroare: Nu exista impartire la zero" << endl;
            return  std::numeric_limits<double>::quiet_NaN();
        }
        return stanga / dreapta;
    case '^':
        return pow(stanga, dreapta);
    case '#':
        return calcRadical(stanga, dreapta);
    default:
        cerr << "Operatorul introdus este necunoscut: " << op << endl;
        return  std::numeric_limits<double>::quiet_NaN();
    }
}

double ExpressionEvaluator::calcRadical(double numar, double exponent) {
    if (numar < 0 || (exponent <= 0)) {
        cerr << "Eroare: Input invalid pentru radical." << endl;
        return std::numeric_limits<double>::quiet_NaN();
    }
    return pow(numar, 1.0 / exponent);
}

//Constructor fara parametri
ExpressionEvaluator::ExpressionEvaluator() : top(-1), expresiePostfixed("") {}

//Constructor cu un parametru string
ExpressionEvaluator::ExpressionEvaluator(const string& expresiePostfixed) : 
    top(-1), expresiePostfixed(expresiePostfixed) {}

//Constructor de copiere
ExpressionEvaluator::ExpressionEvaluator(const ExpressionEvaluator& other)
    : top(other.top), expresiePostfixed(other.expresiePostfixed) {

    for (int i = 0; i <= top; ++i) {
        stack[i] = other.stack[i];
    }
}

//Operator= (de atribuire)
ExpressionEvaluator& ExpressionEvaluator::operator=(const ExpressionEvaluator& other) {
    if (this != &other) {

        top = other.top;
        expresiePostfixed = other.expresiePostfixed;


        for (int i = 0; i <= top; ++i) {
            stack[i] = other.stack[i];
        }
    }
    return *this;
}

//Destructor
ExpressionEvaluator::~ExpressionEvaluator() = default;

const string& ExpressionEvaluator::getExpresiePostfixed() const {
    return expresiePostfixed;
}

void ExpressionEvaluator::setExpresiePostfixed(const string& nouaExpresie) {

    if (nouaExpresie.length() > MAX) {
        throw std::runtime_error("Eroare: Expresia introdusa este prea lunga.");
    }


    for (char c : nouaExpresie) {
        if (!isdigit(c) && !isspace(c) && c != '.' && !ExpressionParser::isOperator(c)) {
            throw std::runtime_error("Eroare: Expresia introdusa contine caractere nepermise.");
        }
    }
    expresiePostfixed = nouaExpresie;
}

double ExpressionEvaluator::eval() {
    if (expresiePostfixed.empty()) return 0;

    char* postfix = new char[expresiePostfixed.length() + 1];
    strcpy(postfix, expresiePostfixed.c_str());

    char* token = strtok(postfix, " ");
    while (token != nullptr) {
        std::istringstream iss(token);
        double num;
        if (iss >> num) {
            stack[++top] = num;
        }
        else if (strlen(token) == 1 && ExpressionParser::isOperator(token[0])) {
            if (top < 1) {
                delete[] postfix;
                throw std::runtime_error("Expresie invalida: prea putini operanzi pentru operator");
            }
            double b = stack[top--];
            double a = stack[top--];
            stack[++top] = applyOperator(a, b, token[0]);
        }
        else {
            delete[] postfix;
            throw std::runtime_error("Expresie invalida: token necunoscut sau incorect");
        }
        token = strtok(nullptr, " ");
    }

    if (top != 0) {
        delete[] postfix;
        throw std::runtime_error("Expresie invalida: dezechilibru intre operatori si operanzi");
    }

    double result = stack[top];
    delete[] postfix;
    return result;
}

// Operator+
ExpressionEvaluator ExpressionEvaluator::operator+(const ExpressionEvaluator& other) const {
    double rezultat1 = stod(expresiePostfixed);
    double rezultat2 = stod(other.expresiePostfixed);
    double rezultatSuma = rezultat1 + rezultat2;
    return ExpressionEvaluator(to_string(rezultatSuma));
}

// Operator-
ExpressionEvaluator ExpressionEvaluator::operator-(const ExpressionEvaluator& other) const {
    double rezultat1 = stod(expresiePostfixed);
    double rezultat2 = stod(other.expresiePostfixed);
    double rezultatDiferenta = rezultat1 - rezultat2;
    return ExpressionEvaluator(to_string(rezultatDiferenta));
}

// Operator/
ExpressionEvaluator ExpressionEvaluator::operator/(const ExpressionEvaluator& other) const {
    double rezultat1 = stod(expresiePostfixed);
    double rezultat2 = stod(other.expresiePostfixed);
    if (rezultat2 == 0) {
        cerr << "Eroare: Impartire la zero!" << endl;
        return ExpressionEvaluator(); // Handle division by zero appropriately
    }
    double rezultatRaport = rezultat1 / rezultat2;
    return ExpressionEvaluator(to_string(rezultatRaport));
}

//Operator! 
bool ExpressionEvaluator::operator!() const {
    return expresiePostfixed.empty();
}

//Operatorul de pre-incrementare
ExpressionEvaluator& ExpressionEvaluator::operator++() {
    double rezultat = eval();
    rezultat++;

    return *this;
}

//Operatorul de post-incrementare
ExpressionEvaluator ExpressionEvaluator::operator++(int) {
    ExpressionEvaluator copie = *this;
    ++(*this);

    return copie;
}

//Supraincarcare operator<< (de citire)
ostream& operator<<(ostream& os, const ExpressionEvaluator& evaluator) {
    os << evaluator.expresiePostfixed;
    return os;
}

//Supraincarcare operator>> (de afisare)
istream& operator>>(istream& in, ExpressionEvaluator& evaluator) {
    cout << "Introduceti expresia postfixata: ";
    string expresiePostfixed;
    getline(in, expresiePostfixed);
    evaluator.setExpresiePostfixed(expresiePostfixed);
    return in;
}