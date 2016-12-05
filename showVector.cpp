#include "showVector.h"

string ShowVector(vector <unsigned int> vecteur)
{
	string temp;
	for(unsigned int i = 0; i < vecteur.size(); i++)
	{
		temp += to_string(vecteur[i]);
		temp += ' ';
	}
	return temp;
}
