# Projet : Fondamentaux de l'ingénierie des langues
Auteurs : - PELLETIER  Sébastien M1 Info TP1b Luminy
		  - BOUDERMINE Antoine   M1 Info TP1b Luminy
 
Compilation : make
Utilisation : ./translator.exe [fichier de lexique] [corpus d'apprentissage] [fichier phrases test (une phrase par ligne)]
Il y aura, plus tard des options pour choisir de tokenizer ou juste d'afficher les n_grams etc..
Le fichier n_grams.txt contient le décompte des ngrams.
 
Résultats pour le fichier de test donné (phrase = perplexité) avec lexique_ratp_fr.txt et corpus_ratp_fr.txt :

	je va à Paris     = 9.7549
	on va à Paris     = 5.83594
	je vais à Paris   = 4.95849 <- La plus probable.
	on vais à Paris   = 11.4422
	tu vas à Paris    = 13.8742
	elle vais à Paris = 12.0696
	elle va à Paris   = 7.08586
	tu vais à Paris   = 13.2555
