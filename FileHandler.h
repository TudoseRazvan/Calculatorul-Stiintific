#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "InterfataCalculator.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class FileHandler {
    friend class InterfataCalculator;
private:
    double ultimulRezultat;
    InterfataCalculator& calculator; 
public:
    FileHandler();
    FileHandler(InterfataCalculator& calc);
    void procesareEcuatie(const string& ecuatie);

    //Metode pentru gestionarea fisierelor
    void SalvareRezultatInFisierBinar(const std::string& numeFisier);
    void IncarcareRezultatDinFisierBinar(const std::string& numeFisier);
    void CitireSiProcesareEcuatiiDinFisier(const string& numeFisier);
    void ScriereRezultateInFisier(const string& numeFisier, const vector<string>& rezultate);
};

#endif // FILEHANDLER_H
