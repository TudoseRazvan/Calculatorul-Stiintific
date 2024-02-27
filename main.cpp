#include "InterfataCalculator.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    InterfataCalculator calculator;

    calculator.afisareMesajInitial();

    if (argc > 1) {
        string ecuatie = argv[1];
        calculator.procesareEcuatie(ecuatie);
    }
    else {
        calculator.executare();
    }

    calculator.afisareMesajIesire();

    return 0;
}
