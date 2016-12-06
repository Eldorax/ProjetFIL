Projet : Fondamentaux de l'ingénierie des langues
Auteurs : - PELLETIER  Sébastien M1 Info TP1b Luminy
          - BOUDERMINE Antoine   M1 Info TP1b Luminy

Résultats pour le fichier de test donné (phrase = perplexité) avec lexique_ratp_fr.txt et corpus_ratp_fr.txt :
 
	je va à Paris     = 9.7549
	on va à Paris     = 5.83594
	je vais à Paris   = 4.95849 <- La plus probable.
	on vais à Paris   = 11.4422
	tu vas à Paris    = 13.8742
	elle vais à Paris = 12.0696
	elle va à Paris   = 7.08586
	tu vais à Paris   = 13.2555


Pour avoir des informations sur les paramétres à mettre dans les executables
veuillez l'éxecuter sans aucun paramétre.

Compilation : make

Les executables : 
 
tokenisateur.exe  : Permet de tokéniser un corpus donné en paramétre.
		tokeniseur <lexique> <fichier à tokeniser>

perplex.exe       : Calcul mla perpléxité d'un fichier de phrases en francais.
		perplex.exe <lexique> <corpus> <fichier à calcule (une phrase par ligne)>

translator.exe    : Permet de traduire en francais une phrase en anglais donné en paramètre.
		translator.exe <lexique fr> <lexique en> <corpus bila fr> <corpus bila en> <corpus de base fr (proba trans)> <phrase à traduire en fr>

