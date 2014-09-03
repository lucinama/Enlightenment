#include <iostream>

int main()
{

    int tent=0;
    while(tent<2){
      std::cout<<"Vc quer proceder(y ou n)?"<<"\n";
      char answer=0;
      std::cin>>answer;
    
      if(answer=='y'){
	std::cout<<"Proceder\n";
	tent++;}
      else if(answer=='n'){
	tent++;
	std::cout<<"Nao proceder, tentativa "<<tent<<"\n";}
      else  {
	tent++;
	std::cout<<"Caracter invalido, tentativa "<<tent<<"\n";}
    }
    return 0; 
}

      
      

