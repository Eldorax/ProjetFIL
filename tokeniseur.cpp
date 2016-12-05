#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "arbre.h"
#include "modele.h"


using namespace std;


int main(int argc, char ** argv)
{
	argc--;
	argv++;
	
	if ( argc < 2 )
	{
		cout << "Mauvaise utilisation :\n	tokeniseur <lexique> <fichier à tokeniser>\n";
		exit(1);
	}
	
	Arbre arbre(argv[0]); //Creation de l'arbre (automatiquement via le constructeur).
	
	//arbre.show();       //Pour afficher les mots construis dans l'arbre.
	
	//Mise en place des séparateurs.	
	unsigned int list_sep[12] = {44, 32, 10, 9, 91, 93, 46, 63, 33, 58, 59, 95};
	vector <unsigned int> sep(0);
	sep.assign(list_sep, list_sep + 12);	

	//Calcule des tokens.
	vector<unsigned int> token_list;
	token_list = arbre.tokenization(argv[1], sep);
	
	//Creation du modele à partir de la liste de tokens
	Modele modele(token_list);
	modele.ShowListToken();    //Affichage dans stdout.

	return 0;
}
