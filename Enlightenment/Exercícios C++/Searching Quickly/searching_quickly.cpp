#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{

  int i1=0;
  string aux1[50], words[50];
  while (i1<50)
    {
      cin >> aux1[i1];
      if (aux1[i1] == "::")
	break;
      else
	{
	  words[i1] = aux1[i1];
	  i1++;
	}	
    }
  cin.clear();
  
  int j=0;
  string titles[3000], aux2[3000];

  while (getline(cin,titles[j]))
    {
      transform(titles[j].begin(), titles[j].end(), titles[j].begin(), ::tolower);
      j++;
    }

  int m1=0, l=0, m2=0;
  vector<string> key_words;
  while (l < j)
    {
      string::size_type pos1[210], pos2[210], dif[210];
      pos1[l]=-1;
      while (pos2[l] != string::npos)
	{
	  int i2 =0, check[3000];
	  string aux3[3000];
	  pos2[l] = titles[l].find(" ", pos1[l]+1);
	  dif[l] = pos2[l] - pos1[l] -1;
	  aux3[m1] = titles[l].substr(pos1[l]+1,dif[l]);
	  pos1[l]=pos2[l];
	  check[m1]=0;

	  while (i2 <= i1)
	    {
	      if (aux3[m1] == words[i2])
		++check[m1];
	      i2++;
	    }
	  if (check[m1] == 0)
	    {
	      key_words.push_back(aux3[m1]);
	      m2++;
	    }
	  m1++;
	}
      l++;
    }
  vector<string>::iterator it;
  sort (key_words.begin(),key_words.end());
  it = unique(key_words.begin(),key_words.end());
  key_words.erase(it, key_words.end());
  m2 = key_words.size();

  string part_1[3000],part_2[3000];
  for (m1=0; m1<m2; m1++)
    {
      string::size_type p1[2100], p2[2100], d[2100], p_test[2100], p3[2100];
      for (l=0; l<j; l++)
	{
	  p1[l]= -1;
 	  p2[l]= 0;
   	  p_test[l] = titles[l].rfind(key_words[m1]);

	  if (p_test[l] == string::npos) {}

	  else
	    {
	      while (p2[l] != string::npos)
		{
		  part_1[l] = "";
		  part_2[l] = "";

		  p2[l] = titles[l].find(key_words[m1], p1[l]+1);
		  d[l] = p2[l] + key_words[m1].size();
		   
		  if(p2[l] == titles[l].size()-key_words[m1].size() || titles[l].at(p2[l]+key_words[m1].size()) == ' ')
			{
			  part_1[l] = titles[l].substr(0, p2[l]);
			  part_2[l] = titles[l].substr(d[l]);
			  
			  string key[3000], key_upper[3000];
			  key[m1] = key_words[m1];
			  key_upper[m1].resize(key[m1].length());
			  transform(key[m1].begin(), key[m1].end(), key_upper[m1].begin(), ::toupper);
			  
			  if (p2[l] == string::npos) {}
		      
			  else
			    cout << part_1[l] << key_upper[m1] << part_2[l] << endl;
			}
		  p1[l] = p2[l];
		}
	    }
	}
    }	 
  return 0;
}     
