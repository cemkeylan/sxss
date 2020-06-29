# See LICENSE for copyright information
PREFIX = /usr/local
BINDIR = ${PREFIX}/bin

LIBS   = -lXss -lX11 -lc
CC     = cc

all: sxss

sxss: config.h sxss.c
	${CC} ${CFLAGS} ${LDFLAGS} -o sxss sxss.c ${LIBS}

config.h: config.def.h
	cp config.def.h config.h

clean:
	${RM} sxss

install: all
	mkdir -p ${DESTDIR}${BINDIR}
	cp sxss ${DESTDIR}${BINDIR}/sxss
	chmod 755 ${DESTDIR}${BINDIR}/sxss

uninstall:
	${RM} ${DESTDIR}${BINDIR}/sxss

.PHONY: all clean install uninstall
