# makefile for configuring lablGTK

# Default compilers
ifdef USE_DOTOPT
CAMLC = ocamlc.opt
CAMLOPT = ocamlopt.opt
else
CAMLC = ocamlc
CAMLOPT = ocamlopt
endif

CAMLMKTOP = ocamlmktop
CAMLMKLIB = ocamlmklib
CAMLP4O = camlp4o
# Default installation directories
BINDIR = `$(GETLIBDIR) | sed -e 's|/lib/[^/]*$$|/bin|' -e 's|/lib$$|/bin|'`
INSTALLDIR = $(LIBDIR)/lablgtk
DLLDIR = $(LIBDIR)/stublibs

# Autoconf
GETLIBDIR = ocamlc -where
LIBDIR = `$(GETLIBDIR)`
RANLIB = `which ranlib 2>/dev/null | sed -e 's|.*/ranlib$$|!|' -e 's/^[^!]*$$/:/' -e 's/!/ranlib/'`

GTK_CONFIG = gtk-config
GNOME_CONFIG = gnome-config
GLADE_CONFIG = libglade-config
GDK_PIXBUF_CONFIG = gdk-pixbuf-config

ifdef USE_GNOME
ifdef USE_GLADE
GTKCFLAGS = `$(GLADE_CONFIG) --cflags gnome` `$(GDK_PIXBUF_CONFIG) --cflags`
GLADELIBS = `$(GLADE_CONFIG) --libs gnome`
else
GTKCFLAGS = `$(GNOME_CONFIG) --cflags gnome` `$(GDK_PIXBUF_CONFIG) --cflags`
endif
GDKPIXBUFLIBS = `$(GDK_PIXBUF_CONFIG) --libs`
GNOMELIBS = `$(GNOME_CONFIG) --libs gtkxmhtml`
else
ifdef USE_GLADE
GTKCFLAGS = `$(GLADE_CONFIG) --cflags gtk`
GLADELIBS = `$(GLADE_CONFIG) --libs gtk`
else
GTKCFLAGS = `$(GTK_CONFIG) --cflags`
endif
endif

GTKLIBS = `$(GTK_CONFIG) --libs`
GLLIBS = -lGLU -lGL

all: config.make
	cd src && $(MAKE) $@

opt install clean depend:
	cd src && $(MAKE) $@

config.make:
	@echo "You must first configure: make configure <options>"
	@echo "Options are:"
	@echo "  USE_GL=1       build GtkGLArea support. Requires LablGL"
	@echo "  USE_GNOME=1    build GtkXmHTML and GdkPixbuf support"
	@echo "  USE_GLADE=1    build libglade support"
	@echo "  USE_DOTOPT=1   use ocamlc.opt and ocamlopt.opt"
	@exit 2

configure:
	@if test -z "$(GTKLIBS)"; then echo "$(GTK_CONFIG) failed"; exit 2; fi
	@if test "$(USE_GLADE)" = 1 && test -z "$(GLADELIBS)"; then \
	  echo "$(GLADE_CONFIG) failed"; exit 2; fi
	@if test "$(USE_GNOME)" = 1 && test -z "$(GNOMELIBS)"; then \
	  echo "$(GNOME_CONFIG) failed"; exit 2; fi
	@if test "$(USE_GNOME)" = 1 && test -z "$(GDKPIXBUFLIBS)"; then \
	  echo "$(GDK_PIXBUF_CONFIG) failed"; exit 2; fi
	@echo "# config.make, generated by make configure" > config.make
	@echo CAMLC=$(CAMLC) >> config.make
	@echo CAMLOPT=$(CAMLOPT) >> config.make
	@echo CAMLMKTOP=$(CAMLMKTOP) >> config.make
	@echo CAMLMKLIB=$(CAMLMKLIB) >> config.make
	@echo CAMLP4O=$(CAMLP4O) >> config.make
	@echo USE_GL=$(USE_GL) >> config.make
	@echo USE_GNOME=$(USE_GNOME) >> config.make
	@echo USE_GLADE=$(USE_GLADE) >> config.make
	@echo USE_CC=$(USE_CC) >> config.make
	@echo DEBUG=$(DEBUG) >> config.make
	@echo CC=$(CC) >> config.make
	@echo RANLIB=$(RANLIB) >> config.make
	@echo LIBDIR=$(LIBDIR) >> config.make
	@echo BINDIR=$(BINDIR) >> config.make
	@echo INSTALLDIR=$(INSTALLDIR) >> config.make
	@echo DLLDIR=$(DLLDIR) >> config.make
	@echo GTKCFLAGS=$(GTKCFLAGS) >> config.make
	@echo GTKLIBS=$(GTKLIBS) >> config.make
	@echo GLLIBS=$(GLLIBS) >> config.make
	@echo GNOMELIBS=$(GNOMELIBS) $(GDKPIXBUFLIBS) >> config.make
	@echo GLADELIBS=$(GLADELIBS) >> config.make
	@cat config.make
