#include "arg.h"

int getArgParm(int len, char ** p_argv, int curr, string* data)
{
	if( curr < len - 1)
	{
		if( p_argv[curr + 1][0] != '-')
			*data = string(p_argv[curr + 1]);
		else
			return 0;
	}
	else
		return 0;
		
	return 1;
}

ArgFlag TraitementArgs(int len, char ** p_argv, int curr)
{
	// 0 -erreur
	// 1 -t  tokenize
	// 2 -cg count ngram
	// 3 -o output
	// 4 -l set lexique
	// 5 -v set corpus
	ArgFlag res = { 0 };
	
	if(p_argv[curr][0] == '-' && p_argv[curr][1] != '\0')
	{
		int test;
		switch( p_argv[curr][1] )
		{
			case 't':
					res.flag = 1;
				break;
				
			case 'c':
				if( p_argv[curr][2] == 'g')
				{
					getArgParm(len, p_argv, curr, &res.data); // pas besion de tester car default = 1.
					res.flag = 2;
				}
				break;
				
			case 'o':
				if( (test = getArgParm(len, p_argv, curr, &res.data)) != 0 )
				{
					res.flag = 3;
				}
				else
				{
					res.flag = 0;
					res.data = "Mauvaise utilisation de '-o'\n";
				}
				break;
				
			case 'l':
				if( (test = getArgParm(len, p_argv, curr, &res.data)) != 0 )
				{
					res.flag = 4;
				}
				else
				{
					res.flag = 0;
					res.data = "Mauvaise utilisation de '-o'\n";
				}
				break;
				
			case 'v':
				if( (test = getArgParm(len, p_argv, curr, &res.data)) != 0 )
				{
					res.flag = 5;
				}
				else
				{
					res.flag = 0;
					res.data = "Mauvaise utilisation de '-o'\n";
				}
				break;
				
			default:
				res.flag = 0;
				res.data = "Mauvais argument(s)\n";	
		}
	}
	else
	{
		res.flag = 0;
		res.data = "Mauvais argument(s) Miss '-' ?\n";	
	}
	
	return res;
}
