#include "encodage.h"
#include <stdio.h>

using namespace std;

string printChar(unsigned char p)
{
	string res;
	unsigned char t = 128;
	for( int i = 0; i < 8; i++)
	{
		if( p & t)
			res = res + '1';
		else
			res = res + '0';
		t = t >> 1;
	}
	return res;
}


string printInt(unsigned int p)
{
	string res;
	unsigned int t = 2147483648;
	for( int i = 0; i < 32; i++)
	{
		if( p & t)
			res = res + '1';
		else
			res = res + '0';
		t = t >> 1;
	}
	return res;
}


unsigned int getUnsignedInt(string str, int i, int j)
{
	unsigned int res = 0;
	for(int k = i; i < j; i++)
	{
		res = res | ((unsigned char)str[k]);
		if( k < j - 1)
			res = res << 8;	
	}
	return res;
}

int octetUsed (unsigned char temp)
{
	char nb_octet = 0;
	if( temp & 128 )
	{
		while( temp & 128 ) 
		{
			nb_octet++;
			temp = temp << 1;
		}
	}
	else
		nb_octet = 1;
	return nb_octet;
}

vector<unsigned int> getUTF8(string str)
{
	vector<unsigned int> res(0);
	unsigned int i = 0;
	char nb_octet;	
	unsigned char temp;
	unsigned int to_add;
	while( i < str.size() )
	{	
		temp = str[i];
		nb_octet = octetUsed(temp);
		

		to_add = 0;
		to_add = getUnsignedInt(str, i, i + nb_octet);
		res.push_back(to_add);
		i += nb_octet;
	}	

	return res;
}

















