#include <iostream>
#include <stdio.h>
#include <string>

#include "elementArbre.h"
#include "arbre.h"
#include "modele.h"
#include <vector>
#include <stdlib.h>
#include "arg.h"
#include "translation.h"
#include "showVector.h"
#include "EM.h"

using namespace std;


int main(int argc, char ** argv)
{
	/*
	//Traitement des arguments.
	argv++;
	argc--;
	
	vector<ArgFlag> args;
	for( int i = 0; i < argc; i++) //Ajout de chaque agument(s) au vector.
	{
		if( argv[i][0] == '-' )
		{
			args.push_back( TraitementArgs(argc, argv, i) );
		}
	}
	
	if( args.size() == 0) //Si aucun argument n'est donné.
	{
		cout << "Mauvaise utilisation.\n";
		exit(1);
	}

	//Variables du programmes.
	string lexique;
	string corpus;
	string output("stdout");
	int n_gram = 1;
	
	//liste des séparateur à prendre en compte.
	unsigned int list_sep[12] = {44, 32, 10, 9, 91, 93, 46, 63, 33, 58, 59, 95};
	vector <unsigned int> sep(0);
	sep.assign(list_sep, list_sep + 12);
	
	//Assignation des variables.
	for( unsigned int i = 0; i < args.size(); i++ )
	{
		switch(args[i].flag)
		{
			case 3: // -o pour choisir la sortie.
				output = args[i].data;
				break;
			case 4: // -l choix du lexique.
				lexique = args[i].data;
				break;
			case 5: // -v choix du corpus.
				corpus = args[i].data;
				break;
			case 2: // -cg nb compté les nb_grams.
				if( atoi( (args[i].data).c_str() ) != 0 )
					n_gram = atoi( (args[i].data).c_str() );;
				break;
			case 0: // si erreur.
				cout << args[i].data << endl;
				exit(1);
			break;
		}
	}
#include "showVector.h"
	//Execution des options.
	vector<unsigned int> token_list;
	
	for( unsigned int i = 0; i < args.size(); i++ )
	{
		if(args[i].flag == 1) // -t pour tokenisé
		{
			//Creation de l'arbre.
			Arbre arbre(lexique);
			
			//Calcule des tokens.
			token_list = arbre.tokenization(corpus, sep);

			Modele modele(token_list);
			modele.ShowListToken();
		}
		else if (args[i].flag == 2)
		{
			//Creation de l'arbre.
			Arbre arbre(lexique);
			
			//Calcule des tokens.
			token_list = arbre.tokenization(corpus, sep);

			Modele modele( token_list );
			modele.NGramConstructor(n_gram); //construction.
			modele.ShowNGram(output);        //Affichage.
		}
	}
	
	

	//Arbre arbre(argv[1]); //creation de l'arbre.

	//arbre.show();       //Pour afficher les mots construis dans l'arbre.
		
	//unsigned int list_sep[12] = {44, 32, 10, 9, 91, 93, 46, 63, 33, 58, 59, 95};
	//vector <unsigned int> sep(0);
	//sep.assign(list_sep, list_sep + 12);	
		
	//Calcule des token
	//vector<unsigned int> token_list;
	//token_list = arbre.tokenization(argv[2], sep);

	//Creation du modele à partir de la liste de tokens
	//Modele modele(token_list);
	
	
	//modele.ShowListToken();

	//modele.NGramConstructor(2); 

	//modele.ShowNGram("n_gram.txt");

	//modele.probasConstructor(2);
	
	//Translation translation = Translation();

	//translation.calcPerplexFromFile(argv[3], &arbre, sep, modele);

	//translation.showPerplex();

	//translation.initTreillis("exemple_treillis.txt");

	//translation.showTreillis();

	//cout << ShowVector(translation.calcTreillisEmmission()) << endl;
	//cout << ShowVector(translation.calcTreillis(modele)) << endl;
	
	/*///////////////// Tokenization en /////////////////
	/*
	Arbre arbre(argv[1]); //creation de l'arbre.

	unsigned int list_sep[12] = {44, 32, 10, 9, 91, 93, 46, 63, 33, 58, 59, 95};
	vector <unsigned int> sep(0);
	sep.assign(list_sep, list_sep + 12);

	//Calcule des token
	vector<unsigned int> token_list;
	string n (argv[2]);
	token_list = arbre.tokenizationStr(n, sep);
	
	Translation translation;
	translation.initTranslationTable(argv[3]);
	translation.createTreillis(argv[4], token_list);
	*/
	
	///////////////// EM /////////////////
	unsigned int list_sep[12] = {44, 32, 10, 9, 91, 93, 46, 63, 33, 58, 59, 95};
	vector <unsigned int> sep(0);
	sep.assign(list_sep, list_sep + 12);
	vector <unsigned int> token_list;
	vector <unsigned int> token_phrase;

	//Constructioin des arbres pour le calcul de la table de traduction.
	Arbre arbre_fr(argv[1]);
	Arbre arbre_en(argv[2]);

	//Creation des listes de phrases tokénisé en francais et en anglais.
	/*	
	Em em;
	em.initTokensFr(argv[3], arbre_fr, sep);
	em.initTokensEn(argv[4], arbre_en, sep);
	
	//Création de la table de traduction.
	em.calcEm(10);
	em.out("table.txt");
	*/
	//tokénisation du corpus d'apprentissage.
	
	token_list = arbre_fr.tokenization(argv[5], sep);

	//Création du modéle à partir du corpus.
	Modele modele(token_list);
	modele.NGramConstructor(2); 
	modele.probasConstructor(2);
	
	modele.ShowNGram("n_gram.txt");

	//Creation du treillis par rapport au texte a traduire.
	Translation translation = Translation();
	translation.initTranslationTable("table.txt");
	string phrase (argv[6]);
	token_phrase = arbre_en.tokenizationStr(phrase, sep);
	translation.createTreillis("treillis.txt", token_phrase);

	translation.initTreillis("treillis.txt");

	//cout << ShowVector(translation.calcTreillisEmmission()) << endl;
	cout << ShowVector(translation.calcTreillis(modele)) << endl;

///////////////////////////////////////////////////////////////////////////////////////
	//modele.ShowProbas();
	//unsigned int list_sep1[1] = {9297};
	//vector <unsigned int> sep1(0);
	//sep1.assign(list_sep1, list_sep1 + 1);	
	//cout << "Probas de vous : " << modele.calcPerplex(sep1) << endl;

	//string sample("vous vous");
	//cout << sample << " " << modele.calcPerplex(sample, &arbre, sep) << endl;
	//9297  1.60239
	return 0;
}
