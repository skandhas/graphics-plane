#include <windows.h>
#include "plotter/glview.h"
#include "plotter/director.h"
#include "glcontroller.h"
#include "win_proc.h"


LRESULT CALLBACK
glview_win_proc(HWND wnd, UINT message, WPARAM wparam, LPARAM lparam)
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