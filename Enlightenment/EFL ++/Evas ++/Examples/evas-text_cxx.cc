#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define PACKAGE_EXAMPLES_DIR "/home/luciana/Enlightenment/scr/efl/src/examples/evas"
#endif

#include <Ecore.h>
#include <Ecore_Evas.h>
#include <stdio.h>
#include <errno.h>

#include <Eina.hh>
#include <Evas.hh>
#include <Eo.hh>
#include <Efl.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"
#include "canvas/evas_image.eo.hh"
#include "canvas/evas_text.eo.hh"

#define WIDTH  (320)
#define HEIGHT (240)

#define GREY {190, 190, 190, 255}
#define BLACK {0, 0, 0, 255}
#define WHITE {255, 255, 255, 255}
#define RED   {255, 0, 0, 255}
#define GREEN {0, 255, 0, 255}
#define BLUE  {0, 0, 255, 255}

#define POINTER_CYCLE(_ptr, _array)					\
  do									\
    {									\
      if ((unsigned int)(((unsigned char *)(_ptr)) - ((unsigned char *)(_array))) >= \
	  sizeof(_array))						\
	_ptr = _array;							\
    }									\
  while(0)

static const char *commands = \
  "commands are:\n"
  "\tt - change text's current style\n"
  "\tz - change text's font size\n"
  "\tf - change text's font family\n"
  "\tb - change text's base color\n"
  "\ts - change text's \'shadow\' color\n"
  "\to - change text's \'outline\' color\n"
  "\tw - change text's \'glow\' color\n"
  "\tg - change text's \'glow 2\' color\n"
  "\th - print help\n";

static const char *border_img_path = PACKAGE_EXAMPLES_DIR "/red.png";

struct color_tuple
{
  int r, g, b, a;
};

struct text_preset_data
{
  const char        **font_ptr;
  const char         *font[3];

  struct color_tuple *text_ptr;
  struct color_tuple  text[6];

  struct color_tuple *shadow_ptr;
  struct color_tuple  shadow[4];

  struct color_tuple *outline_ptr;
  struct color_tuple  outline[4];

  struct color_tuple *glow_ptr;
  struct color_tuple  glow[4];

  struct color_tuple *glow2_ptr;
  struct color_tuple  glow2[4];
};

Ecore_Evas *ee;
evas::canvas canvas(::eo_ref(::ecore_evas_get(ee)));
struct text_preset_data t_data;
evas::rectangle bg(efl::eo::parent = canvas);
evas::text text(efl::eo::parent = canvas);
evas::image border(efl::eo::parent = canvas);

static void
_on_destroy(Ecore_Evas *ee EINA_UNUSED)
{
  ecore_main_loop_quit();
}

static void
_canvas_resize_cb(Ecore_Evas *ee)
{
  int w, h;

  ::ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
  bg.evas::object::size_set(w, h);
}

static const char *
_text_style_type_to_str(Evas_Text_Style_Type mode)
{
  switch (mode)
    {
    case EVAS_TEXT_STYLE_PLAIN:
      return "plain";

    case EVAS_TEXT_STYLE_SHADOW:
      return "shadow";

    case EVAS_TEXT_STYLE_OUTLINE:
      return "outline";

    case EVAS_TEXT_STYLE_SOFT_OUTLINE:
      return "soft outline";

    case EVAS_TEXT_STYLE_GLOW:
      return "glow";

    case EVAS_TEXT_STYLE_OUTLINE_SHADOW:
      return "outline shadow";

    case EVAS_TEXT_STYLE_FAR_SHADOW:
      return "far shadow";

    case EVAS_TEXT_STYLE_OUTLINE_SOFT_SHADOW:
      return "outline soft shadow";

    case EVAS_TEXT_STYLE_SOFT_SHADOW:
      return "soft shadow";

    case EVAS_TEXT_STYLE_FAR_SOFT_SHADOW:
      return "far soft shadow";

    default:
      return "invalid";
    }
}

static void
_on_keydown(void *data EINA_UNUSED, Evas *evas EINA_UNUSED, Evas_Object *o EINA_UNUSED, Evas_Event_Key_Down *ev)
{
  //Evas_Event_Key_Down *ev = einfo;

  if (strcmp(ev->key, "h") == 0)
    {
      fprintf(stdout, commands);
      return;
    }

  if (strcmp(ev->key, "t") == 0)
    {
      Evas_Text_Style_Type type = text.style_get();

      type = (type + 1) % 10;

      text.style_set(type);

      fprintf(stdout, "Changing text's style to \'%s\'\n",
	      _text_style_type_to_str(type));

      return;
    }

  if (strcmp(ev->key, "f") == 0)
    {
      int sz;

      (t_data.font_ptr)++;

      text.font_get(NULL, &sz);

      POINTER_CYCLE(t_data.font_ptr, t_data.font);

      text.font_set(*t_data.font_ptr, sz);

      fprintf(stdout, "Changing text's font to %s\n", *t_data.font_ptr);

      return;
    }

  if (strcmp(ev->key, "b") == 0)
    {
      (t_data.text_ptr)++;

      POINTER_CYCLE(t_data.text_ptr, t_data.text);

      text.color_set(t_data.text_ptr->r, t_data.text_ptr->g, t_data.text_ptr->b, t_data.text_ptr->a);

      fprintf(stdout, "Changing base color for text to (%d, %d, %d, %d)\n", t_data.text_ptr->r, t_data.text_ptr->g, t_data.text_ptr->b, t_data.text_ptr->a);

      return;
    }

  if (strcmp(ev->key, "g") == 0)
    {
      (t_data.glow2_ptr)++;

      POINTER_CYCLE(t_data.glow2_ptr, t_data.glow2);

      text.glow2_color_set(t_data.glow2_ptr->r, t_data.glow2_ptr->g, t_data.glow2_ptr->b, t_data.glow2_ptr->a);

      fprintf(stdout, "Changing glow 2 color for text to (%d, %d, %d, %d)\n",
	      t_data.glow2_ptr->r, t_data.glow2_ptr->g,
	      t_data.glow2_ptr->b, t_data.glow2_ptr->a);

      return;
    }

  if (strcmp(ev->key, "w") == 0)
    {
      (t_data.glow_ptr)++;

      POINTER_CYCLE(t_data.glow_ptr, t_data.glow);

      text.glow_color_set(t_data.glow_ptr->r, t_data.glow_ptr->g, t_data.glow_ptr->b, t_data.glow_ptr->a);

      fprintf(stdout, "Changing glow color for text to (%d, %d, %d, %d)\n",
	      t_data.glow_ptr->r, t_data.glow_ptr->g,
	      t_data.glow_ptr->b, t_data.glow_ptr->a);

      return;
    }

  if (strcmp(ev->key, "o") == 0)
    {
      (t_data.outline_ptr)++;

      POINTER_CYCLE(t_data.outline_ptr, t_data.outline);

      text.outline_color_set(t_data.outline_ptr->r, t_data.outline_ptr->g, t_data.outline_ptr->b, t_data.outline_ptr->a);

      fprintf(stdout, "Changing outline color for text to (%d, %d, %d, %d)\n", t_data.outline_ptr->r, t_data.outline_ptr->g, t_data.outline_ptr->b, t_data.outline_ptr->a);

      return;
    }

  if (strcmp(ev->key, "s") == 0)
    {
      (t_data.shadow_ptr)++;

      POINTER_CYCLE(t_data.shadow_ptr, t_data.shadow);

      text.shadow_color_set(t_data.shadow_ptr->r, t_data.shadow_ptr->g, t_data.shadow_ptr->b, t_data.shadow_ptr->a);

      fprintf(stdout, "Changing shadow color for text to (%d, %d, %d, %d)\n", t_data.shadow_ptr->r, t_data.shadow_ptr->g, t_data.shadow_ptr->b, t_data.shadow_ptr->a);

      return;
    }

  if (strcmp(ev->key, "z") == 0)
    {
      const char *font;
      int size;

      text.font_get(&font, &size);

      size = (size + 10) % 50;
      if (!size) size = 10;

      text.font_set(font, size);

      fprintf(stdout, "Changing text's font size to %d\n", size);

      return;
    }
}

int
main(void)
{
  int size;
  const char *font;

  efl::eina::eina_init eina_init;
  efl::eo::eo_init init;
  if (!::ecore_evas_init()) return EXIT_FAILURE;
  if (!::evas_init()) return EXIT_FAILURE;

  struct text_preset_data init_data =
    {
      .font = {"DejaVu", "Courier", "Utopia"},
      .text = {BLACK, WHITE, GREY, RED, GREEN, BLUE},
      .shadow = {WHITE, BLUE, GREEN, RED},
      .outline = {WHITE, RED, GREEN, BLUE},
      .glow = {WHITE, BLUE, GREEN, RED},
      .glow2 = {WHITE, RED, BLUE, GREEN}
    };

  t_data = init_data;
  t_data.font_ptr = t_data.font;
  t_data.text_ptr = t_data.text;
  t_data.glow_ptr = t_data.glow;
  t_data.glow2_ptr = t_data.glow2;
  t_data.outline_ptr = t_data.outline;
  t_data.shadow_ptr = t_data.shadow;

  ee = ::ecore_evas_new(NULL, 10, 10, WIDTH, HEIGHT, NULL);
  if (!ee)
    goto error;

  ::ecore_evas_callback_destroy_set(ee, _on_destroy);
  ::ecore_evas_callback_resize_set(ee, _canvas_resize_cb);
  ::ecore_evas_show(ee);

  bg.color_set(255, 255, 255, 255);
  bg.position_set(0, 0);
  bg.evas::object::size_set(WIDTH, HEIGHT);
  bg.visibility_set(EINA_TRUE);

  bg.focus_set(EINA_TRUE);
  evas_object_event_callback_add(bg, EVAS_CALLBACK_KEY_DOWN, _on_keydown, NULL);

  text.style_set(EVAS_TEXT_STYLE_PLAIN);

  text.color_set(t_data.text_ptr->r, t_data.text_ptr->g, t_data.text_ptr->b, t_data.text_ptr->a);

  text.glow_color_set(t_data.glow_ptr->r, t_data.glow_ptr->g, t_data.glow_ptr->b, t_data.glow_ptr->a);

  text.glow2_color_set(t_data.glow2_ptr->r, t_data.glow2_ptr->g, t_data.glow2_ptr->b, t_data.glow2_ptr->a);

  text.outline_color_set(t_data.outline_ptr->r, t_data.outline_ptr->g, t_data.outline_ptr->b, t_data.outline_ptr->a);

  text.shadow_color_set(t_data.shadow_ptr->r, t_data.shadow_ptr->g, t_data.shadow_ptr->b, t_data.shadow_ptr->a);

  text.font_set(*t_data.font_ptr, 30);
  text.text_set("sample text");

  text.evas::object::size_set((3 * WIDTH) / 4, HEIGHT / 4);
  text.position_set(WIDTH / 8, (3 * HEIGHT) / 8);
  text.visibility_set(EINA_TRUE);

  text.font_get(&font, &size);
  fprintf(stdout, "Adding text object with font %s, size %d\n", font, size);

  border.file_set(border_img_path, NULL);
  border.border_set(3, 3, 3, 3);
  border.border_center_fill_set(EVAS_BORDER_FILL_NONE);

  border.evas::object::size_set(((3 * WIDTH) / 4) + 3, (HEIGHT / 4) + 3);
  border.position_set((WIDTH / 8) - 3, ((3 * HEIGHT) / 8) - 3);
  border.visibility_set(EINA_TRUE);

  fprintf(stdout, commands);
  ecore_main_loop_begin();

  ::ecore_evas_free(ee);
  ::ecore_evas_shutdown();
  return 0;

 error:
  fprintf(stderr, "you got to have at least one evas engine built and linked"
	  " up to ecore-evas for this example to run properly.\n");
  ::ecore_evas_shutdown();
  return -1;
}
