#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord 
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWord) 
{
	set<string>returnset;
	string lowerWord = convToLower(rawWord);
	string mot;	
	for(unsigned int i=0; i<=lowerWord.size(); i++)
	{
		if(i == lowerWord.size())
		{
			if(mot.size()<2)
			{
				mot.clear();
			}
			else
			{
				returnset.insert(mot);
				mot.clear();
			}	
		}
		if(ispunct(lowerWord[i]) == 0 && lowerWord[i] != ' ')
		{
			mot.push_back(lowerWord[i]);
		}
		else
		{
			if(mot.size()<2)
			{
				mot.clear();
			}
			else
			{
				returnset.insert(mot);
				mot.clear();
			}
		}
	}
	return returnset;
}
