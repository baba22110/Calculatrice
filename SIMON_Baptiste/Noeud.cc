#include "Noeud.h"
#include <iostream>
#include <cctype>
using namespace std;


Noeud::Noeud(const string& val) : valeur(val), gauche(nullptr), droite(nullptr) {}

// La classe Arbre

int Arbre::evaluateTree(Noeud* noeud) {

    if (isdigit(noeud->valeur[0]) || (noeud->valeur[0] == '-' && isdigit(noeud->valeur[1]))) { // Si la valeur est un nombre
        return stoi(noeud->valeur);

    } else if (isalpha(noeud->valeur[0])) { // Si la valeur est une variable

        if (variables.find(noeud->valeur) != variables.end()) { // La variable existe

            return variables[noeud->valeur];

        } else {

            cerr << "Erreur : variable '" << noeud->valeur << "' non définie." << endl;
            exit(EXIT_FAILURE);
        }
    } else {
        int gaucheValeur = evaluateTree(noeud->gauche);
        int droiteValeur = evaluateTree(noeud->droite);

        cout << gaucheValeur << noeud->valeur << droiteValeur << endl;

        if (!noeud->valeur.empty()) {
            if (noeud->valeur == "+") {
                return gaucheValeur + droiteValeur;
            } else if (noeud->valeur == "-") {
                return gaucheValeur - droiteValeur;
            } else if (noeud->valeur == "*") {
                return gaucheValeur * droiteValeur;
            } else if (noeud->valeur == "/") {
                if (droiteValeur != 0) {
                    return gaucheValeur / droiteValeur;
                } else {
                    cerr << "Erreur : division par zéro." << endl;
                    exit(EXIT_FAILURE);
                }
            } else if (noeud->valeur == "%") {
                if (droiteValeur != 0) {
                    return gaucheValeur % droiteValeur;
                } else {
                    cerr << "Erreur : modulo par zéro." << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    cerr << "Erreur : opérateur non reconnu." << endl;
    exit(EXIT_FAILURE);
}

void Arbre::afficherArbre(Noeud* noeud, int niveau) {
    if (noeud != nullptr) {
        afficherArbre(noeud->droite, niveau + 1);

        for (int i = 0; i < niveau; i++) {
            cout << "   ";
        }

        cout << noeud->valeur << endl;

        afficherArbre(noeud->gauche, niveau + 1);
    }
}

int Arbre::trouverParentheseFermante(const string& expression, int posOuverture) {
    int nbParenthesesOuvrante = 1;
    int pos = posOuverture + 1;

    while (nbParenthesesOuvrante > 0 && pos < expression.length()) {
        if (expression[pos] == '(') {
            nbParenthesesOuvrante++;
        } else if (expression[pos] == ')') {
            nbParenthesesOuvrante--;
        }
        pos++;
    }

    if (nbParenthesesOuvrante > 0) {
        cerr << "Erreur : parenthèses non équilibrées." << endl;
        exit(EXIT_FAILURE);
    }

    return pos - 1;
}

Noeud* Arbre::construireArbre(string expression) {
    Noeud* noeud = new Noeud("");

    // Retirer les parenthèses non nécessaires
    while (!expression.empty() && expression[0] == '(' && trouverParentheseFermante(expression, 0) == expression.length() - 1) {
        expression = expression.substr(1, expression.length() - 2);
    }

    size_t pos = expression.find_first_of("(");
    if (pos != std::string::npos) {
        int posFermante = trouverParentheseFermante(expression, pos);

        if (pos == 0) {
            noeud->gauche = construireArbre(expression.substr(1, posFermante - 1));

            if (posFermante + 1 <= expression.length()) {
                noeud->valeur = expression.substr(posFermante + 1, 1);

                if (posFermante + 2 <= expression.length()) {
                    noeud->droite = construireArbre(expression.substr(posFermante + 2));
                }
            }
        } else {
            noeud->gauche = construireArbre(expression.substr(0, pos - 1));

            noeud->valeur = expression.substr(pos - 1, 1);

            if (pos+1 <= expression.length()) {
                noeud->droite = construireArbre(expression.substr(pos));
            }

        }
    } else {
        size_t posOperateur = expression.find_first_of("*/%+-");

        if (posOperateur != std::string::npos) {
            noeud->valeur = expression.substr(posOperateur, 1);

            noeud->gauche = construireArbre(expression.substr(0, posOperateur));

            noeud->droite = construireArbre(expression.substr(posOperateur + 1));
        } else {
            noeud->valeur = expression;
        }
    }
    return noeud;
}

void Arbre::libererArbre(Noeud* noeud) {
    if (noeud != nullptr) {
        libererArbre(noeud->gauche);
        libererArbre(noeud->droite);
        delete noeud;
    }
}

void Arbre::affecterVariable(const string& variable, int valeur) {
    this->variables[variable] = valeur;
}
