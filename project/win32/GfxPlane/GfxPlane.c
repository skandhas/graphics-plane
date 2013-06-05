#include "stdafx.h"
#include <plotter.h>
#include "GfxPlane.h"
#include "plotter/glview.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

	MSG msg;
  HACCEL acctbl;
  LARGE_INTEGER freq;
  LARGE_INTEGER last;
  LARGE_INTEGER now;
  LARGE_INTEGER interval;
  glview * view;

  plt_open();
  acctbl = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GFXPLANE));
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&last);
  interval.QuadPart = (LONGLONG)(1.0/60 * freq.QuadPart);

  view = glview_open(800, 400);
  glview_show(view);


  while (1)
  {
    if (! PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      QueryPerformanceCounter(&now);

      if (now.QuadPart - last.QuadPart > interval.QuadPart)
      {
        last.QuadPart = now.QuadPart;
      }
      else
      {
        Sleep(0);
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