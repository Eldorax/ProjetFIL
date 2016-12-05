#include "modele.h"

Modele::Modele(vector<unsigned int> p_list_token)
{
	list_token = p_list_token;
}

void Modele::ShowListToken(void)
{
	cout << list_token[0];
	for(unsigned int i = 1; i < list_token.size(); i++)
	{
		cout << " " << list_token[i];
	}
}

void Modele::NGramConstructor(char taille)
{
	taille_gram = taille;
	n_grams.clear();
	vector<unsigned int> n_gram;
	map<vector<unsigned int>, unsigned int> i_gram;

	for(char i = 0; i < taille; i++) //Creation des i == N  Grams.
	{
		i_gram.clear();
		for(unsigned int j = 0; j < list_token.size() - i; j++)
		{
			for(char k = 0; k < i + 1; k++)
				n_gram.push_back(list_token[j + k]);

			i_gram[n_gram]++;
			n_gram.clear();
		}
		n_grams.push_back(i_gram);
	}

	
}

void Modele::ShowNGram(string type)
{
	if( type == "stdout" )
	{
		for(unsigned int i = 0; i < n_grams.size(); i++)
		{
			cout << i + 1 << "_gram:\n";
			for (map<vector<unsigned int>, unsigned int>::iterator it = n_grams[i].begin(); it != n_grams[i].end(); it++)
				cout << ShowVector(it->first) << " " << it->second << '\n';
		}
	}
	else
	{
		ofstream file(type.c_str(), ios::out | ios::trunc);
		for(unsigned int i = 0; i < n_grams.size(); i++)
			{
				file << i + 1 << "_gram:\n";
				for (map<vector<unsigned int>, unsigned int>::iterator it = n_grams[i].begin(); it != n_grams[i].end(); it++)
					file << ShowVector(it->first) << " " << it->second << '\n';
			}
		file.close();
	}
}

void Modele::setList_token(vector<unsigned int> p_list_token)
{
	list_token = p_list_token;
}

void Modele::probasConstructor(char taille)
{
	if( taille <= taille_gram )
	{
		vector<unsigned int> key;
		vector<unsigned int> temp;
		for(int n = 0; n < taille; n++)
		{
			for(map<vector<unsigned int>, unsigned int>::iterator it = n_grams[n].begin(); it != n_grams[n].end(); it++)
			{
				key = it->first;
				if(n == 0)
				{
					probas[key] = calcProba( ( (double) n_grams[n][key] ), ( (double) list_token.size() ), "laplace");
				}
				else
				{
					temp = key;
					temp.pop_back();
					probas[key] = calcProba( ( (double) (n_grams[n][key]) ), ( (double) (n_grams[n - 1][temp]) ), "laplace" );
				}
			}
			key.clear();
		}
	}
	else
		cout << "Erreur lors de l'utilisation du modèle.\n";
	
}


double Modele::calcProba(double num, double denum, string type)
{
	double a = 0.1;
	double res;

	if( type == "laplace" )
	{
		res = -1 * log10( (num + a) / ( denum + (list_token.size()*a) ) );
	}
	else
	{
		cout << "Type de lissage inconnu.\n";
		exit(1);		
	}
	return res;	
}

void Modele::ShowProbas(void)
{
	for (map<vector<unsigned int>, double>::iterator it = probas.begin(); it != probas.end(); it++)
		cout << ShowVector(it->first) << " " << (double) it->second << '\n';
}













