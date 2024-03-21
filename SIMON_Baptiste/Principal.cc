#include "Noeud.h"
#include <iostream>
using namespace std;


int main() {
    Arbre a1;
    Noeud* n;
    string variable;
    string expression;

    while (true){
      cout << "entrez une variable ou (q pour quitter): ";
      cin >> variable;

      if (variable == "q"){
        return 0;
      }

      cout << "entrez une expression : ";
      cin >> expression;

      cout << "Arbre pour "<< variable << " = " << expression <<":" << endl;
      n = a1.construireArbre(expression);

      a1.afficherArbre(n, 0);
      cout << endl;
      a1.affecterVariable(variable, a1.evaluateTree(n));
      cout << endl;
      a1.libererArbre(n);

      cout << variable << " = " << a1.variables[variable] << endl;
    }


    return 0;
}
