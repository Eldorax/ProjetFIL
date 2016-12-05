#include "arbre.h"

void Arbre::addMot(vector<unsigned int> str, int i, ElementArbre* current, unsigned int token)
	{	
		while(true)
		{
			if(current->getEtat() == 0)
			{
				current->setEtat(1);
				current->setSymbole(str[i]);
				if(i >= str.size() - 1)
				{
					current->setMot(token);				
					break;
				}
			}else
			if(current->getSymbole() == str[i])
			{
				i++;
				if (current->getElDroite() == NULL)
					current->setElDroite(new ElementArbre);
				current = current->getElDroite();
			}else
			if(current->getSymbole() != str[i])
			{
				if (current->getElGauche() == NULL)
					current->setElGauche(new ElementArbre);
				current = current->getElGauche();
			}
		}
	}

void Arbre::addLexique(string lex_line)
{
	//Parsing
	string word("");
	string word_token_temp("");
	
	int i;
	for(i = 0; i < lex_line.size() && lex_line[i] != ' '; i++)
	{
		word = word + lex_line[i];
	}

	i++;
	for(i; i < lex_line.size(); i++)
	{
		word_token_temp = word_token_temp + lex_line[i];
	}
	
	unsigned int word_token = atoi(word_token_temp.c_str());
	
	//Convertion en tableau d'utf-8
	vector<unsigned int> word_utf8 = getUTF8(word);
	//ajout du mot dans l'arbre
	addMot(word_utf8, 0, &start, word_token);
}

Arbre::Arbre(string p_fichier)
{
	ifstream fichier(p_fichier.c_str(), ios::in);

	if ( !fichier )
		cout << "Erreur de lecture du fichier " << p_fichier << endl;

	string buffer;

	while( !fichier.eof() )
	{
		getline(fichier, buffer);
		if(buffer != "")
		{
			addLexique(buffer);
		}	
	}

	fichier.close();
	
}

void Arbre::printVector(vector <unsigned int> vec)
{
	for (int i = 0; i < vec.size(); i++)
		printf("%c", vec[i]);
}

void Arbre::showRecur(ElementArbre* current, vector <unsigned int> mot)
{
	mot.push_back(current->getSymbole());
	if(current->getMot() != 0)
	{
		printVector(mot);
		cout << " : " << current->getMot() << endl;
	}

	if(current->getElDroite() != NULL)
		showRecur(current->getElDroite(), mot);

	if(current->getElGauche() != NULL)
	{
		mot.pop_back();
		showRecur(current->getElGauche(), mot);
	}
	
	return;
}

void Arbre::show()
{
	vector <unsigned int> temp(0);
	showRecur(&start, temp);
}


ElementArbre* Arbre::rechercheChar(ElementArbre* current, unsigned int &current_char, bool flag)
{
	//cout << "-------->" << current->getSymbole() << endl;
	ElementArbre* tempCurrent = current;
	if (!flag)
		tempCurrent = tempCurrent->getElDroite();
	if(tempCurrent == NULL)
		return NULL;

	while(true)
	{
		//cout << tempCurrent->getSymbole() << endl;
		if(tempCurrent->getSymbole() == current_char)
		{
			//cout << "--------------------->" << tempCurrent->getSymbole() << endl;
			current = tempCurrent;
			return current;
		}
		else if (tempCurrent->getElGauche() != NULL)
		{
			tempCurrent = tempCurrent->getElGauche();
		}
		else
		{
			return NULL;
		}
	}
}

bool Arbre::in(vector <unsigned int> vecteur, unsigned int elem)
{
	for(int i = 0; i < vecteur.size(); i++)
		if(vecteur[i] == elem)
			return true;
	return false;
}

void Arbre::getUtf8FromFile(ifstream& file, unsigned int* res)
{
	string str("");
	char buffer;
	unsigned int nb_octet;
	unsigned int current_char;

	file.get(buffer);
	nb_octet = octetUsed ((unsigned char) buffer); //taille du caractere utf8
	str += buffer;
	for(int i = 0; i < nb_octet - 1; i++)
	{
		file.get(buffer);
		str += buffer;
	}
	current_char = getUnsignedInt(str, 0, nb_octet);
	res[0] = current_char;
	res[1] = nb_octet;	
}

vector<unsigned int> Arbre::tokenization(string file, vector <unsigned int> sep)
{
	ElementArbre* current = &start;
	ElementArbre* last_word = NULL;

	vector<unsigned int> token_list(0);


	ifstream fichier(file.c_str(), ios::in);
	unsigned int* res = new unsigned int [2];
	unsigned int current_char;
	int nb_octet;

	bool flag = true; //vrai si current est element de la racine de l'arbre
	int go_back;      //sert à se balader dans le fichier pour aller à la fin du dernier mot valide.

	if(!fichier)
		cout << "erreur lors de l'ouverture du fichier" << file << endl;

	while( !fichier.eof() )
	{
		getUtf8FromFile(fichier, res);
		current_char = res[0];
		nb_octet = res[1];
		
		if((current_char == 32 && flag) || (current_char == 10 && flag)) //on saute les espace et les \n en debut de recherche de mot
			continue;

		if(current_char == 32)  //modification des " " en "_" pendant la recherche d'un mot.
			current_char = 95;

		go_back -= nb_octet;

		current = rechercheChar(current, current_char, flag); //recherche du charactère dans l'arbre.

		if(flag)
			flag = false;

		if(current == NULL) //Si le charactère n'a pas été trouvé.
		{
			if(last_word == NULL) //si aucun mot valide n'a pas encore été trouvé.
			{
				while(!in(sep, current_char) && !fichier.eof()) //Avance jusqu'au prochaien separateur.
				{
					getUtf8FromFile(fichier, res);
					current_char = res[0];
					nb_octet = res[1];
				}
				fichier.seekg(-nb_octet, ios::cur);
				token_list.push_back(0);
			}
			else
			{
				token_list.push_back( last_word->getMot() );
				fichier.seekg(go_back, ios::cur);
			}
			last_word = NULL;
			current = &start;
			flag = true;
			go_back = 0;
		}

		else if (current->getMot() != 0) //si on trouve le charactère et que c'est la fin d'un mot
		{                                //on vérifi si il se termine par un separateur ou que c'est une " ' ".  
			getUtf8FromFile(fichier, res);
			current_char = res[0];
			nb_octet = res[1];

			if(in(sep,current_char) || current->getSymbole() == 39)
			{
				last_word = current;
				go_back = 0;
			}
			
			fichier.seekg(-nb_octet, ios::cur);
		}
		
	}
	
	return token_list;
}


void Arbre::getUtf8FromString(string phrase, unsigned int* res, int cursor)
{
	string str("");
	char buffer;
	unsigned int nb_octet;
	unsigned int current_char;

	buffer = phrase[cursor];
	nb_octet = octetUsed ((unsigned char) buffer); //taille du caractere utf8
	str += buffer;
	for(int i = 0; i < nb_octet - 1; i++)
	{
		buffer = phrase[cursor];
		cursor++;
		str += buffer;
	}
	current_char = getUnsignedInt(str, 0, nb_octet);
	res[0] = current_char;
	res[1] = nb_octet;
}


vector<unsigned int> Arbre::tokenizationStr(string phrase, vector <unsigned int> sep)
{
	phrase+='\n';
	ElementArbre* current = &start;
	ElementArbre* last_word = NULL;

	vector<unsigned int> token_list(0);


	unsigned int* res = new unsigned int [2];
	unsigned int current_char;
	int nb_octet;

	bool flag = true; //vrai si current est element de la racine de l'arbre
	int go_back;      //sert à se balader dans le fichier pour aller à la fin du dernier mot valide.
	int cpt = 0;
	while( cpt < phrase.size() )
	{
		getUtf8FromString(phrase, res, cpt);
		current_char = res[0];
		nb_octet = res[1];
		cpt += nb_octet;
		
		if((current_char == 32 && flag) || (current_char == 10 && flag)) //on saute les espace et les \n en debut de recherche de mot
			continue;

		if(current_char == 32)  //modification des " " en "_" pendant la recherche d'un mot.
			current_char = 95;
	
		//cout << (char) current_char << "nb_octet" << nb_octet << endl;

		go_back -= nb_octet;

		current = rechercheChar(current, current_char, flag); //recherche du charactère dans l'arbre.

		if(flag)
			flag = false;

		if(current == NULL) //Si le charactère n'a pas été trouvé.
		{
			if(last_word == NULL) //si aucun mot valide n'a pas encore été trouvé.
			{
				while(!in(sep, current_char) && cpt < phrase.size()) //Avance jusqu'au prochaien separateur.
				{
					getUtf8FromString(phrase, res, cpt);
					current_char = res[0];
					nb_octet = res[1];
					cpt += nb_octet;
				}
				cpt -= nb_octet;
				token_list.push_back(0);
			}
			else
			{
				token_list.push_back( last_word->getMot() );
				cpt += go_back;
			}
			last_word = NULL;
			current = &start;
			flag = true;
			go_back = 0;
		}

		else if (current->getMot() != 0) //si on trouve le charactère et que c'est la fin d'un mot
		{                                //on vérifi si il se termine par un separateur ou que c'est une " ' ".  
			getUtf8FromString(phrase, res, cpt);
			current_char = res[0];
			nb_octet = res[1];
			cpt += nb_octet;

			if(in(sep, current_char) || current->getSymbole() == 39)
			{
				last_word = current;
				go_back = 0;
			}

			cpt -= nb_octet;
		}
	}
	
	return token_list;
}
