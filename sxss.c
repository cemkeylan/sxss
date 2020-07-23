/*
 * simple X screensaver
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/extensions/scrnsaver.h>
#include <xcb/xproto.h>

#include "config.h"

#define VERSION "0.1.0"

static void
spawn(char *const argv[])
{
	switch (fork()) {
	case 0:
		execvp(argv[0], argv);
		perror("execvp");
		_exit(1);
	case -1:
		perror("fork");
	}
}

static void
die(const char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}


int
main(int argc, char *argv[])
{

	if (argc > 1) die("sxss-"VERSION);

	XScreenSaverInfo *info;
	Display *dpy;
	int base, errbase;

	if (!(dpy = XOpenDisplay(0))) die("Cannot open display.");

	if (!XScreenSaverQueryExtension(dpy, &base, &errbase))
		die("Screensaver extension not activated.");

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
