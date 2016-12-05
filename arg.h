#ifndef __ARG
#define __ARG

#include <string>
#include <vector>

using namespace std;


typedef struct
{
	int flag;
	string data;
}ArgFlag;

ArgFlag TraitementArgs(int, char **, int);
int getArgParm(int, char **, int, string*);

#endif
