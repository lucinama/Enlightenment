#include <iostream>
#include <iomanip>
#include <map>
	 
using namespace std;

int main()
{
  map<string,string> cadastro;
  map<string,string>::iterator it;
  
  string line = "sim";
  int a;
  
  cout << "Quantos alunos você deseja cadastrar?" << endl;
  cin >> a;
  cin.ignore();

  for(int i=0; i < a; i++)
    {
      string matricula, aluno;
      
      cout << "Digite a matrícula" << endl;
      getline(cin,matricula);
      
      cout << "Digite o nome completo do respectivo aluno" << endl;
      getline(cin,aluno);
      
      cadastro.insert(pair<string,string>(matricula,aluno));
      
    }
  
  string line3;
  cout << endl << "Digite a matrícula do aluno que deseja procurar" << endl;
  getline(cin,line3);
  if (cadastro.find(line3) != cadastro.end())
    cout << "O nome do aluno de matrícula " << line3 << " é: " << (*cadastro.find(line3)).second << endl << endl;
  else
    cout << "Matrícula não encontrada" << endl;


  cout << endl << "Ordenando por ordem alfabética:" << endl;
  multimap<string,string> cadastro_alfab;
  multimap<string,string>::iterator it_m;
  for(it=cadastro.begin(); it != cadastro.end(); ++it)
    { 
      string y = it->first, x = it->second;
      cadastro_alfab.insert(pair<string,string>(x,y));
    }
  for(it_m = cadastro_alfab.begin(); it_m != cadastro_alfab.end(); ++it_m)
    cout << "Matrícula: " << it_m->second << " / Aluno(a): " << it_m->first << endl;
  
  cout << endl << "Ordenando pelo número de matrícula:" << endl;
  cout << "Você cadastrou os seguintes alunos:" << endl;
  for (it=cadastro.begin(); it != cadastro.end(); ++it)
    cout << "Matrícula: " << it->first << " / Aluno(a): " << it->second << endl;
  int size_before = cadastro.size();

  cout << endl << "Digite a matrícula do aluno a ser decadastrado" << endl;
  getline(cin,line3);
  it = cadastro.find(line3);
  if (it != cadastro.end())
    {
      cadastro.erase(it);
      cout << "Você não decadastrou os seguintes alunos:" << endl;
      for (it=cadastro.begin(); it!=cadastro.end(); ++it)
	cout << "Matrícula: " << it->first << " / Aluno(a): " << it->second << endl;
    }
  else
    cout << "Matrícula não encontrada. Não houve alteração no cadastro" << endl << endl;

  return 0;
}
