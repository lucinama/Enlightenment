#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define EFL_BETA_API_SUPPORT 1

#include <Eo.h>
#include "simple.eo.h"

int main(void)
{
  eo_init();
  
  Eo *obj = eo_add(SIMPLE_CLASS, NULL);

  eo_do(obj, simple_xy_set(10,5));

  int x = 0, y = 0, mxy = 0;

eo_do(obj, simple_xy_get(&x,&y),
	mxy = interface_mxy_get());

  printf("%d vezes %d igual %d\n", x, y, mxy);
	     
  eo_unref(obj);
  eo_shutdown();
  return 0;
}
