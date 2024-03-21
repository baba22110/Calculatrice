#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H
#include <string>
#include <map>
using namespace std;

struct Noeud {
    std::string valeur;
    Noeud* gauche;
    Noeud* droite;

    Noeud(const std::string&);
};

class Arbre {
public:
    map<string, int> variables;

    int evaluateTree(Noeud* noeud);
    void afficherArbre(Noeud* noeud, int niveau);
    int trouverParentheseFermante(const string& expression, int posOuverture);
    Noeud* construireArbre(string expression);
    void libererArbre(Noeud* noeud);
    void affecterVariable(const string& variable, int valeur);
};


#endif
