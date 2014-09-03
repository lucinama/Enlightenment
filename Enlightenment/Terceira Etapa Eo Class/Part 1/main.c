#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define EFL_BETA_API_SUPPORT 1

#include <Eo.h>
#include "eo_class.h"

int main(void)
{
  eo_init();
  
  Eo *obj = eo_add(SIMPLE_CLASS, NULL);

  eo_do(obj, simple_xy_set(10,5));

  int x = 0, y = 0, mxy = 0;

  printf("Erro3\n");
  eo_do(obj, simple_xy_get(&x,&y),
	simple_mxy_get(&mxy));

  printf("%d vezes %d igual %d", x, y, mxy);
	     
  eo_unref(obj);
  eo_shutdown();
  return 0;
}
      
