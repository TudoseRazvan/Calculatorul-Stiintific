#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <iostream>
#include <cstring>
#include <string>
#include <cctype>

using namespace std;

class ExpressionParser {
    friend class ExpressionEvaluator;
private:
    char* expresie;
    static const int MAX = 1000;

    int prioritate(char op);
    bool isParenthesesBalanced(const string& expresie);
    static bool isCharacterValid(char ch);
    static bool isOperator(char c);

public:
    ExpressionParser();
    ExpressionParser(const string& str);
    ExpressionParser(const ExpressionParser& other);
    ExpressionParser& operator=(const ExpressionParser& other);
    ~ExpressionParser();

    //Getters si setters
    string getExpresie() const;
    void setExpresie(const string& nouaExpresie);

    string convertToPostfix();
    static bool isCharacterValidForExpression(char c);

    //Supraincarcarea operatorilor
    const char& operator[](int index) const;
    explicit operator string() const;
    static bool isNumberValid(const string& numar);
    friend ostream& operator<<(ostream& os, const ExpressionParser& parser);
    friend istream& operator>>(istream& in, ExpressionParser& parser);
};

#endif // EXPRESSIONPARSER_H