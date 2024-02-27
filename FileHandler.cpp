#include "FileHandler.h"
#include "InterfataCalculator.h"
#include <exception>

FileHandler::FileHandler(InterfataCalculator& calc) : ultimulRezultat(0.0), calculator(calc) {
}

void FileHandler::SalvareRezultatInFisierBinar(const string& numeFisier) {
    ofstream fisierOut(numeFisier, ios::binary);
    if (fisierOut.is_open()) {
        fisierOut.write(reinterpret_cast<const char*>(&calculator.ultimulRezultat), sizeof(calculator.ultimulRezultat));
        fisierOut.close();
        cout << "Rezultatul a fost salvat in fisierul binar '" << numeFisier << "'" << endl;
    }
    else {
        cerr << "Eroare: Nu s-a putut deschide fisierul '" << numeFisier << "' pentru salvare." << endl;
    }
}

void FileHandler::IncarcareRezultatDinFisierBinar(const std::string& numeFisier) {
    ifstream fisierIn(numeFisier, ios::binary);
    if (fisierIn.is_open()) {
        fisierIn.read(reinterpret_cast<char*>(&calculator.ultimulRezultat), sizeof(calculator.ultimulRezultat));
        fisierIn.close();
        cout << "Rezultatul a fost incarcat din fisierul binar '" << numeFisier << "'" << endl;
        cout << "Rezultat incarcat din fisier: " << calculator.ultimulRezultat << endl;
    }
    else {
        cerr << "Eroare: Nu s-a putut deschide fisierul '" << numeFisier << "' pentru încărcare." << endl;
    }
}

void FileHandler::CitireSiProcesareEcuatiiDinFisier(const string& numeFisier) {
    ifstream fisier(numeFisier);
    string ecuatie;
    if (!fisier.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul '" << numeFisier << "'." << endl;
        return;
    }

    string optiune;
    cout << "Doriti sa afisati rezultatele la consola sau sa le salvati intr-un fisier? (consola/fisier): ";
    cin >> optiune;
    cin.ignore();

    ofstream fisierRezultate;

    if (optiune == "fisier") {
        string numeFisierRezultate;
        cout << "Introduceti numele fisierului pentru rezultate: ";
        getline(cin, numeFisierRezultate);
        fisierRezultate.open(numeFisierRezultate);
    }

    double rezultatAnterior = 0.0;
    while (getline(fisier, ecuatie)) {
        if (ecuatie.empty() || ecuatie[0] == '#') continue;
        try {
            procesareEcuatie(ecuatie);

            if (ultimulRezultat != rezultatAnterior) {
                if (optiune == "consola") {
                    cout << "Rezultat: " << ultimulRezultat << endl;
                }

                if (optiune == "fisier") {
                    fisierRezultate << "Rezultat: " << ultimulRezultat << "\n";
                }
                rezultatAnterior = ultimulRezultat;
            }
        }
        catch (const exception& e) {
            cerr << "Eroare la procesarea ecuatiei: " << e.what() << endl;
            if (optiune == "fisier") {
                fisierRezultate << "Eroare la procesarea ecuatiei: " << e.what() << "\n";
            }
        }
    }

    fisier.close();
    if (optiune == "fisier") {
        fisierRezultate.close();
    }
}

void FileHandler::ScriereRezultateInFisier(const string& numeFisier, const vector<string>& rezultate) {
    ofstream fisier(numeFisier);

    if (!fisier.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul '" << numeFisier << "' pentru scriere." << endl;
        return;
    }

    for (const string& rezultat : rezultate) {
        fisier << rezultat << endl;
    }

    fisier.close();
    cout << "Rezultatele au fost scrise in fisierul '" << numeFisier << "'" << endl;
}

void FileHandler::procesareEcuatie(const string& ecuatie) {
    try {
        calculator.parser = ExpressionParser(ecuatie);
        calculator.expresieCurenta = calculator.parser.convertToPostfix();
        calculator.evaluator = ExpressionEvaluator(calculator.expresieCurenta);
        double rezultat = calculator.evaluator.eval();
        calculator.ultimulRezultat = rezultat; // Setează ultimulRezultat al calculatorului
        cout << "Rezultat: " << rezultat << endl;
    }
    catch (const exception& e) {
        cerr << "Eroare: " << e.what() << endl;
    }
}