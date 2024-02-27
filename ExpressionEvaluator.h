#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H

#include "ExpressionParser.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class ExpressionEvaluator {
private:
    static const int MAX = 1000;
    double stack[MAX];
    int top;
    string expresiePostfixed;

    double applyOperator(double stanga, double dreapta, char op);
    double calcRadical(double numar, double exponent);

public:
    ExpressionEvaluator();
    ExpressionEvaluator(const string& expresiePostfixed);
    ExpressionEvaluator(const ExpressionEvaluator& other);
    ExpressionEvaluator& operator=(const ExpressionEvaluator& other);
    ~ExpressionEvaluator();

    //Getters si setters
    const string& getExpresiePostfixed() const;
    void setExpresiePostfixed(const string& nouaExpresie);

    // Functia eval() calculeaza expresia postfixata si returneaza rezultatul
    double eval();

    // Supraincarcarea operatorilor
    ExpressionEvaluator operator+(const ExpressionEvaluator& other) const;
    ExpressionEvaluator operator-(const ExpressionEvaluator& other) const;
    ExpressionEvaluator operator/(const ExpressionEvaluator& other) const;
    bool operator!() const;
    ExpressionEvaluator& operator++();
    ExpressionEvaluator operator++(int);
    friend ostream& operator<<(ostream& os, const ExpressionEvaluator& evaluator);
    friend istream& operator>>(istream& in, ExpressionEvaluator& evaluator);
};

#endif // EXPRESSIONEVALUATOR_H