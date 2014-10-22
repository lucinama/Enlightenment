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

#include <time.h>

typedef struct Progressbar_Example
{
   Evas_Object *pb1;
   Evas_Object *pb2; /* pulsing */
   Evas_Object *pb3;
   Evas_Object *pb4;
   Evas_Object *pb5;
   Evas_Object *pb6; /* pulsing */
   Evas_Object *pb7;
   Evas_Object *pb8; /* pulsing */

   Eina_Bool    run;
   Ecore_Timer *timer;
} Progressbar_Example;

static Progressbar_Example example_data;

static Eina_Bool
_progressbar_example_value_set(::elm_progressbar data)
{
   double progress;

   progress = example_data.pb1.value_get();
   if (progress < 1.0) progress += 0.0123;
   else progress = 0.0;

   /* just the non-pulsing ones need an update */
   example_data.pb1.value_set(progress);
   example_data.pb3.value_set(progress);
   example_data.pb4.value_set(progress);
   example_data.pb5.value_set(progress);
   example_data.pb7.value_set(progress);

   if (progress < 1.0) return ECORE_CALLBACK_RENEW;

   example_data.run = 0;
   return ECORE_CALLBACK_CANCEL;
}

static void
_progressbar_example_start(::elm_progressbar data, Evas_Object *obj, void *event_info)
{
  example_data.pb2.pulse(EINA_TRUE);
  example_data.pb6.pulse(EINA_TRUE);
  example_data.pb8.pulse(EINA_TRUE);

  if (!example_data.run)
    {
      example_data.timer = ecore_timer_add(0.1, _progressbar_example_value_set, NULL);
      example_data.run = EINA_TRUE;
    }
}

static void
_progressbar_example_stop(void *data, Evas_Object *obj, void *event_info)
{
  example_data.pb2.pulse(EINA_FALSE);
  example_data.pb6.pulse(EINA_FALSE);
  example_data.pb8.pulse(EINA_FALSE);

  if (example_data.run)
    {
      ecore_timer_del(example_data.timer);
      example_data.run = EINA_FALSE;
    }
}

static char *
_progress_format_cb(double val)
{
  static char buf[30];
  int files = (1-val)*14000;
  if (snprintf(buf, 30, "%i files left", files) > 0)
    return strdup(buf);
  return NULL;
}

static void
_progress_format_free(char *str)
{
  free(str);
}

static void
_on_changed(void        *data,
            ::elm_progressbar obj,
            void        *event_info)
{
  static char buf[30];
  static time_t tstart = 0;
  static double eta = 0;
  time_t tdiff;
  double val;
  Evas_Object *label =  (Evas_Object *)data;

  val = obj.value_get();
  if (val == 0)
    {
      tstart = 0;
      elm_object_text_set(label._eo_ptr(), "ETA: N/A");   // XXX
      return;
    }

  if (tstart == 0)
    {
      tstart = time(NULL);
    }

  tdiff = time(NULL) - tstart;
  eta = 0.3*eta + 0.7*(tdiff/val)*(1-val);
  snprintf(buf, 30, "ETA: %.0fs", eta);
  elm_object_text_set(label._eo_ptr(), buf); // XXX
}

static void
_on_done(void        *data,
         Evas_Object *obj,
         void        *event_info)
{
  _progressbar_example_stop(NULL, NULL, NULL);
  elm_exit();
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  char buf[PATH_MAX];

  elm_app_info_set(elm_main, "elementary", "images/logo_small.png");

  ::elm_win win(elm_win_util_standard_add("progressbar", "Progress bar example"));
  win.callback_delete_request_add(&_on_done);

  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

 ::elm_progressbar pb(efl::eo::parent = win);
  pb.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  pb.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  bx.pack_end(pb);
  pb.visibility_set(true);
  example_data.pb1 = pb;

  ::elm_progressbar pb2(efl::eo::parent = win);
  pb2.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  pb2.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  elm_object_text_set(pb2._eo_ptr(), "Infinite bounce");  // XXX
  pb2.pulse_set(EINA_TRUE);
  bx.pack_end(pb2);
  pb2.visibility_set(true);
  example_data.pb2 = pb2;

  ::elm_icon ic1(efl::eo::parent = win);
  snprintf(buf, sizeof(buf), "%s/images/logo_small.png", elm_app_data_dir_get());
  elm_image_file_set(ic1, buf, NULL);
  ic1.size_hint_aspect_set(EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);

  ::elm_progressbar pb3(efl::eo::parent = win);
  elm_object_text_set(pb3._eo_ptr(), "Label");   // XXX
  pb3.content_set("icon", ic1);
  pb3.inverted_set(EINA_TRUE);
  pb3.unit_format_function_set(_progress_format_cb, _progress_format_free);
  pb3.span_size_set(200);
  pb3.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  pb3.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(pb3);
  ic1.visibility_set(true);
  pb3.visibility_set(true);
  example_data.pb3 = pb3;

  ::elm_progressbar pb4(efl::eo::parent = win);
  elm_object_text_set(pb4._eo_ptr(), "Label");  // XXX
  pb4.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  pb4.size_hint_weight_set( EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(pb4);
  pb4.visibility_set(true);

  ::elm_label label(efl::eo::parent = win);
  elm_object_text_set(label._eo_ptr(), "ETA: N/A");   // XXX
  label.size_hint_align_set(0.5, 0.5);
  label.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(label);
  label.visibility_set(true);

  pb4.callback_changed_add(&_on_changed);
  example_data.pb4 = pb4;

  ::elm_box hbx(efl::eo::parent = win);
  hbx.horizontal_set(EINA_TRUE);
  hbx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  hbx.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx.pack_end(hbx);
  hbx.visibility_set(true);

  ::elm_progressbar pb5(efl::eo::parent = win);
  pb5.horizontal_set(pb, EINA_FALSE);
  pb5.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  pb5.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  hbx.pack_end(pb5);
  elm_object_text_set(pb5._eo_ptr(), "percent");   // XXX
  pb.visibility_set(true);
  example_data.pb5 = pb5;

  ::elm_progressbar pb6(efl::eo::parent = win);
  pb6.horizontal_set(EINA_FALSE);
  pb6.size_hint_align_set( EVAS_HINT_FILL, 0.5);
  pb6.size_hint_weight_set( EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  pb6.span_size_set(80);
  pb6.pulse_set(EINA_TRUE);
  pb6.unit_format_set(NULL);
  elm_object_text_set(pb6._eo_ptr(), "Infinite bounce");   // XXX
  hbx.pack_end(pb6);
  pb6.visibility_set(true);
  example_data.pb6 = pb6;

  ::elm_icon ic2(efl::eo::parent = win);
  ic2.file_set(buf, NULL);
  ic2.size_hint_aspect_set(EVAS_ASPECT_CONTROL_HORIZONTAL, 1, 1);

  ::elm_progressbar pb7(efl::eo::parent = win);
  pb7.horizontal_set(EINA_FALSE);
  elm_object_text_set(pb7._eo_ptr(), "Label");
  pb7.content_set("icon", ic2);
  pb7.inverted_set(EINA_TRUE);
  pb7.unit_format_set( "%1.2f%%");
  pb7.span_size_set(200);
  pb7.size_hint_align_set(EVAS_HINT_FILL, 0.5);
  pb7.size_hint_weight_set( EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  hbx.pack_end(pb7);
  ic2.visibility_set(true);
  pb7.visibility_set(true);
  example_data.pb7 = pb7;

  ::elm_progressbar pb8(efl::eo::parent = win);
  pb8.style_set("wheel");
  elm_object_text_set(pb8._eo_ptr(), "Style: wheel");   // XXX
  pb8.pulse_set(EINA_TRUE);
  pb8.size_hint_align_set( EVAS_HINT_FILL, 0.5);
  pb8.size_hint_weight_set( EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(pb8);
  pb8.visibility_set(true);
  example_data.pb8 = pb8;

  ::elm_box bt_bx(efl::eo::parent = win);
  bt_bx.horizontal_set(EINA_TRUE);
  bt_bx.size_hint_weight_set( EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx.pack_end(bt_bx);
  bt_bx.visibility_set(true);

 ::elm_button bt(efl::eo::parent = win);
  elm_object_text_set(bt._eo_ptr(), "Start");  // XXX
  bt.callback_clicked_add(&_progressbar_example_start);
  bt_box.pack_end( bt);
  bt.visibility_set(true);

  ::elm_button bt2(efl::eo::parent = win);
  elm_object_text_set(bt2._eo_ptr(), "Stop");   // XXX
  bt2.callback_clicked_add(&_progressbar_example_stop);
  bt_bx.pack_end(bt2);
  bt2.visibility_set(true);

  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
