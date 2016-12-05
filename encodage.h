#ifndef __ENCODAGE
#define __ENCODAGE

#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<unsigned int> getUTF8(string);
int octetUsed (unsigned char var);
unsigned int getUnsignedInt(string, int, int);


#endif
