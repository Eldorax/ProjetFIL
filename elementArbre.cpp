#include "elementArbre.h"

ElementArbre::ElementArbre()
{
	etat = 0;
	symbole = 0;
	mot = 0;
	elementArbreGauche = NULL;
	elementArbreDroite = NULL;
}

bool ElementArbre::isWord()
{
	return (mot != 0);
}


void ElementArbre::setSymbole(const unsigned int p_sym)
{
	symbole = p_sym;
}

void ElementArbre::setMot(const unsigned int p_mot)
{
	mot = p_mot;
}

void ElementArbre::setElGauche(ElementArbre * p_el)
{
	elementArbreGauche = p_el;	
}

void ElementArbre::setElDroite(ElementArbre * p_el)
{
	elementArbreDroite = p_el;
}

unsigned int ElementArbre::getSymbole()
{
	return symbole;
}

unsigned int ElementArbre::getMot()
{
	return mot;
}

ElementArbre* ElementArbre::getElGauche()
{
	return elementArbreGauche;
}

ElementArbre* ElementArbre::getElDroite()
{
	return elementArbreDroite;
}




















