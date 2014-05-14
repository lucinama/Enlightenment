#include <iostream>

int n,c;
int main()
{
  std::cout<<"digite o numero";
  std::cin>>c;
  n=c+1;
  while(n>1){
    std::cout<<"*";
    n=c--;}
  return 0;
}
