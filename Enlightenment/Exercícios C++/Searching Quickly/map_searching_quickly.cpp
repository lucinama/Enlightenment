#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <set> 
#include <iomanip>
#include <algorithm>

using namespace std;

int main ()
{
  set<string> words_to_ignore;
  string aux1;
  set<string>::iterator it_set;
  int i;
  
  for (i=0; i<50; i++)
    {
      getline(cin,aux1);
      if (aux1 == "::")
	break;
      if (aux1 != "::" && aux1 !="")
	words_to_ignore.insert(aux1);
    }

  for (it_set = words_to_ignore.begin(); it_set != words_to_ignore.end(); ++it_set)
    cout << *it_set << endl;

  map<int,string> titles;
  map<int,string>::iterator it_map;
  string line;

  int j=0;
  while(getline(cin,line) && j<200)
    {
      transform(line.begin(), line.end(), line.begin(), ::tolower);
      titles.insert(pair<int,string>(j,line));
      j++;
      cin.clear();
    }

  cout << j << endl;

  for (it_map = titles.begin(); it_map != titles.end(); ++it_map)
    {
      cout << (*it_map).second << endl;
    }

  int l=0;
  set<string> key_words;
  string aux1, aux2;
  for (it_map = titles.begin(); it_map != titles.end(); ++it_map)
    {
      aux2 = (*it_map).second; // iterar cada palavra aqui tb, cada aux2 um titulo
      
      for (it_set = words_to_ignore.begin(); it_set != words_to_ignore.end(); ++it_set)
	{
	  aux1 = *it_set;
	  if (aux2 != aux1)
	    key_words.insert(aux2);
	  else {}
	}
    }

  
  for (it_set = key_words.begin(); it_set != key_words.end(); ++it_set)
    cout << *it_set << endl;

  return 0;   
}
