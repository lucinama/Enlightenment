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
#include <pthread.h>

#include "elm_interface_atspi_accessible.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_text.h"
#include "elm_interface_scrollable.h"
}

#include <Elementary.hh>
#include <Eina.hh>

void
_btn_cb(void *data, ::elm_naviframe nf, void *event_info)
{
   Evas_Object *nf = data, *btn;
   if (!nf) return;

   ::elm_button btn(efl::eo::parent = nf);
elm_object_text_set(btn._eo_ptr(), "Go to Second Page.");  // XXX
   btn.callback_clicked_add(&_btn_cb);

   nf.item_push("Next Page", NULL, NULL, btn, NULL);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

::elm_win win(elm_win_util_standard_add("naviframe", "Naviframe"));
win.autodel_set(true);

::elm_naviframe nf(efl::eo::parent = win);
 nf.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   win.resize_object_add(nf);
 nf.visibility_set(true);

::elm_button btn(efl::eo::parent = nf);
btn = elm_button_add(nf);
elm_object_text_set(btn._eo_ptr(), "Go to Second Page."); // XXX
btn.callback_clicked_add(&_btn_cb);

nf.item_push(nf, "First Page", NULL, NULL, btn, NULL);

win.evas::object::size_set( 400, 400);
win.visibility_set(true);

elm_run();
elm_shutdown();

return 0;
}
ELM_MAIN()
