#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
  struct grupo
  {
    string g[];
  };
  struct aluno
  {
    string a[];
  };
  struct professor
  {
    string p[];
  };
  
  grupo g[50];
  aluno a[50];
  professor p[50];

  int matricula[50], i=0;
  string nome[50], sobrenome[50], qualificacao[50], especificacao[50];
  string line;

  ifstream arquivo;
  arquivo.open("cadastro.txt", ios::in);

  while(getline(arquivo,line)) {
    stringstream input(line);
    input >> matricula[i] >> nome[i] >> sobrenome[i] >> qualificacao[i] >> especificacao[i];
    if(input) { 
      
      if(qualificacao[i]=="Aluno") {
	cout << "Aluno: " << "000" << matricula[i] <<" "<< nome[i] <<" "<< sobrenome[i] <<" Turma "<< especificacao[i] << "\n";
      }
      if(qualificacao[i]=="Professor") {
	cout << "Professor: " << "000" << matricula[i] <<" "<< nome[i] <<" "<< sobrenome[i] <<" Departamento "<< especificacao[i] << "\n";   
      }
    }
  }
arquivo.close();
return 0;
}


  

