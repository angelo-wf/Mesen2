
#include <stdio.h>
#include <stdint.h>

#include <X11/Xlib.h>
#include <X11/cursorfont.h>

// gcc -c gccx11.c -o gccx11.o
// gcc -o gccx11 gccx11.o -lX11
// (GCC needs libraries at end, clang allows them before as well)

int main(int argc, char** argv) {
  Display* display = XOpenDisplay(NULL);
  int defaultScreen = XDefaultScreen(display);
	Window rootWindow = XRootWindow(display, defaultScreen);

  Window root = 0;
	Window c = 0;
	Window child = 0;
	int rootX, rootY, childX, childY;
	uint32_t mask;

	XGrabServer(display);
	XQueryPointer(display, rootWindow, &root, &c, &rootX, &rootY, &childX, &childY, &mask);
  XUngrabServer(display);
	XFlush(display);

  printf("Cursor: %d,%d\n", rootX, rootY);

  return 0;
}
