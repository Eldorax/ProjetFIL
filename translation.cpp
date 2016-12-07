#include "translation.h"

Translation::Translation(void)
{

}

void Translation::calcPerplexFromFile(string file_name, Arbre* arbre, vector<unsigned int> sep, Modele& modele)
{
	ifstream fichier(file_name, ios::in);
	string read_buffer;
	vector<unsigned int> clef;
	if(fichier)
	{
		while(getline(fichier, read_buffer))
		{
			clef = arbre->tokenizationStr(read_buffer+"\n", sep);
			perplex[clef] = calcPerplex(clef, modele);
		}	
		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier : " << file_name << "!\n";
}

double Translation::calcPerplex(vector<unsigned int> tokens, Modele& modele)
{
	//Plog
	double plog = 0;
	char taille_gram = modele.getTaille_gram();
	map<vector<unsigned int>, double> probas = modele.getProbas();
	vector<unsigned int> clef_buffer;	
	vector<unsigned int > temp;

	//probabilitée particulieres.
	unsigned int i;
	for( i = 0; i < (unsigned char) taille_gram && i < tokens.size(); i++)
	{
		clef_buffer.push_back(tokens[i]);
		if( probas.find(clef_buffer) != probas.end() ) //si la proba != 0
		{
			plog += probas[clef_buffer];
		}
		else
		{
			temp = clef_buffer;
			temp.pop_back();
			if( probas.find(temp) != probas.end() ) //test de la proba du denum.
				plog += modele.calcProba(0, probas[temp], "laplace");
			else
				plog += modele.calcProba(0, 0, "laplace");
		}
	}
	
	//N_gram "normal"
	for( i = i; i < tokens.size(); i++)
	{
		//Ajoute du nouveau mot.
		clef_buffer.push_back(tokens[i]);
		//suppresion de l'ancien mot.
		clef_buffer.assign( clef_buffer.begin() + 1, clef_buffer.end() );

		if( probas.find(clef_buffer) != probas.end() ) //si la proba != 0
		{
			plog += probas[clef_buffer];
		}
		else
		{
			temp = clef_buffer;
			temp.pop_back();
			if( probas.find(temp) != probas.end() ) //test de la proba du denum.
				plog += modele.calcProba(0, probas[temp], "laplace");
			else
				plog += modele.calcProba(0, 0, "laplace");
		}
	}
	return pow(2, plog/tokens.size());
}


double Translation::calcPerplex(string phrase, Arbre* arbre, vector<unsigned int> sep, Modele& modele)
{
	vector<unsigned int> res;
	res = arbre->tokenizationStr(phrase, sep);
	return calcPerplex(res, modele);
}

void Translation::showPerplex(void)
{
	for (map<vector<unsigned int>, double>::iterator it = perplex.begin(); it != perplex.end(); it++)
		cout << code2Mot(it->first) << " => " << (double) it->second << '\n';
}

void Translation::showTreillis(void)
{
	for(unsigned int i = 0; i < treillis.size(); i++)
	{
		cout << endl << "Etat " << i << endl;
		for(unsigned int j = 0; j < treillis[i].size(); j++)
		{
			cout << treillis[i][j].token << ' ' << treillis[i][j].proba_emission << endl;
		}
	}
}


double Translation::calc2gramProba(vector<unsigned int> tokens, Modele& modele)
{
	//Plog
	double plog = 0;
	map<vector<unsigned int>, double> probas = modele.getProbas();
	vector<unsigned int > temp;

	//probabilitée particulieres.
	if( probas.find(tokens) != probas.end() ) //si la proba != 0
	{
		plog = probas[tokens];
	}
	else
	{
		temp = tokens;
		temp.pop_back();
		if( probas.find(temp) != probas.end() ) //test de la proba du denum.
			plog = modele.calcProba(0, probas[temp], "laplace");
		else
			plog = modele.calcProba(0, 0, "laplace");
	}
	return plog;
}



//Retourne la structure sommet_treillis acossier à une ligne de fichier.
sommet_treillis getSommetTFromLine(string line)
{
	string token;
	string proba_em;

	unsigned int i;
	for( i = 0; line[i] != ' ' and i < line.size(); i++)
		token += line[i];

	for( i = i+1; i < line.size(); i++)
		proba_em += line[i];

	sommet_treillis res = { ((unsigned int) atoll(token.c_str())), atof(proba_em.c_str()) };
	return res;
}

void Translation::initTreillis(string file_name)
{
	treillis.clear();
	ifstream file(file_name, ios::in);
	string read_buffer;
	vector<sommet_treillis> etat_temp;

	if(file)
	{
		getline(file, read_buffer);
		while(getline(file, read_buffer))
		{
			if( read_buffer[0] == '%' ) //Nouvel état
			{
				treillis.push_back(etat_temp);
				etat_temp.clear();
				
			}
			else
				etat_temp.push_back(getSommetTFromLine(read_buffer));
			
		}
		treillis.push_back(etat_temp);	
		file.close();
	}
	else
	{
		cerr << "Impossible d'ouvrir le fichier " << file_name << "!\n";
		exit(1);
	}
	
}



vector<unsigned int> Translation::calcTreillisEmmission(void)
{
	vector <unsigned int> res;
	sommet_treillis min;
	for(unsigned int i = 0; i < treillis.size(); i++)
	{
		min = treillis[i][0];
		for(unsigned int j = 1; j < treillis[i].size(); j++)
		{
			if(treillis[i][j].proba_emission < min.proba_emission)
				min = treillis[i][j];
		}
		res.push_back(min.token);
	}
	return res;
}



vector<unsigned int> Translation::calcTreillis(Modele modele)
{
	//vector< vector<unsigned int> > paths(treillis[0].size()); //Liste des chemins (il faut seletionner le plus cours à la fin.
	vector <chemin> paths;
	vector <chemin> temp_paths;
	vector <unsigned int> clef;
	//unsigned int temp;
	double min;
	chemin temp;
	double probas_temp;

	//Initialisation des état initiaux.
	for( unsigned int i = 0; i < treillis[0].size(); i++)
	{
		clef.push_back(treillis[0][i].token);
		temp.path.push_back(treillis[0][i].token);
		temp.proba = (treillis[0][i].proba_emission) + calc2gramProba(clef, modele);
		paths.push_back(temp);
		temp.path.clear();
		clef.clear();
	}
	temp.path.clear();

	//Pour chaque états.
	for( unsigned  int i_etat = 1; i_etat < treillis.size(); i_etat ++)
	{
		//Calcule du meilleur.
		for( unsigned int i_token = 0; i_token < treillis[i_etat].size(); i_token++)
		{
			//Parcour des ancètres et construction d'une liste de chemin temporaire.
			temp_paths.push_back(temp);
			clef.clear();
			clef.push_back(treillis[i_etat-1][0].token);
			clef.push_back(treillis[i_etat][i_token].token);
			min = paths[0].proba + treillis[i_etat][i_token].proba_emission + calc2gramProba(clef, modele); 
			temp_paths[i_token].path = paths[0].path;
			temp_paths[i_token].path.push_back(treillis[i_etat][i_token].token);	

			for( unsigned int i_token_a = 1; i_token_a < treillis[i_etat-1].size(); i_token_a++)
			{
				clef.clear();
				clef.push_back(treillis[i_etat-1][i_token_a].token);
				clef.push_back(treillis[i_etat][i_token].token);
				probas_temp = paths[i_token_a].proba + treillis[i_etat][i_token].proba_emission + calc2gramProba(clef, modele);

				if (probas_temp < min)
				{
					min = probas_temp;
					temp_paths[i_token].path = paths[i_token_a].path;
					temp_paths[i_token].path.push_back(treillis[i_etat][i_token].token);				
				}
			}
			temp_paths[i_token].proba = min;
		}
		paths.clear();
		paths = temp_paths;
		temp_paths.clear();
		
	}
	
	int save = 0;
	double p = paths[0].proba;
	for( unsigned int i = 1; i < paths.size(); i++)
	{
		if( paths[i].proba < p )
		{
			p = paths[i].proba;
			save = i;
		}
	}

	return paths[save].path;
}


void Translation::initTranslationTable(string file_name)
{
	translate_table.clear();
	ifstream table_file(file_name, ios::in);
	string read_buffer;

	if(table_file)
	{
		unsigned int i;
		string clef;
		string trans;
		string prob;
		transElem temp;

		while( getline(table_file, read_buffer) )
		{
			i = 0;
			clef.clear();
			trans.clear();
			prob.clear();
			
			while(read_buffer[i] != ' ')
			{
				clef += read_buffer[i];
				i++;
			}

			i++;
			while(read_buffer[i] != ' ')
			{
				trans += read_buffer[i];
				i++;
			}

			i++;
			while(i < read_buffer.size())
			{
				prob += read_buffer[i];
				i++;
			}
			
			//Creation de la structure.
			temp.trad = ((unsigned int) atoll(trans.c_str()));
			temp.proba = atof(prob.c_str());

			translate_table[((unsigned int) atoll(clef.c_str()))].push_back(temp);
			
		}
	}
	else
	{
		cout << "Erreur de l'ouverture de : " << file_name << endl;
		exit(1);		
	}
}

void Translation::createTreillis(string dest_file, vector<unsigned int> phrase)
{
	ofstream file(dest_file.c_str(), ios::out | ios::trunc);
	
	for( unsigned int i = 0; i < phrase.size(); i++)
	{
		file << "%col " << i << endl;

		if( translate_table[ phrase[i] ].size() == 0) //si la traduction est inconnu
			file << '0' << ' ' << "15" << endl;
		else
		{
			for( unsigned int j = 0; j < translate_table[ phrase[i] ].size(); j++)
			{
				file << translate_table[phrase[i]][j].trad << ' ' << translate_table[phrase[i]][j].proba << endl;
			}
		}
	}
}


void Translation::initCodetomot(string file_name)
{
	ifstream file(file_name, ios::in);
	if( file )
	{
		unsigned int i;
		unsigned int token;
		string buffer, mot, token_str;
		while ( getline(file, buffer) )
		{
			mot.clear();
			token_str.clear();
			for( i = 0; buffer[i] != ' '; i++)
			{
				mot += buffer[i];
			}
			i++;
			for(; i < buffer.size(); i++)
			{
				token_str += buffer[i];
			}
			token = (unsigned int) atoll(token_str.c_str());
			codetomot[token] = mot;
		}
		codetomot[0] = "TOKEN_INCONNU";

	}

}

string Translation::code2Mot(vector<unsigned int> tokens)
{
	string res;
	for( unsigned int i = 0; i < tokens.size(); i++)
	{
		res += codetomot[tokens[i]];
		res += ' ';
	}
	return res;
}



