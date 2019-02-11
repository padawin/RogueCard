SRCDIR := src
BUILDDIR := build
BUILDDIRGCW := build-gcw
BINDIR := bin

PROG   := card-rogue
TARGET := $(PROG)
TARGETDIST := $(PROG).opk
CC     := $(CROSS_COMPILE)g++ -std=c++11
INCL   :=
CFLAGS := -g -O2 -Wall -Wmissing-declarations -Weffc++ \
		-pedantic -pedantic-errors -Wextra -Wcast-align \
		-Wcast-qual -Wconversion -Wsign-conversion \
		-Wdisabled-optimization \
		-Werror -Wfloat-equal -Wformat=2 \
		-Wformat-nonliteral -Wformat-security \
		-Wformat-y2k \
		-Wimport -Winit-self -Winline \
		-Winvalid-pch \
		-Wlong-long \
		-Wmissing-field-initializers -Wmissing-format-attribute \
		-Wmissing-include-dirs -Wmissing-noreturn \
		-Wpacked -Wpointer-arith \
		-Wredundant-decls \
		-Wshadow -Wstack-protector \
		-Wstrict-aliasing=2 -Wswitch-default \
		-Wswitch-enum \
		-Wunreachable-code -Wunused \
		-Wunused-parameter \
		-Wvariadic-macros \
		-Wwrite-strings
LDFLAGS:=-Isrc/
CCDYNAMICFLAGS := ${CFLAGS} ${LDFLAGS} -lSDL2 -lSDL2_image

SRC := $(shell find $(SRCDIR)/ -type f -name '*.cpp')
OBJ := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC))
OBJGCW := $(patsubst %.cpp,$(BUILDDIRGCW)/%.o,$(SRC))
DEP := $(patsubst %.o,%.deps,$(OBJ))

all: game

game: $(PROG)

-include $(DEP)

%.deps: %.cpp
	$(CC) -MM $< >$@

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) -c -MMD $(patsubst $(BUILDDIR)/%.o,%.cpp,$@) $(CCDYNAMICFLAGS) -o $@

$(BUILDDIRGCW)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) -DGCW -c -MMD $(patsubst $(BUILDDIRGCW)/%.o,%.cpp,$@) $(CCDYNAMICFLAGS) -o $@

clean:
	rm -rf $(BUILDDIR) $(LIBDIR)

$(PROG): $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(CCDYNAMICFLAGS)

gcw: $(OBJGCW)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$(PROG) $^ $(CCDYNAMICFLAGS)

opk:
	mkdir -p dist/bin
	cp -r configs dist/
	cp $(BINDIR)/$(PROG) dist/bin/
	mksquashfs dist $(TARGETDIST) -all-root -noappend -no-exports -no-xattrs
