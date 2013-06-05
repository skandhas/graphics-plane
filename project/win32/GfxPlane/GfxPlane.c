#include "stdafx.h"
#include <plotter.h>
#include "GfxPlane.h"
#include "plotter/glview.h"
#include "plotter/director.h"
#include "glcontroller.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

	MSG msg;
  HACCEL acctbl;
  LARGE_INTEGER freq, last, now, interval;
  glview * view;
  plt_director * director;
  glcontroller * controller;

  acctbl = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GFXPLANE));
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&last);
  interval.QuadPart = (LONGLONG)(1.0/60 * freq.QuadPart);

  plt_open();
  view       = glview_open(800, 480); 
  director   = plt_director_open();
  controller = glcontroller_open(director, view);
  glview_show(view);

  while (1)
  {
    if (! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      QueryPerformanceCounter(&now);

      if (now.QuadPart - last.QuadPart > interval.QuadPart)
      {
        last.QuadPart = now.QuadPart;
        controller->actions->draw(controller);
      }
      else
      {
         Sleep(1);
      }
      continue;
    }

    if (WM_QUIT == msg.message)
    {
      break;
    }

    if (! TranslateAccelerator(msg.hwnd, acctbl, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  return (int) msg.wParam;
}