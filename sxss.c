/*
 * simple X screensaver
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/extensions/scrnsaver.h>

#include "config.h"

static void spawn(char *const argv[]) {
  switch (fork()) {
  case 0:
    execvp(argv[0], argv);
    perror("execvp");
    _exit(1);
  case -1:
    perror("fork");
  }
}


int main(int argc, char *argv[]) {
  XScreenSaverInfo *info;
  Display *dpy;
  int base, errbase;

  if(!(dpy = XOpenDisplay(0))) {
    printf("Cannot open display.\n");
    exit(1);
  }

  if (!XScreenSaverQueryExtension(dpy, &base, &errbase)) {
    printf("Screensaver extension not activated.\n");
    exit(1);
  }

  while(1) {

    info = XScreenSaverAllocInfo();
    XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), info);

    switch(info->state) {
    case ScreenSaverDisabled:
      sleep(10);
      break;
    case ScreenSaverOn:
      break;
    case ScreenSaverOff:
      if (info->til_or_since < 1000) spawn(screensaver);
      break;
    }
    sleep(1);
  }
}