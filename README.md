# Calculator Științific C++

Bun venit pe pagina proiectului meu de Calculator Științific implementat în C++! Acesta este un proiect care vine în întâmpinarea pasionaților de programare și matematică, oferindu-le un instrument simplu și versatil pentru evaluarea expresiilor matematice.

Proiectul este construit în totalitate cu ajutorul Programării Orientate pe Obiect (POO), punând accent pe utilizarea claselor și a obiectelor pentru o structură și reutilizare eficientă a codului. Implementarea în C++ a permis crearea unui cod ușor de înțeles și de întreținut, oferind totodată o bază solidă pentru extinderea funcționalităților viitoare.

## Descriere Generală

Acest calculator este capabil să manipuleze expresii matematice complexe, inclusiv paranteze rotunde și pătrate, puteri, rădăcini și toate operațiile de bază. Prin intermediul unui meniu interactiv, utilizatorul poate introduce ecuații, iar calculatorul va afișa rezultatele într-un mod intuitiv.

## Caracteristici Cheie

- **Evaluare Expresii:** Capacitatea de a evalua expresii matematice complexe, oferind rezultate precise.

- **Operații Suportate:** Adunare, scădere, înmulțire, împărțire, putere, radical.

- **Ecuații și Variabile:** Suport pentru introducerea de ecuații și salvarea rezultatelor în variabile pentru utilizare ulterioară.

- **Tratarea Erorilor și a Excepțiilor:** Manejarea și afișarea mesajelor de eroare pentru expresii invalide sau operații nedefinite.

- **Fisiere Text și Binare:** Salvarea și citirea rezultatelor în/din fișiere text și binare pentru stocare și acces ulterior.

## Utilizare

Pentru a utiliza calculatorul, puteți:
- Introduce ecuații direct de la tastatură.
- Furniza ecuația ca parametru în linia de comandă.
- Citirea ecuațiilor dintr-un fișier text și afișarea rezultatelor.
- Salvarea și citirea rezultatelor în/din fișiere text și binare pentru acces ulterior.

## Exemple de Utilizare

### Evaluare Expresii Complicate:

- Ecuație: `[(2^6)^4 / 2^3*(2^6+2^6)-4^6 / 2^10] / (2^28-2^2)+9`, unde `x^y` înseamnă `x` la puterea `y` și `x#y` radical de ordinul `y` din `x`.
  - Rezultat: 10

- Ecuație: `5 / 0`
  - Rezultat: Va afișa eroare deoarece împărțirea la 0 nu are sens.

- Ecuație: `24342343.0002-3`
  - Rezultat: 24342340.0002

- Ecuație: `2 *    3 - 8`
  - Rezultat: -2

- Ecuație: `(0.425.242 ^ 7)`
  - Rezultat: Va afișa eroare deoarece primul număr nu este valid.

- Ecuație: `[(100000.2 * 1.12) ^ (1.23 + 0.298)] # [(99999 / 3.3) - (1.9754 - 4.162673761)]`
  - Rezultat: 1.0005863777

### Utilizare Variabile:

- Ecuație 1: `x = 5 * (2^3)` (variabila `x` acum conține 40)
- Ecuație 2: `y = x^2 + 10`
  - Rezultat: `y` este acum 1610.

## Gestionarea Fișierelor Text/Binare - FileHandler

`FileHandler` reprezintă un mod eficient de a gestiona operațiunile cu fișiere text și binare în cadrul proiectului Calculatorului Științific. Această componentă esențială permite salvarea și încărcarea rezultatelor, precum și citirea și procesarea ecuațiilor din fișiere externe.

### Salvare și Încărcare în Format Binar

Cu ajutorul funcționalității de salvare și încărcare în format binar, utilizatorul poate reține și recupera rezultatele anterioare ale calculatorului. Această opțiune oferă portabilitate și ușurință în gestionarea datelor, fiind utilă în situații precum reînceperea unei sesiuni de lucru sau partajarea rezultatelor între diferite execuții ale programului.

### Citire și Procesare a Ecuatiilor din Fișier

`FileHandler` facilitează citirea și procesarea eficientă a ecuațiilor din fișiere externe. Utilizatorul poate introduce ecuații pe linii separate într-un fișier text, iar apoi programul le procesează, afișează rezultatele sau le salvează în alt fișier. Această funcționalitate aduce un nivel de automatizare și flexibilitate în utilizarea calculatorului, facilitând manipularea unui număr mare de ecuații.

## Cum Rulezi Proiectul

1. Clonează acest repository.
2. Compilează și rulează proiectul folosind compilatorul C++ preferat.

## Contribuții/Sugestii

Dacă ai sugestii de îmbunătățiri sau descoperi probleme, te rog să deschizi un issue sau să trimiți un pull request. Contribuțiile sunt binevenite!

## Licență

Acest proiect este licențiat sub Licența MIT, ceea ce înseamnă că îl poți utiliza și modifica liber, cu menținerea drepturilor de autor.

Sper că acest calculator iți va fi de folos și iți va stârni curiozitatea pentru explorarea matematicii și programării!
