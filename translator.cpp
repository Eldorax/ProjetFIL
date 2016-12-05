#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "elementArbre.h"
#include "arbre.h"
#include "modele.h"
#include "translation.h"
#include "EM.h"

using namespace std;


int main(int argc, char ** argv)
{
	argc--;
	argv++;
	
	if ( argc < 6 )
	{
		cout << "Mauvaise utilisation :\n";
		cout << "translator.exe <lexique fr> <lexique en> <corpus bila fr> <corpus bila en> <corpus de base fr (proba trans)> <phrase à traduire en fr>\n";
		exit(1);
	}
	
	///////////////// EM /////////////////
	unsigned int list_sep[12] = {44, 32, 10, 9, 91, 93, 46, 63, 33, 58, 59, 95};
	vector <unsigned int> sep(0);
	sep.assign(list_sep, list_sep + 12);
	vector <unsigned int> token_list;
	vector <unsigned int> token_phrase;

	//Construction des arbres pour le calcul de la table de traduction.
	Arbre arbre_fr(argv[0]);
	Arbre arbre_en(argv[1]);

	//Creation des listes de phrases tokénisé en francais et en anglais.
	//(tokenisation ligne par line du corpu fr et en)
	Em em;
	em.initTokensFr(argv[2], arbre_fr, sep);
	em.initTokensEn(argv[3], arbre_en, sep);
	
	//Création de la table de traduction.
	em.calcEm(10);       //nb d'iterration de l'algo EM.
	em.out("table.txt"); 
	
	//tokénisation du corpus d'apprentissage.
	token_list = arbre_fr.tokenization(argv[4], sep);

	//Création du modéle à partir du corpus.
	Modele modele(token_list);
	modele.NGramConstructor(2); 
	modele.probasConstructor(2);
	
	//modele.ShowNGram("n_gram.txt"); affichage des n_gram dans le fichier.

	//Creation du treillis par rapport au texte a traduire.
	Translation translation = Translation();
	translation.initTranslationTable("table.txt");
	string phrase(argv[5]);
	token_phrase = arbre_en.tokenizationStr(phrase, sep);
	translation.createTreillis("treillis.txt", token_phrase);

	translation.initTreillis("treillis.txt");

	//cout << ShowVector(translation.calcTreillisEmmission()) << endl;
	cout << ShowVector(translation.calcTreillis(modele)) << endl;

	return 0;
}
