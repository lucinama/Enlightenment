#include <stdio.h>
#include <set>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
  set<string> words_ignored;
  string line;
  set<string>::iterator it;
  while(getline(cin,line))
    {
      if (line == "::")
	break;
      else
	words_ignored.insert(line);
    }

  set<string> titles;
  while (getline(cin,line))
    titles.insert(line);
  
  int j = words_ignored.size(), l = titles.size();
  
  return 0;
}

