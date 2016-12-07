Projet : Fondamentaux de l'ingénierie des langues
Auteurs : - PELLETIER  Sébastien M1 Info TP1b Luminy
          - BOUDERMINE Antoine   M1 Info TP1b Luminy

Résultats pour le fichier de test (phrase_test1.txt) lexique_ratp_fr.txt et corpus_ratp_fr.txt (Perplexité):

aller_retour Paris j' ai un pour  => 10.4859
aller_retour pour Paris un j' ai  => 12.9572
aller_retour pour un Paris ai j'  => 16.008
j' ai un aller_retour pour Paris  => 7.99312  <----
j' aller_retour ai Paris un pour  => 23.8377
Paris ai aller_retour pour j' un  => 31.7038
pour j' aller_retour Paris ai un  => 19.507
pour Paris j' ai un aller_retour  => 7.32509  <---------
pour un aller_retour j' ai Paris  => 11.699
un ai Paris aller_retour j' pour  => 35.7031



Résultats pour le fichier de test (phrase_test2.txt) lexique_ratp_fr.txt et corpus_ratp_fr.txt (traductions):

----- very good day-----
emi : très courage jour 
viterbi : très bonne journée 

----- you can take a bus to Clichy then change to Opera-----
emi : vous peut prendre une bus appartient Clichy puis changement appartient Opéra 
viterbi : vous pouvez prendre un bus de Clichy puis changement à Opéra 

----- and the next one for Porte de Clignancourt is in twenty one minutes-----
emi : et la prochaine vingt_et_une pour Porte Lyon Clignancourt tombe dans vingt vingt_et_une minutes 
viterbi : et le prochain actuellement pour Porte Porte Clignancourt a dans vingt vingt_et_une minutes 

----- well it's not very far-----
emi : ben TOKEN_INCONNU pas très loin 
viterbi : bien TOKEN_INCONNU pas très loin 

----- I would like to have some information about the Roissy bus-----
emi : je rapprocherait voudrait appartient avez quelques information sujet la Roissy bus 
viterbi : j' aurais voulu pour avoir quelques informations près de Roissy bus 

----- you mentioned the industrial area-----
emi : vous parliez la industrielle arrondissement 
viterbi : vous parlais du industrielle arrondissement 

----- I have the papers which proove that it is valid-----
emi : je avez la papiers quel prouvent ça c' tombe valable 
viterbi : j' ai les papiers qui prouvent que ça a valable 

----- you're welcome Have a nice day-----
emi : TOKEN_INCONNU prie TOKEN_INCONNU une souhaite jour 
viterbi : TOKEN_INCONNU prie TOKEN_INCONNU un souhaite jour 

Remarque : TOKEN_INCONNU est présant quand le TOKEN n'est pas présent dans la table de traduction créé
		   car non présent dans les corpus bilang.




Pour avoir des informations sur les paramétres à mettre dans les executables
veuillez l'éxecuter sans aucun paramétre.

Compilation : make

Les executables : 
 
tokenisateur.exe  : Permet de tokéniser un corpus donné en paramétre.
		tokeniseur <lexique> <fichier à tokeniser>

perplex.exe       : Calcul la perpléxité d'un fichier de phrases en francais. Affiche les n_gram dans le fichier n_gram.txt
		perplex.exe <lexique> <corpus> <fichier à calcule (une phrase par ligne)>

translator.exe    : Permet de traduire en francais une phrase en anglais donné en paramètre.
		translator.exe <lexique fr> <lexique en> <corpus bila fr> <corpus bila en> <corpus de base fr (proba trans)> <phrase à traduire en fr>

main.exe          : Permet de traduire en francais un fichier de phrase en anglais donné en paramètre. ils les traduit avec et sans viterbi?*.
		main.exe <lexique fr> <lexique en> <corpus bila fr> <corpus bila en> <corpus de base fr (proba trans)> <fichier de phrase à traduire>


Détails du code : 

Les principales classes : 

	- arbre       : permet de modéliser le lexique dans un arbre.
	- modele      : permet, à partir du corpus d'apprentissage tokénisé, de construire nos n-grammes et nos probabilités logarithmiques.
	- translation : permet de calculer la perpléxité d'un fichier de phrases, de traduire un fichier avec seulement un treillis 
					ou avec l'algorithme de viterbi (treillis + modele).
	- EM          : permet de créer la table de traduction.

De manière général, les structure de données utilisé sont des vector (liste chainé en c++) et des map.



















