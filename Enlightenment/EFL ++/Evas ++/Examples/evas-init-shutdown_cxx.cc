#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <Evas.h>

#include <Eo.hh>
#include <Eina.hh>
#include <Evas.hh>
#include <Efl.hh>

#include <stdio.h>
#include <iostream>
#include <errno.h>

int
main(void)
{
   Eina_List *engine_list, *l;
   char *engine_name;

   efl::eina::eina_init eina_init;
   efl::eo::eo_init init;

   engine_list = evas_render_method_list();
   if (!engine_list)
     {
        fprintf(stderr, "ERROR: Evas supports no engines! Exit.\n");
        exit(-1);
     }

   std::cout << "Available Evas Engines:" << std::endl;
   EINA_LIST_FOREACH(engine_list, l, engine_name)
     std::cout << engine_name << std::endl;

   evas_render_method_list_free(engine_list);

   evas_shutdown();
   return 0;
}
