#ifndef INTERFATACALCULATOR_H
#define INTERFATACALCULATOR_H
#include "BaseCalculator.h"
#include "ExpressionParser.h"
#include "ExpressionEvaluator.h"
#include "FileHandler.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

class InterfataCalculator : public BaseCalculator {
    friend class FileHandler;
private:
    ExpressionEvaluator evaluator;
    ExpressionParser parser;
    string expresieCurenta;

    static const string mesajInitial;
    static const string IndicatiiUtilizator;
    static const string mesajIesire;

    double ultimulRezultat;
    int fileHandlerPlaceholder;

public:
    InterfataCalculator();
    InterfataCalculator(const InterfataCalculator& other) = default;

    // Metode pentru afisare si interactiune cu utilizatorul
    void afisareMesajInitial() const;
    void afisareIndicatiiUtilizator() const;
    void afisareMesajIesire() const;

    // Getters si setters
    string getExpresieCurenta() const;
    void setExpresieCurenta(const string& nouaExpresie);

    void run();
    void procesareEcuatie(const string& ecuatie);
    void afisareMeniu();
    void executareAlegereUtilizator(int alegere);

    // Supraincarcarea operatorilor
    bool operator>(const InterfataCalculator& other) const;
    int operator*(const InterfataCalculator& other) const;
    friend ostream& operator<<(ostream& os, const InterfataCalculator);
    friend istream& operator>>(istream& in, InterfataCalculator& interfata);

    void executare() override;
};

#endif // INTERFATACALCULATOR_H
