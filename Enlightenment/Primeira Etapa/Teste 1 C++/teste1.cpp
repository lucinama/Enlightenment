#include <iostream>

int main()
{
  int x;
  int *p =&x;
  *p=10;

  std::cout<<x<<std::endl;
  return 0;
  
}
