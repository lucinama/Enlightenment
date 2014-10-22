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

#include <Evas_GL.h>
#include <stdio.h>

typedef struct _GLData GLData;

struct _GLData
{
  Evas_GL_API *glapi;
  GLuint       program;
  GLuint       vtx_shader;
  GLuint       fgmt_shader;
  GLuint       vbo;
  int          initialized : 1;
};

static float red = 1.0;

static GLuint
load_shader( GLData *gld, GLenum type, const char *shader_src )
{
  Evas_GL_API *gl = gld->glapi;
  GLuint shader;
  GLint compiled;

  shader = gl->glCreateShader(type);
  if (shader==0)
    return 0;

  gl->glShaderSource(shader, 1, &shader_src, NULL);
  gl->glCompileShader(shader);
  gl->glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (!compiled)
    {
      GLint info_len = 0;
      gl->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
      if (info_len > 1)
	{
	  char* info_log = malloc(sizeof(char) * info_len);

	  gl->glGetShaderInfoLog(shader, info_len, NULL, info_log);
	  printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, shader_src );
	  free(info_log);
	}
      gl->glDeleteShader(shader);
      return 0;
    }

  return shader;
}

static int
init_shaders(GLData *gld)
{
  Evas_GL_API *gl = gld->glapi;
  GLbyte vShaderStr[] =
    "attribute vec4 vPosition;    \n"
    "void main()                  \n"
    "{                            \n"
    "   gl_Position = vPosition;  \n"
    "}                            \n";

  GLbyte fShaderStr[] =
    "#ifdef GL_ES                                 \n"
    "precision mediump float;                     \n"
    "#endif                                       \n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
    "}                                            \n";

  GLint linked;

  gld->vtx_shader  = load_shader(gld, GL_VERTEX_SHADER, (const char*)vShaderStr);
  gld->fgmt_shader = load_shader(gld, GL_FRAGMENT_SHADER, (const char*)fShaderStr);

  gld->program = gl->glCreateProgram( );
  if (gld->program==0)
    return 0;

  gl->glAttachShader(gld->program, gld->vtx_shader);
  gl->glAttachShader(gld->program, gld->fgmt_shader);

  gl->glBindAttribLocation(gld->program, 0, "vPosition");
  gl->glLinkProgram(gld->program);
  gl->glGetProgramiv(gld->program, GL_LINK_STATUS, &linked);

  if (!linked)
    {
      GLint info_len = 0;
      gl->glGetProgramiv(gld->program, GL_INFO_LOG_LENGTH, &info_len);
      if (info_len > 1)
	{
	  char* info_log = malloc(sizeof(char) * info_len);

	  gl->glGetProgramInfoLog(gld->program, info_len, NULL, info_log);
	  printf("Error linking program:\n%s\n", info_log);
	  free(info_log);
	}
      gl->glDeleteProgram(gld->program);
      return 0;
    }
  return 1;
}

static void
_init_gl(Evas_Object *obj)
{
  GLData *gld = evas_object_data_get(obj, "gld");
  Evas_GL_API *gl = gld->glapi;
  GLfloat vVertices[] = {
    0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f };

  if (!init_shaders(gld))
    {
      printf("Error Initializing Shaders\n");
      return;
    }

  gl->glGenBuffers(1, &gld->vbo);
  gl->glBindBuffer(GL_ARRAY_BUFFER, gld->vbo);
  gl->glBufferData(GL_ARRAY_BUFFER, 3 * 3 * 4, vVertices, GL_STATIC_DRAW);
}

static void
_del_gl(Evas_Object *obj)
{
  GLData *gld = evas_object_data_get(obj, "gld");
  if (!gld)
    {
      printf("Unable to get GLData. \n");
      return;
    }
  Evas_GL_API *gl = gld->glapi;

  gl->glDeleteShader(gld->vtx_shader);
  gl->glDeleteShader(gld->fgmt_shader);
  gl->glDeleteProgram(gld->program);
  gl->glDeleteBuffers(1, &gld->vbo);

  evas_object_data_del((Evas_Object*)obj, "..gld");
  free(gld);
}

static void
_resize_gl(Evas_Object *obj)
{
  int w, h;
  GLData *gld = evas_object_data_get(obj, "gld");
  Evas_GL_API *gl = gld->glapi;

  elm_glview_size_get(obj, &w, &h);

  gl->glViewport(0, 0, w, h);
}

static void
_draw_gl(Evas_Object *obj)
{
  Evas_GL_API *gl = elm_glview_gl_api_get(obj);
  GLData *gld = evas_object_data_get(obj, "gld");
  if (!gld) return;
  int w, h;

  elm_glview_size_get(obj, &w, &h);

  gl->glViewport(0, 0, w, h);
  gl->glClearColor(red,0.8,0.3,1);
  gl->glClear(GL_COLOR_BUFFER_BIT);

  gl->glEnable(GL_BLEND);

  gl->glUseProgram(gld->program);

  gl->glBindBuffer(GL_ARRAY_BUFFER, gld->vbo);
  gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			    0, 0);
  gl->glEnableVertexAttribArray(0);

  gl->glDrawArrays(GL_TRIANGLES, 0, 3);

  gl->glFinish();

  red -= 0.1;
  if (red < 0.0) red = 1.0;
}

static Eina_Bool
_anim(void *data)
{
  elm_glview_changed_set(data);
  return EINA_TRUE;
}

static void
_on_done(void *data, Evas_Object *obj, void *event_info)
{
  evas_object_del((Evas_Object*)data);
  elm_exit();
}

static void
_del(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
  Ecore_Animator *ani = evas_object_data_get(obj, "ani");
  ecore_animator_del(ani);
}

EAPI_MAIN int
elm_main (int argc, char *argv[])
{
  Ecore_Animator *ani;
  GLData *gld = NULL;

  if (!(gld = calloc(1, sizeof(GLData)))) return 1;

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  ::elm_win win(elm_win_util_standard_add("glview simple", "GLView Simple"));
  win.autodel_set(true);

  ::elm_box bx(efl::eo::parent = win);
  bx.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  win.resize_object_add(bx);
  bx.visibility_set(true);

  ::elm_glview gl(efl::eo::parent = win);
  gld->glapi = gl.gl_api_get();
  gl.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  gl.size_hint_weight_set(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

  gl.mode_set(ELM_GLVIEW_ALPHA | ELM_GLVIEW_DEPTH);
  gl.resize_policy_set( ELM_GLVIEW_RESIZE_POLICY_RECREATE);
  gl.render_policy_set( ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);
  gl.init_func_set(_init_gl);
  gl.del_func_set( _del_gl);
  gl.resize_func_set(_resize_gl);
  gl.render_func_set(_draw_gl);

  bx.pack_end(gl);
  gl.visibility_set(true);

  gl.focus_set(EINA_TRUE);

  ani = ecore_animator_add(_anim, gl);

  gl.data_set("ani", ani);
  gl.data_set("gld", gld);
  gl.event_callback_add(EVAS_CALLBACK_DEL, _del, gl);

  ::elm_button bt(efl::eo::parent = win);
  elm_object_text_set(bt._eo_ptr(), "OK"); // XXX
  bt.size_hint_align_set(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bt.size_hint_align_set(EVAS_HINT_EXPAND, 0.0);
  bx.pack_end(bt);
  bt.visibility_set(true);
  bt.callback_clicked_add(&_on_done);

  win.evas::object::size_set(320, 480);
  win.visibility_set(true);

  elm_run();
  elm_shutdown();

  return 0;
}
ELM_MAIN()
