#ifdef HAVE_CONFIG_H
# include <elementary_config.h>
#endif

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
#include "elm_interface_atspi_accessible.eo.h"
#include "elm_interface_atspi_widget_action.h"
#include "elm_interface_atspi_widget_action.eo.h"

#include <elm_win.eo.hh>
#include <elm_box.eo.hh>
#include <elm_button.eo.hh>
#include <elm_image.eo.hh>

#include <Elementary.h>

typedef struct
{
   Evas_Object *mid;
   Evas_Object *icon_still;
   struct
     {
        Evas_Object *up;
        Evas_Object *down;
        Evas_Object *left;
        Evas_Object *right;
     } cursors;
} App_Data;

static void
_btn_cursors_release_cb(void *data, Evas_Object *btn, void *ev)
{
   App_Data *app = data;
   elm_object_part_content_set(app->mid, "icon", app->icon_still);
   app->icon_still = NULL;
}

static void
_btn_cursors_move_cb(void *data, Evas_Object *btn, void *ev)
{
   App_Data *app = data;
   double ax, ay;

   if (!app->icon_still)
     {
        Evas_Object *icon;
        app->icon_still = elm_object_content_unset(app->mid);
        evas_object_hide(app->icon_still);
        icon = elm_icon_add(app->mid);
        elm_icon_standard_set(icon, "chat");
        elm_object_part_content_set(app->mid, "icon", icon);
     }

   evas_object_size_hint_align_get(app->mid, &ax, &ay);
   if (btn == app->cursors.up)
     {
        ay -= 0.05;
        if (ay < 0.0)
          ay = 0.0;
     }
   else if (btn == app->cursors.down)
     {
        ay += 0.05;
        if (ay > 1.0)
          ay = 1.0;
     }
   else if (btn == app->cursors.left)
     {
        ax -= 0.05;
        if (ax < 0.0)
          ax = 0.0;
     }
   else if (btn == app->cursors.right)
     {
        ax += 0.05;
        if (ax > 1.0)
          ax = 1.0;
     }
   evas_object_size_hint_align_set(app->mid, ax, ay);
}

static void
_btn_options_cb(void *data, Evas_Object *btn, void *ev)
{
   char *ptr;
   double t;
   App_Data *app = data;
   const char *lbl = elm_object_text_get(btn);

   ptr = strchr(lbl, ':');
   ptr += 2;
   t = strtod(ptr, NULL);

   if (!strncmp(lbl, "Initial", 7))
     {
        elm_button_autorepeat_initial_timeout_set(app->cursors.up, t);
        elm_button_autorepeat_initial_timeout_set(app->cursors.down, t);
        elm_button_autorepeat_initial_timeout_set(app->cursors.left, t);
        elm_button_autorepeat_initial_timeout_set(app->cursors.right, t);
     }
   else if (!strncmp(lbl, "Gap", 3))
     {
        elm_button_autorepeat_gap_timeout_set(app->cursors.up, t);
        elm_button_autorepeat_gap_timeout_set(app->cursors.down, t);
        elm_button_autorepeat_gap_timeout_set(app->cursors.left, t);
        elm_button_autorepeat_gap_timeout_set(app->cursors.right, t);
     }
}

EAPI_MAIN int
elm_main(int argc, char *argv[])
{
   Evas_Object *win, *box, *box2, *btn, *icon;
   static App_Data data;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   win = elm_win_util_standard_add("Button example", "Button example");
   elm_win_autodel_set(win, EINA_TRUE);

   box = elm_box_add(win);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, box);
   evas_object_show(box);

   box2 = elm_box_add(win);
   elm_box_horizontal_set(box2, EINA_TRUE);
   evas_object_size_hint_weight_set(box2, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(box, box2);
   evas_object_show(box2);

   btn = elm_button_add(win);
   elm_object_text_set(btn, "Initial: 0.0");
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _btn_options_cb, &data);

   btn = elm_button_add(win);
   elm_object_text_set(btn, "Initial: 1.0");
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _btn_options_cb, &data);

   btn = elm_button_add(win);
   elm_object_text_set(btn, "Initial: 5.0");
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _btn_options_cb, &data);

   box2 = elm_box_add(win);
   elm_box_horizontal_set(box2, EINA_TRUE);
   evas_object_size_hint_weight_set(box2, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(box, box2);
   evas_object_show(box2);

   btn = elm_button_add(win);
   elm_object_text_set(btn, "Gap: 0.1");
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _btn_options_cb, &data);

   btn = elm_button_add(win);
   elm_object_text_set(btn, "Gap: 0.5");
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _btn_options_cb, &data);

   btn = elm_button_add(win);
   elm_object_text_set(btn, "Gap: 1.0");
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _btn_options_cb, &data);

   btn = elm_button_add(win);
   elm_button_autorepeat_set(btn, EINA_TRUE);
   elm_button_autorepeat_initial_timeout_set(btn, 1.0);
   elm_button_autorepeat_gap_timeout_set(btn, 0.5);
   evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 0.0);
   elm_box_pack_end(box, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "repeated", _btn_cursors_move_cb, &data);
   evas_object_smart_callback_add(btn, "unpressed", _btn_cursors_release_cb,
                                  &data);

   icon = elm_icon_add(win);
   elm_icon_standard_set(icon, "arrow_up");
   elm_object_part_content_set(btn, "icon", icon);

   data.cursors.up = btn;

   box2 = elm_box_add(win);
   elm_box_horizontal_set(box2, EINA_TRUE);
   evas_object_size_hint_weight_set(box2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(box2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, box2);
   evas_object_show(box2);

   btn = elm_button_add(win);
   elm_button_autorepeat_set(btn, EINA_TRUE);
   elm_button_autorepeat_initial_timeout_set(btn, 1.0);
   elm_button_autorepeat_gap_timeout_set(btn, 0.5);
   evas_object_size_hint_weight_set(btn, 0.0, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, 0.0, EVAS_HINT_FILL);
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "repeated", _btn_cursors_move_cb, &data);
   evas_object_smart_callback_add(btn, "unpressed", _btn_cursors_release_cb,
                                  &data);

   icon = elm_icon_add(win);
   elm_icon_standard_set(icon, "arrow_left");
   elm_object_part_content_set(btn, "icon", icon);

   data.cursors.left = btn;

   btn = elm_button_add(win);
   evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);

   icon = elm_icon_add(win);
   elm_icon_standard_set(icon, "close");
   elm_object_part_content_set(btn, "icon", icon);

   data.mid = btn;

   btn = elm_button_add(win);
   elm_button_autorepeat_set(btn, EINA_TRUE);
   elm_button_autorepeat_initial_timeout_set(btn, 1.0);
   elm_button_autorepeat_gap_timeout_set(btn, 0.5);
   evas_object_size_hint_weight_set(btn, 0.0, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, 0.0, EVAS_HINT_FILL);
   elm_box_pack_end(box2, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "repeated", _btn_cursors_move_cb, &data);
   evas_object_smart_callback_add(btn, "unpressed", _btn_cursors_release_cb,
                                  &data);

   icon = elm_icon_add(win);
   elm_icon_standard_set(icon, "arrow_right");
   elm_object_part_content_set(btn, "icon", icon);

   data.cursors.right = btn;

   btn = elm_button_add(win);
   elm_button_autorepeat_set(btn, EINA_TRUE);
   elm_button_autorepeat_initial_timeout_set(btn, 1.0);
   elm_button_autorepeat_gap_timeout_set(btn, 0.5);
   evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, 0.0);
   elm_box_pack_end(box, btn);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "repeated", _btn_cursors_move_cb, &data);
   evas_object_smart_callback_add(btn, "unpressed", _btn_cursors_release_cb,
                                  &data);

   icon = elm_icon_add(win);
   elm_icon_standard_set(icon, "arrow_down");
   elm_object_part_content_set(btn, "icon", icon);

   data.cursors.down = btn;

   evas_object_resize(win, 300, 320);
   evas_object_show(win);

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()






#include <Eina.hh>

struct clean_ref
{
  clean_ref(efl::eo::base base)
    : _ref(base._eo_ptr())
  {}

  template <typename T>
  void operator()(T const&, Eo_Event_Description const&, void*) const
  {
    if(_ref)
      eo_unref(_ref);
  }

  Eo* _ref;
};

static void
on_click(void *data, Evas_Object *obj, void *event_info)
{
  elm_exit();
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   
  ::elm_win win(elm_win_util_standard_add("Greetings", "Hello, World!"));
  win.autodel_set(true);

  ::elm_button btn(efl::eo::parent = win);
  btn.text_set("elm.text","Good-Bye, World!");
  btn.callback_clicked_add(on_click);
  btn.size_set(120, 30);
  btn.position_set(60, 15);
  // btn.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  // btn.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  btn.visibility_set(true);

  win.size_set(240, 60);
  win.visibility_set(true);

  win._release();
  
  elm_run();
  elm_shutdown();

  return 0;

}
ELM_MAIN();
