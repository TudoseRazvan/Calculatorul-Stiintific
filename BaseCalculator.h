#ifndef BASECALCULATOR_H
#define BASECALCULATOR_H

#include <iostream>
using namespace std;

class BaseCalculator {
public:
    virtual void executare() = 0;

    virtual void afisareMesajInitial() const {
        cout << "Bine ati venit la Calculatorul Stiintific!" << endl;
    }

    virtual void afisareMesajIesire() const {
        cout << "\nVa mai asteptam!" << endl;
    }

};

#endif // BASECALCULATOR_H