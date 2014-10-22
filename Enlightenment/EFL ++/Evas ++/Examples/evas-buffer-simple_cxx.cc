#include <Evas.h>
#include <Evas_Engine_Buffer.h>
#include <stdio.h>
#include <errno.h>

#include <Eina.hh>
#include <Evas.hh>
#include <Eo.hh>
#include <Efl.hh>

#include "canvas/evas_canvas.eo.hh"
#include "canvas/evas_rectangle.eo.hh"

#define WIDTH (320)
#define HEIGHT (240)

static Evas *create_canvas(int width, int height);
static void destroy_canvas(Evas *canvas);
static void draw_scene(Evas *canvas);

static void save_scene(Evas *canvas, const char *dest);

int main(void)
{
  Evas *canvas;

  evas_init();

  canvas = create_canvas(WIDTH, HEIGHT);
  if (!canvas)
    return -1;

  evas::rectangle bg(efl::eo::parent = canvas);
  bg.color_set(255, 255, 255, 255); 
  bg.position_set( 0, 0);                 
  bg.evas::object::size_set(WIDTH, HEIGHT); 
  bg.visibility_set(EINA_TRUE);     

  puts("initial scene, with just background:");
  draw_scene(canvas);

  evas::rectangle r1(efl::eo::parent = canvas);
  r1.color_set(255, 0, 0, 255); 
  r1.position_set(10, 10);
  r1.evas::object::size_set(100, 100);
  r1.visibility_set(EINA_TRUE);

  evas::rectangle r2(efl::eo::parent = canvas);
  r2.color_set(0, 128, 0, 128); 
  r2.position_set(10, 10);
  r2.evas::object::size_set( 50, 50);
  r2.visibility_set(EINA_TRUE);

  evas::rectangle r3(efl::eo::parent = canvas);
  r3.color_set(0, 128, 0, 255); 
  r3.position_set(60, 60);
  r3.evas::object::size_set(50, 50);
  r3.visibility_set(EINA_TRUE);

  puts("final scene (note updates):");
  draw_scene(canvas);
  save_scene(canvas, "/tmp/evas-buffer-simple-render.ppm");

  destroy_canvas(canvas);

  evas_shutdown();

  return 0;
}

static Evas *create_canvas(int width, int height)
{
  Evas *canvas;
  Evas_Engine_Info_Buffer *einfo;
  int method;
  void *pixels;

  method = evas_render_method_lookup("buffer");
  if (method <= 0)
    {
      fputs("ERROR: evas was not compiled with 'buffer' engine!\n", stderr);
      return NULL;
    }

  canvas = evas_new();
  if (!canvas)
    {
      fputs("ERROR: could not instantiate new evas canvas.\n", stderr);
      return NULL;
    }

  evas_output_method_set(canvas, method);
  evas_output_size_set(canvas, width, height);
  evas_output_viewport_set(canvas, 0, 0, width, height);

  einfo = (Evas_Engine_Info_Buffer *)evas_engine_info_get(canvas);
  if (!einfo)
    {
      fputs("ERROR: could not get evas engine info!\n", stderr);
      evas_free(canvas);
      return NULL;
    }

  pixels = malloc(width * height * sizeof(int));
  if (!pixels)
    {
      fputs("ERROR: could not allocate canvas pixels!\n", stderr);
      evas_free(canvas);
      return NULL;
    }

  einfo->info.depth_type = EVAS_ENGINE_BUFFER_DEPTH_ARGB32;
  einfo->info.dest_buffer = pixels;
  einfo->info.dest_buffer_row_bytes = width * sizeof(int);
  einfo->info.use_color_key = 0;
  einfo->info.alpha_threshold = 0;
  einfo->info.func.new_update_region = NULL;
  einfo->info.func.free_update_region = NULL;
  evas_engine_info_set(canvas, (Evas_Engine_Info *)einfo);

  return canvas;
}

static void destroy_canvas(Evas *canvas)
{
  Evas_Engine_Info_Buffer *einfo;

  einfo = (Evas_Engine_Info_Buffer *)evas_engine_info_get(canvas);
  if (!einfo)
    {
      fputs("ERROR: could not get evas engine info!\n", stderr);
      evas_free(canvas);
      return;
    }

  free(einfo->info.dest_buffer);
  evas_free(canvas);
}

static void draw_scene(Evas *canvas)
{
  Eina_List *updates, *n;
  Eina_Rectangle *update;

  updates = evas_render_updates(canvas);

  EINA_LIST_FOREACH(updates, n, update)
    printf("UPDATED REGION: pos: %3d, %3d    size: %3dx%3d\n",
	   update->x, update->y, update->w, update->h);

  evas_render_updates_free(updates);
}

static void save_scene(Evas *canvas, const char *dest)
{
  Evas_Engine_Info_Buffer *einfo;
  const unsigned int *pixels, *pixels_end;
  int width, height;
  FILE *f;

  einfo = (Evas_Engine_Info_Buffer *)evas_engine_info_get(canvas);
  if (!einfo)
    {
      fputs("ERROR: could not get evas engine info!\n", stderr);
      return;
    }
  evas_output_size_get(canvas, &width, &height);

  f = fopen(dest, "wb+");
  if (!f)
    {
      fprintf(stderr, "ERROR: could not open for writing '%s': %s\n",
	      dest, strerror(errno));
      return;
    }

  pixels = einfo->info.dest_buffer;
  pixels_end = pixels + (width * height);

  fprintf(f, "P6\n%d %d\n255\n",  width, height);
  for (; pixels < pixels_end; pixels++)
    {
      int r, g, b;

      r = ((*pixels) & 0xff0000) >> 16;
      g = ((*pixels) & 0x00ff00) >> 8;
      b = (*pixels) & 0x0000ff;

      fprintf(f, "%c%c%c", r, g, b);
    }

  fclose(f);
  printf("saved scene as '%s'\n", dest);
}
