#include <stdio.h>
#include <Evas.h>

#ifdef EAPI
# undef EAPI
#endif

/*EAPI int ecore_evas_init(void);
EAPI Ecore_Evas*
*/
/* EAPI Ecore_Evas * */
/* ecore_evas_ews_new(int x, int y, int w, int h) */
/* { */
/* // basically a copy of ecore_evas_buffer_new() keep in sync... */
/*    Evas_Object *o; */
/*    Evas_Engine_Info_Buffer *einfo; */
/*    Ecore_Evas *ee; */
/*    int rmethod; */
/*    static Eina_Bool creating = EINA_FALSE; */

/*    if (_ecore_evas_ews_init() < 1) return NULL; */

/*    if (creating) return NULL; /\* avoid recursive ecore_evas_new() with ews *\/ */
/*    creating = EINA_TRUE; */
/*    if (!_ews_ee) _ews_ee = _ecore_evas_ews_ee_new(); */
/*    creating = EINA_FALSE; */
/*    if (!_ews_ee) */
/*      { */
/*         ERR("Could not create EWS backing store"); */
/*         _ecore_evas_ews_shutdown(); */
/*         return NULL; */
/*      } */
/* } */

int main()
{
  if (ecore_evas_init() <= 0)
    return 1;


  int x=500, y=600, w=450, h=750;
  Eina_Bool ee = ecore_evas_ews_setup (x,y,w,h);
  //ecore_evas_ews_evas_get()
  return 0;
}
 
