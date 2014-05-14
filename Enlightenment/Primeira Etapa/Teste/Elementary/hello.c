#include <Elementary.h>

static void
win_del(void *data, Evas_Object *obj, void *event_info)
{
   elm_exit();
}

EAPI int
elm_main(int argc, char **argv)
{
   Evas_Object *win, *bg, *lb;

   win = elm_win_add(NULL, "hello", ELM_WIN_BASIC);
   elm_win_title_set(win, "Hello");
   evas_object_smart_callback_add(win, "delete,request", win_del, NULL);

   bg = elm_bg_add(win);
   evas_object_size_hint_weight_set(bg, 1.0, 1.0);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   lb = elm_label_add(win);
   elm_object_text_set(lb, "Hello World!");
   evas_object_size_hint_weight_set(lb, 1.0, 1.0);
   elm_win_resize_object_add(win, lb);
   evas_object_show(lb);

   evas_object_show(win);

   elm_run();
   elm_shutdown();
   return 0;
}
ELM_MAIN()
