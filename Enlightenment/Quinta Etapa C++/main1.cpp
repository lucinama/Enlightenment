#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

  struct individual
  {
    string matricula[15];
    string nome[15];
    string sobrenome[15];
    string qualificacao[15];
    string especificacao[15];
  };
  struct aluno : individual
  {
    string turma[5];
  };
  struct professor : individual
  {
    string departamento[5];
  };
int main()
{
  int i1=0, i2=0, i3=0;
  string line;
  string::size_type p1, p2, p3, m1, m2, m3, n1, n2, n3;
  vector<string> linhas;
  ifstream arquivo;
  arquivo.open("cadastro.txt");
  string nome[15], qualificacao[15], especificacao[15], matricula[15];

  if (!arquivo)
    {
      cout << "Erro: Não foi possivel abrir cadastro.txt" << endl;
    }

  while(getline(arquivo, line))
    {
      linhas.push_back(line);
      cout << linhas[i1] << endl << endl;
      i1++;
    }
  i1=0;
  while(i1 < 4)
    {
      p1 = linhas[i1].find(".");
      p2 = linhas[i1].find(".",p1+1);
      p3 = linhas[i1].find(".",p2+1);
      n1 = p1 +1;
      n2 = p2 +1;
      n3 = p3 +1;
      m1 = p2 - p1 -1;
      m2 = p3 - p2 -1;
    
      matricula[i1] = linhas[i1].substr(0,p1);

      nome[i1] = linhas[i1].substr(n1,m1);
      
      qualificacao[i1] = linhas[i1].substr(n2,m2);
     
      especificacao[i1] = linhas[i1].substr(n3);

      cout << "Matricula: " << matricula[i1] << endl;
      cout << "Nome: "<< nome[i1] << endl;
      cout << "Qualificacao: " << qualificacao[i1] << endl;
      cout << "Especificacao: " << especificacao[i1] << endl << endl;
      i1++;
    }
  arquivo.close();
  return 0;
}
