SRCDIR := src
BUILDDIR := build
BUILDDIRGCW := build-gcw
BINDIR := bin

PROG   := rogue-card
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
LDFLAGS:=-I$(SRCDIR)/game -I$(SRCDIR)/common -I$(SRCDIR)/rogue-card -I$(SRCDIR)/sdl2
CCDYNAMICFLAGS := ${CFLAGS} ${LDFLAGS} -lSDL2 -lSDL2_image -ldl

SRC := $(shell find $(SRCDIR)/game $(SRCDIR)/common $(SRCDIR)/rogue-card $(SRCDIR)/sdl2 -type f -name '*.cpp')
OBJ := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC))
OBJGCW := $(patsubst %.cpp,$(BUILDDIRGCW)/%.o,$(SRC))
DEP := $(patsubst %.o,%.deps,$(OBJ))

all: game

full: tools game build-resources

build-resources:
	./bin/tools/data-compiler tilesets resources/src/tilesets.dat resources/tilesets.dat
	./bin/tools/data-compiler enemies resources/src/enemies.dat resources/enemies.dat
	./bin/tools/data-compiler objects resources/src/objects.dat resources/objects.dat
	./bin/tools/data-compiler font-atlas resources/src/font-atlas.dat resources/font-atlas.dat

game: $(PROG)
	cp -r config bin/

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

opk: tools build-resources
	mkdir -p dist/bin dist/resources
	cp -r config dist/
	cp $(BINDIR)/$(PROG) dist/bin/
	cp resources/intro.txt dist/resources/
	cp resources/tilesets.dat resources/enemies.dat resources/objects.dat resources/font-atlas.dat dist/resources/
	cp resources/action-attack.png resources/arrows.png resources/atlas-red.png resources/door-up.png resources/monsters.png resources/ui-equipment-select.png resources/action-loot.png resources/atlas-black.png resources/card.png resources/final-goal.png resources/objects.png resources/ui-inventory.png resources/action-pick.png resources/atlas-green.png resources/cursor.png resources/health-color.png resources/quick-action-bar.png resources/ui.png resources/action-runaway.png resources/atlas.png resources/door-down.png resources/menu-background.png resources/ui-equipment.png dist/resources/

	mksquashfs dist $(TARGETDIST) -all-root -noappend -no-exports -no-xattrs

tools:
	@mkdir -p $(BINDIR)/tools
	$(CC) ${CFLAGS} ${CFLAGS} ${LDFLAGS} $(shell find src/tools/dataCompiler/ $(SRCDIR)/common/ -name "*.cpp") \
		-o $(BINDIR)/tools/data-compiler
	$(CC) ${CFLAGS} ${CFLAGS} ${LDFLAGS} $(shell find src/tools/dataDecompiler/ $(SRCDIR)/common/ -name "*.cpp") \
		-o $(BINDIR)/tools/data-decompiler
	g++ -lSDL2_ttf -lSDL2 -lSDL2_image -Isrc src/tools/font2png.cpp -o $(BINDIR)/font2png
