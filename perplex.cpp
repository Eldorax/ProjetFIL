#include <string>
#include <stdlib.h>

#include "elementArbre.h"
#include "arbre.h"
#include "modele.h"
#include <vector>
#include "translation.h"

using namespace std;


int main(int argc, char ** argv)
{
	argc--;
	argv++;
	
	if ( argc < 3 )
	{
		cout << "Mauvaise utilisation :\n	perplex.exe <lexique> <corpus> <fichier à calcule (une phrase par ligne)>\n";
		exit(1);
	}

	Arbre arbre(argv[0]); //creation de l'arbre.

	//Initialisation des séparateurs.
	unsigned int list_sep[12] = {44, 32, 10, 9, 91, 93, 46, 63, 33, 58, 59, 95};
	vector <unsigned int> sep(0);
	sep.assign(list_sep, list_sep + 12);

	//Tokenisation du corpus.
	vector<unsigned int> token_list;
	token_list = arbre.tokenization(argv[1], sep);

	//Creation du modele à partir de la liste de tokens.
	Modele modele(token_list);
	//Construction des n_gram de taille 2 (bigram).
	modele.NGramConstructor(2); 
	//Pour afficher les compte dans le fichier donné.   
	modele.ShowNGram("n_gram.txt");
	
	// Calcule des probabilitées.
	modele.probasConstructor(2);
	
	Translation translation = Translation();
	//Calcule de la perplexité de chaque ligne du fichier donné en param 1.
	//(Implique la tokenisation de chaque ligne)
	translation.calcPerplexFromFile(argv[2], &arbre, sep, modele);

	//Affichage des tokens -> perplexité.
	translation.initCodetomot(argv[0]);
	translation.showPerplex();

	return 0;
}
