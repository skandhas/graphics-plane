#include <windows.h>
#include "plotter.h"
#include "glview.h"
#include "gl/glew.h"
#include "gl/wglew.h"

struct glview {
  HWND wnd;
  HDC  dc; 
  HGLRC rc; 
  int  width;
  int  height;
};

static plt_bool 
init_gl(glview * view)
{
  int pixel_format;
  GLenum glew_init_ret;
  PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 
                                1,
                                PFD_SUPPORT_OPENGL |
                                PFD_DRAW_TO_WINDOW |
                                PFD_DOUBLEBUFFER,
                                PFD_TYPE_RGBA,    
                                32, 
                                0, 0, 0, 0, 0, 0,
                                0,
                                0,
                                0,
                                0, 0, 0, 0,
                                24,
                                8,
                                0,
                                PFD_MAIN_PLANE, 
                                0,
                                0, 0, 0, };

  view->dc = GetDC(view->wnd);
  pixel_format = ChoosePixelFormat(view->dc, &pfd);
  SetPixelFormat(view->dc, pixel_format, &pfd);

  view->rc = wglCreateContext(view->dc);
  wglMakeCurrent(view->dc, view->rc);

  glew_init_ret = glewInit();

  if (GLEW_OK != glew_init_ret) {
    return FALSE;
  }

  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  return TRUE;
}

static void
release_gl(glview * view)
{
  if (view->dc != NULL && view->rc != NULL) {
    wglMakeCurrent(view->dc, NULL);
    wglDeleteContext(view->rc);
  }
}

static LRESULT CALLBACK
win_proc(HWND wnd, UINT message, WPARAM wparam, LPARAM lparam)
{
  switch (message) {
    case WM_PAINT:
      {
        PAINTSTRUCT ps;
        BeginPaint(wnd, &ps);
        EndPaint(wnd, &ps);
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(wnd, message, wparam, lparam);
  }
  return 0;
}

static plt_bool
create(glview * view)
{
#define PLOTTER_WINDOW_CLASS_NAME  L"Plotter Window"
  HINSTANCE instance = GetModuleHandle( NULL );
  WNDCLASS  wc;

  wc.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc    = win_proc;
  wc.cbClsExtra     = 0;
  wc.cbWndExtra     = 0;
  wc.hInstance      = instance;
  wc.hIcon          = LoadIcon( NULL, IDI_WINLOGO );
  wc.hCursor        = LoadCursor( NULL, IDC_ARROW );
  wc.hbrBackground  = NULL;
  wc.lpszMenuName   = 0;
  wc.lpszClassName  = PLOTTER_WINDOW_CLASS_NAME;
  
  if (!RegisterClass(&wc)) {
    return FALSE;
  }
  
  view->wnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
                              PLOTTER_WINDOW_CLASS_NAME,
                              PLOTTER_WINDOW_CLASS_NAME,
                              WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX,
                              0, 0,
                              view->width,
                              view->height,
                              NULL,
                              NULL,
                              instance,
                              NULL );

  if (view->wnd) {
    return FALSE;
  }

  if(!init_gl(view)) {
    release_gl(view);
    return FALSE;
  }
  return TRUE;
}

glview *
glview_open(int width, int height)
{
  glview * view = malloc(sizeof(glview));
  memset(view, 0, sizeof(glview));

  view->width = width;
  view->height = height;
  create(view); 
  return view;
}

void
glview_show(glview * view){
   ShowWindow(view->wnd, SW_SHOW);
}

void
glview_swap_buffers(glview * view)
{
  if (view->dc) {
    SwapBuffers(view->dc);
  }
}

void
glview_close(glview * view)
{
  if (view) {
    release_gl(view);
    free(view);
  }
}


