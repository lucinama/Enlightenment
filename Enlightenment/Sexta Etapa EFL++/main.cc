#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

#include <Eina.h>
#include <Eo.h>

#include <Eina.hh>
#include <Eo.hh>

using namespace std;

  struct individual {
    string matr;
    string nome;
    string quali;
    string espec;
  };



bool cmp(const individual &a, const individual &b)
{
  return a.matr < b.matr;
}

bool pred(const individual &a, const individual &b)
{
  return a.matr == b.matr;
}

int main()
{
  individual x;
  efl::eina::ptr_array<individual> pessoas;
  efl::eina::ptr_array<individual>::iterator it;
  ifstream arquivo;
  arquivo.open("cadastro.txt");
  string line;
  if (!arquivo)
    {
      cout << "Erro: Não foi possivel abrir cadastro.txt" << endl;
    }
  while(getline(arquivo, line))
    {
      int p1, p2, p3, m1, m2, n1, n2, n3;
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
      cout << "Especificacao: " << x.espec << endl<< endl;
      pessoas.push_back(x);
    }
  size_t n_before = pessoas.size();
  sort (pessoas.begin(), pessoas.end(), cmp);
  it = unique(pessoas.begin(), pessoas.end(), pred);
  pessoas.erase(it, pessoas.end());

  size_t n_after = pessoas.size();
  if (n_after < n_before)
    {
      cout << "Removed " << (n_before-n_after) << " repeated entries." << endl;
    }
  arquivo.close();
  return 0;
}

