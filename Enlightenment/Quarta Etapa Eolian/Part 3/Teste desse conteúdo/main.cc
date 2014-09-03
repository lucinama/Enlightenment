#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>

#define EFL_BETA_API_SUPPORT 1

#include <Eo.h>
#include <Eo.hh>

#include "simple.eo.hh"

int main(void)
{
  efl::eo::eo_init eo;

  //Eo *obj = eo_add(SIMPLE_CLASS, NULL);
  simple obj;
  int x = 0, y = 0, mxy = 0, dxy = 0;
  //eo_do(obj, simple_xy_set(10,5));
  obj.simple_x_set(10);
  obj.simple_y_set(5);

/* eo_do(obj, simple_xy_get(&x,&y), */
/*       mxy = interface_mxy_get(), */
/*       dxy = mixin_dxy_get()); */
  
  obj.simple_x_get(x);
  obj.simple_y_get(y);
  mxy = obj.mxy_get();
  dxy = obj.dxy_get();

/*   printf("%d vezes %d igual %d\n", x, y, mxy); */
/*   printf("%d divido por %d igual %d\n", x, y, dxy); */

  std::cout << x << " vezes " << y << " igual a " << mxy << endl;
  std::cout << x << " dividido por " << y << " igual a " << dxy << endl;
	     
  return 0;
}
