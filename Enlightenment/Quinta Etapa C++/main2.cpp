#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

  struct individual {
    string matr;
    string nome;
    string quali;
    string espec;
  };

individual
individual_parse_line(std::string line)
{
  individual x;
  string::size_type p1, p2, p3, m1, m2, n1, n2, n3;
  p1 = line.find(".");
  p2 = line.find(".",p1+1);
  p3 = line.find(".",p2+1);
  n1 = p1 +1;
  n2 = p2 +1;
  n3 = p3 +1;
  m1 = p2 - p1 -1;
  m2 = p3 - p2 -1;
  x.matr = line.substr(0,p1);
  x.nome = line.substr(n1,m1);
  x.quali = line.substr(n2,m2);
  x.espec = line.substr(n3);
  cout << "Matricula: " << x.matr << endl;
  cout << "Nome: "<< x.nome << endl;
  cout << "Qualificacao: " << x.quali << endl;
  cout << "Especificacao: " << x.espec << endl;
  return x;
}

int main()
{
  int i;
  ifstream arquivo;
  arquivo.open("cadastro.txt");
  vector<individual> pessoas;
  string line;
  if (!arquivo)
    {
      cout << "Erro: Não foi possivel abrir cadastro.txt" << endl;
    }
  while(getline(arquivo, line))
    {
      individual x = individual_parse_line(line);
      pessoas.push_back(x);
      i++;
    }

  // for (int t = 0; t <= i; t++)
  //   {
  //     for (int j = t+1; j < i;j++)
  // 	{
  // 	  if (x.matr[j] == x.matr[t])
  //  	    {
  //  	      cout << "pessoa da linha " << t+1 << " cadastrada novamente na linha " << j+1 << endl;
  // 	    }
  //  	}
  //   }
  arquivo.close();
  return 0;
  
}
