#ifndef ___EM___
#define ___EM___

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>

#include "arbre.h"
#include "showVector.h"

using namespace std;

class Em
{
	private:

	vector< vector<unsigned int> > tokens_fr;
	vector< vector<unsigned int> > tokens_en;

	map< vector<unsigned int>, double > p_t;
	map< vector<unsigned int>, double > nb;
	map<unsigned int, double> total;
	map<unsigned int, double> stotal;

	


	public:

	void initTokensFr(string, Arbre&, vector<unsigned int>);    //Initialise les tokens du corpus Fr.
	void initTokensEn(string, Arbre&, vector<unsigned int>);    //Initialise les tokens du corpus En.
	
	void initProbas();
	void calcEm(unsigned int);

	void out(string);


};


#endif


