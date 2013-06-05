#include "gl/glew.h"
#include "gl/glu.h"
#include "plotter.h"
#include "plotter/glview.h"
#include "plotter/director.h"

typedef struct glcamera{
  float angle_x;
  float angle_y;
  float distance;
}glcamera;

struct plt_director{
  glview *view;
  glcamera camera;
};

static void
set_camera(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(pos_x, pos_y, pos_z, target_x, target_y, target_z, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}
static void
set_viewport(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0f, (float)(w)/h, 0.1f, 20.0f); 
  glMatrixMode(GL_MODELVIEW);
}
static void
init_lights()
{ 
  float light_pos[4] = {0, 0, 20, 1}; 

  GLfloat light_ka[] = {.2f, .2f, .2f, 1.0f};      // ambient light
  GLfloat light_kd[] = {.7f, .7f, .7f, 1.0f};      // diffuse light
  GLfloat light_ks[] = {1, 1, 1, 1};               // specular light
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ka);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_kd);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_ks);
 
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

  glEnable(GL_LIGHT0);        
}

plt_director *
plt_director_open(void)
{
  plt_director * director = calloc(1, sizeof(plt_director));
  director->camera.angle_x  = 0;
  director->camera.angle_y  = 0;
  director->camera.distance = 5;

  glShadeModel(GL_SMOOTH); 
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);

  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  glClearColor(0, 0, 0, 0);
  glClearStencil(0);  
  glClearDepth(1.0f);  
  glDepthFunc(GL_LEQUAL);
  init_lights();
  set_camera(0, 0, 10, 0, 0, 0);
  return director;
}

void
plt_director_set_viewport(plt_director * director, int w, int h)
{
  set_viewport(w, h);
}

void
plt_director_draw(plt_director * director)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glPushMatrix();

    glTranslatef(0, 0, director->camera.distance);
    glRotatef(director->camera.angle_x, 1, 0, 0);   // pitch
    glRotatef(director->camera.angle_y, 0, 1, 0);   // heading

    glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, 1);
        glColor3f(1, 0, 0);
        glVertex3f(3, -2, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0, 2, 0);
        glColor3f(0, 0, 1);
        glVertex3f(-3, -2, 0);
    glEnd();
    glPopMatrix();
}

void
plt_director_close(plt_director * director)
{

}


