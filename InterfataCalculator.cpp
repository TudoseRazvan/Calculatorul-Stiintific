#include "InterfataCalculator.h"

InterfataCalculator::InterfataCalculator() : BaseCalculator(), ultimulRezultat(0.0) {}

const string InterfataCalculator::mesajInitial = "Bine ati venit la Calculatorul Stiintific!";
void InterfataCalculator::afisareMesajInitial() const {
    cout << mesajInitial << endl;
}

const string InterfataCalculator::mesajIesire = "Va mai asteptam!";
void InterfataCalculator::afisareMesajIesire() const {
    cout << endl << mesajIesire << endl;
}

const string InterfataCalculator::IndicatiiUtilizator = "Introduceti expresia si apasati Enter. Scrie 'exit' pentru a iesi.";
void InterfataCalculator::afisareIndicatiiUtilizator() const {
    cout << IndicatiiUtilizator << endl;
}

string InterfataCalculator::getExpresieCurenta() const {
    return expresieCurenta;
}

void InterfataCalculator::setExpresieCurenta(const string& nouaExpresie) {

    if (nouaExpresie.length() > 1000) {
        cout << "Expresia introdusa este prea lunga. Limita maxima este de 1000 de caractere." << endl;
        return;
    }
    if (nouaExpresie.find_first_not_of("0123456789+-*/^()[]#., ") != string::npos) {
        cout << "Expresia introdusa contine caractere nepermise." << endl;
        return;
    }
    expresieCurenta = nouaExpresie;
}

void InterfataCalculator::run() {
    string input;
    while (true) {
        cout << "\nExpresie: ";
        getline(cin, input);

        if (input == "exit") {
            cout << mesajIesire << endl;
            break;
        }

        try {
            parser = ExpressionParser(input);
            expresieCurenta = parser.convertToPostfix();
            evaluator = ExpressionEvaluator(expresieCurenta);
            double rezultat = evaluator.eval();
            if (rezultat == 0)
            {
                rezultat = 0;
            }


            std::ostringstream oss;
            oss << std::fixed << std::setprecision(10) << rezultat;
            string rezultatFormatat = oss.str();


            rezultatFormatat.erase(rezultatFormatat.find_last_not_of('0') + 1, std::string::npos);
            if (rezultatFormatat.back() == '.') {
                rezultatFormatat.pop_back();
            }

            cout << "Rezultat: " << rezultatFormatat << endl;
        }
        catch (const exception& e) {
            cout << "Eroare: " << e.what() << endl;
        }
    }
}

void InterfataCalculator::procesareEcuatie(const string& ecuatie) {
    try {
        parser = ExpressionParser(ecuatie);
        expresieCurenta = parser.convertToPostfix();
        evaluator = ExpressionEvaluator(expresieCurenta);
        double rezultat = evaluator.eval();
        ultimulRezultat = rezultat; 
        cout << "Rezultat: " << rezultat << endl;
    }
    catch (const exception& e) {
        cout << "Eroare: " << e.what() << endl;
    }
}

void InterfataCalculator::afisareMeniu() {
    cout << "\nMeniu:" << endl;
    cout << "1. Introducere ecuatie" << endl;
    cout << "2. Citire ecuatii din fisier" << endl;
    cout << "3. Salvarea ultimului rezultat" << endl;
    cout << "4. Incarcarea unui rezultat salvat" << endl;
    cout << "5. Iesire" << endl;
    cout << "Alegeti o optiune: ";
}

void InterfataCalculator::executareAlegereUtilizator(int alegere) {
    FileHandler fileHandler(*this); //Paseaza o referinta la instanta curenta a clasei

    switch (alegere) {
    case 1:
    {
        string ecuatie;
        while (true) {
            cout << "Introduceti ecuatia (sau 'exit' pentru a reveni la meniu): ";
            getline(cin, ecuatie);

            if (ecuatie == "exit") {
                break;
            }

            procesareEcuatie(ecuatie);
        }
    }
    break;
    case 2:
    {
        string numeFisier;
        cout << "Introduceti numele fisierului: ";
        getline(cin, numeFisier);
        fileHandler.CitireSiProcesareEcuatiiDinFisier(numeFisier);
    }
    break;
    case 3:
    {
        string numeFisier;
        cout << "Introduceti numele fisierului pentru salvare: ";
        getline(cin, numeFisier);
        fileHandler.SalvareRezultatInFisierBinar(numeFisier);
    }
    break;
    case 4:
    {
        string numeFisier;
        cout << "Introduceti numele fisierului pentru incarcare: ";
        getline(cin, numeFisier);
        fileHandler.IncarcareRezultatDinFisierBinar(numeFisier);
    }
    break;
    case 5:
        cout << "Iesire din program." << endl;
        exit(0);
        break;
    default:
        cout << "Optiunea este invalida!" << endl;
    }
}

//Supraincarcare operator*
int InterfataCalculator::operator*(const InterfataCalculator& other) const {
    return this->expresieCurenta.length() * other.expresieCurenta.length();
}

//Supraincarcare operator>
bool InterfataCalculator::operator>(const InterfataCalculator& other) const {
    return this->expresieCurenta.length() > other.expresieCurenta.length();
}

//Supraincarcare operator<< (afisare)
ostream& operator<<(ostream& os, const InterfataCalculator& interfata)
{
    os << "Expresie Curenta: " << interfata.getExpresieCurenta();
    return os;
}

//Supraincarcare operator>> (citire)
istream& operator>>(istream& in, InterfataCalculator& interfata) {
    cout << "Introduceti expresia: ";
    string expresie;
    getline(in, expresie);
    interfata.setExpresieCurenta(expresie);
    return in;
}

void InterfataCalculator::executare() {
    while (true) {
        afisareMeniu();
        int alegere;
        if (!(cin >> alegere)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Input invalid. Introduceti un numar." << endl;
            continue;
        }
        cin.ignore(); 

        if (alegere == 5) {
            break;
        }

        executareAlegereUtilizator(alegere);
    }
}
