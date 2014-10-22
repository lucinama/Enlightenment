#ifdef HAVE_CONFIG_H
# include <elementary_config.h>
#endif

extern "C"
{
#define ELM_INTERNAL_API_ARGESFSDFEFC
#define ELM_INTERFACE_ATSPI_ACCESSIBLE_PROTECTED
#define ELM_INTERFACE_ATSPI_COMPONENT_PROTECTED
#define ELM_INTERFACE_ATSPI_ACTION_PROTECTED
#define ELM_INTERFACE_ATSPI_VALUE_PROTECTED
#define ELM_INTERFACE_ATSPI_EDITABLE_TEXT_PROTECTED
#define ELM_INTERFACE_ATSPI_TEXT_PROTECTED
#define ELM_INTERFACE_ATSPI_SELECTION_PROTECTED
#define ELM_INTERFACE_ATSPI_IMAGE_PROTECTED
#define ELM_INTERFACE_ATSPI_WIDGET_ACTION_PROTECTED

#include <Eo.h>
#include <Evas.h>
#include <Elementary.h>
#include <elm_widget.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>
#include <Eina.hh>

static void
_enabled_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *mb = data;
   elm_mapbuf_enabled_set(mb, elm_check_state_get(obj));
}

static void
_alpha_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *mb = data;
   elm_mapbuf_alpha_set(mb, elm_check_state_get(obj));
}

static void
_smooth_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *mb = data;
   elm_mapbuf_smooth_set(mb, elm_check_state_get(obj));
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   unsigned int i, j;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   ::elm_win win(elm_win_util_standard_add("mapbuf", "Mapbuf Example"));
  win.autodel_set(true);

  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

  ::elm_mapbuf mb(efl::eo::parent = win);
   mb.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   mb.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   bx.pack_end(mb);

   ::elm_table tb(efl::eo::parent = win);
   tb.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   tb.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   tb.visibility_set(true);

   for (i = 0; i < 8; i++)
     {
        for (j = 0; j < 8; j++)
          {
	      ::elm_icon ic(efl::eo::parent = win);
             ic = elm_icon_add(win);
             ic.standard_set("home");
             ic.resizable_set(EINA_FALSE, EINA_FALSE);
	     ic.visibility_set(true);
             tb.pack(ic, i, j, 1, 1);
          }
     }

   elm_object_content_set(mb._eo_ptr(), tb._eo_ptr());  // XXX
   mb.visibility_set(true);

   ::elm_box hbx(efl::eo::parent = win);
   hbx.horizontal_set(EINA_TRUE);
   hbx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   hbx.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
   bx.pack_end(hbx);
   hbx.visibility_set(true);

   ::elm_check tg(efl::eo::parent = win);
   tg.style_set("toggle");
   tg.text_set("on", "Enabled");   // XXX
   tg.text_set("off", "Disabled");
   elm_object_text_set(tg._eo_ptr(), "Map");  // XXX
   tg.callback_changed_add(&_enabled_cb);
   hbx.pack_end(tg);
   tg.visibility_set(true);

   ::elm_check ck(efl::eo::parent = win);
   elm_object_text_set(ck._eo_ptr(), "Alpha");  // XXX
   ck.state_set(EINA_TRUE);
   ck.callback_changed_add(&_alpha_cb);
   hbx.pack_end(ck);
   ck.visibility_set(true);

   ::elm_check ck2(efl::eo::parent = win);
   elm_object_text_set(ck2._eo_ptr(), "Smooth");  // XXX
   ck2.state_set(EINA_TRUE);
   ck2.callback_changed_add(&_smooth_cb);
   hbx.pack_end(ck2);
   ck2.visibility_set(true);

   win.evas::object::size_set(240, 320);
   win.visibility_set(true);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
